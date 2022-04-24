/*------------------------------------------------------------------+
| PROGRAM  : regr.cpp - This routine builds X'X, X'y and SSy.       |
|            Does a multiple regression on the desired data set.    |
| CALLED BY: tty_stat, wind_stat                                    |
| CALLS    : buildss,borderinv                                      |
|                                                                   |
| 29 Apr 91 - Modified to handle data,row,col as global variables.  |
|  9 Jun 91 - Modified XP to be a pointer.                          |
|  1 Feb 92 - Changed <os9stat.h> to "os9stat.h"                    |
|  2 Feb 92 - Changed data handling from data[] to working.osd      |
| 24 Apr 92 - Added the ability to do a regression on only part     |
|             of data[]                                             |
| 25 May 92 - Had to fix some problems that were caused with XP when|
|             the full matrix was not being used with the values    |
|             being selected by the new bldstr routine.             |
| 31 May 92 - Modified the call to buildss to return the varlst     |
|             so the results could be used in the screen info output|
| 14 Jun 92 - Added suggestions on which variables to delete from   |
|             from the regression model.                            |
| 20 Dec 92 - Added comments and check to determine why the value   |
|             to be deleted from the regression model is to be      |
|             deleted.                                              |
| 13 Feb 93 - Added the hardcopy option.                            |
| 10 May 93 - Fixed the problem with selecting the variable to be   |
|             deleted when using negative numbers.                  |
| 13 Jun 93 - Added fprint to error and debug lines.  Also added .  |
|             printouts to let the user know something is happening.|
| 25 Jul 93 - MAJOR MOD: Move the bldstr, and varcnt from buildss   |
|             to here, to optimize memory requirements for XP.      |
| 25 Sep 93 - Looks like the bugs in the caused by the above mod    |
|             have been finally ironed out.                         |
|  5 Jul 97 - Started porting over to C++ to work with C++ Builder  |
+------------------------------------------------------------------*/


#include <stdio.h>
#include <math.h>
#include <alloc.h>
#include "WebStat.h"
#include "TSSData.h"
#include "mathss.h"
#include "matrixss.h"
//----------------------------------------------------------------------

void borderinv(double *, int);
void buildss(double *, int, int *);
void minmax(double *, double *, double *, int);

void regr (int *varlst, int varcnt)
{
   char buff[255];
   char val[32];

   double N;
   double std;
   double mean;
   double se;
   double serr;
   double tmp1;
   double r2;
   double adjr2;
   double stdn;
   double min;
   double max;
   double tmp2;

   int i;
   int j,k,n;

   double rss;
   double rms;
   double rs;
   double ts;


//*****************
   n=varcnt+1;  /* Since col is 0...n-1, make 1...n */
//****************

   double *XP = new double[MAXCOL*MAXCOL];
   for (i=0;i<MAXCOL*MAXCOL;i++) XP[i]=0;
   if (XP == NULL) return;

/***************/
   buildss(XP,varcnt,varlst);
/***************/

/* Allocate the required memory for the work variables */
   double  *x = new double[MAXCOL];
   double *x2 = new double[MAXCOL];
   double  *y = new double[MAXCOL];

   for (i=0;i<MAXCOL;i++) {
      x[i]  = 0;
      x2[i] = 0;
      y[i]  = 0;
   }
/* Get the sum of squares and the sum of x's */

   for(i=0 ;i<=n; i++) {
      x[i] = XP[i*n];
      x2[i] = XP[i+i*n];
   }

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"Sum of Squares Matrix");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   for (k=0;k<varcnt;k++) {
      sprintf(buff,"");
      for (i=0;i<varcnt;i++) {
         if (XP[k+i*n] != 0) {
            sprintf(val,"%4e ", XP[k+i*n]);
            strcat(buff,val);
         }
         else {
            sprintf(val,"             ");
            strcat(buff,val);
         }
      }
         SStat->Results->Lines->Add(buff);
   }

/* Used to compute Beta since XP changes */

   for (i=0; i<n; i++)
     y[i] = XP[i+n*(n-1)];

   ts = XP[n*n-1];  /* Sum y squared (Total sum of squares) */

   N=XP[0];
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"\nThe Univarite Statistics Are:  N=%4d",SSData->row+1);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"    Mean                Std Dev/(n-1)      Std Dev/n");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   for (i=1; i<n; i++) {
      mean= XP[i*n]/N;
      tmp1= XP[i*n] * XP[i*n]/N;
      tmp2=x2[i] - tmp1;
      stdn=(1./N)*tmp2;
      std=(1./(N-1.))*tmp2;
      sprintf(buff,"%4e          %4e      %4e",mean,sqrt(std),sqrt(stdn));
      SStat->Results->Lines->Add(buff);
   }

   if  (x) delete[] x;
   if (x2) delete[] x2;


/****************/
   borderinv(XP,varcnt);
/****************/

#ifdef DEBUG
   for (i=0;i<n*n;i++) fprintf(stderr,"REGR: XP[%d]=%7.4g\n",i,*(XP+i));
#endif

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   sprintf(buff,"(X'X) Inverse");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   for (k=0;k<varcnt;k++) {
      sprintf(buff,"");
      sprintf(val,"");
      for (i=0;i<varcnt;i++) {
         if (XP[i+k*n] != 0) {
            if (XP[i+k*n] > 0) sprintf(val," ");
            sprintf(val,"% 4e ", XP[i+k*n]);
            strcat(buff,val);
         }
         else sprintf(val,"");
      }
      SStat->Results->Lines->Add(buff);
   }

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   for (i=0; i<n; i++){
      for (j=1; j<n; j++)
         *(XP+j+i*n) = *(XP+i+j*n);
   }


   double *beta = new double[MAXCOL];
   double *tval = new double[MAXCOL];

   for (i=0;i<MAXCOL;i++) {
      beta[i]=0;
      tval[i]=0;
   }

   rs=0.0;

/* See p. 96, Sr= B'X'y */
/* This loop builds Sr */

   for (i=0; i<varcnt; i++) {
      for (j=0; j<varcnt; j++)
         *(beta+i) = *(beta+i) + *(XP+i+j*n) * *(y+j);
      rs = rs + *(beta+i) * *(y+i);
   }

   rss=ts-rs;    /* p.96 Rs=A(K+1,K+J) - Sr NOTE: rss = Rs */
                 /*      se=Rs/(n-k), where N=n and k=n */
   se=rss/(N-varcnt); /* n=varcnt+1 since varcnt=0...n-1 */

   rms= rs - ( *(XP + varcnt*n) * (*(XP + varcnt*n)/N));

   if (rms+rss == 0) {
      if (beta) delete[] beta;
      if (y)    delete[] y;
      if (XP)   delete[] XP;
      if (tval) delete[] tval;
      sprintf(buff,"Error Computing RMS");
      SStat->Results->Lines->Add(buff);

      return;
   }

   r2=1.0 - rss/(rms+rss); /* Numerator is Root Mean Square */
   adjr2=1.-(1.-r2)*(N-1.)/(N-varcnt);

   sprintf(buff,"The regression Coeffients are:");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   for (i=0; i<varcnt; i++) {

      if ( (se * XP[i*(n+1)]) < 0) {
         if (beta) delete[] beta;
         if (y)    delete[] y;
         if (XP)   delete[] XP;
         if (tval) delete[] tval;
         sprintf(buff,"Error computing SQRT se * XP[i*(n+1)]");
         SStat->Results->Lines->Add(buff);
         return;
      }

      serr=sqrt(se * *(XP+i*(n+1)));
      *(tval+i) = *(beta+i)/serr;
      sprintf(buff,"beta[%d]=%15.6g  tvalue=%15.6g  Std Error=%15.6g",
         i,*(beta+i),*(tval+i),serr);
      SStat->Results->Lines->Add(buff);
   }

/* Print out the regression equation information */

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"The Regression Equation is:");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   sprintf(val,"Y = %7.3g ", beta[0]);
   strcat(buff,val);

   for (i=0;i<varcnt-1;i++) {
      sprintf(val,"+ %7.3g * X%d",beta[i+1],varlst[i]+1);
      strcat(buff,val);
   }
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   sprintf(buff,"R-squared: %7.3g   Adjusted R-Squared: %7.3g",r2,adjr2);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

/* Determine if a tvalue is under 2, and which is the smallest */

   for (i=0; i<varcnt; i++) *(tval+i)=fabs(*(tval+i));
   minmax(tval,&min,&max,varcnt-1);
   if (min < 2.0) {
      for (i=0;i<varcnt;i++) {
         if (fabs(*(tval+i) - min) < EPSILON) {
            j = i-1;
            i=varcnt;  /* Escape from loop */
         }
      }
      sprintf(buff,"Recommend deleting X%d from the regression model.",
         varlst[j+1]);
      SStat->Results->Lines->Add(buff);
   }

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   sprintf(buff,"               Analysis of Variance");
   SStat->Results->Lines->Add(buff);

   sprintf(buff,
      "                DF            SS                MS                 F");
   SStat->Results->Lines->Add(buff);

   sprintf(buff,"Regression    %4d    %11.6g      %11.6g       %11.6g",
      varcnt-1, rms, (rms/(varcnt-1)), rms*(N-varcnt)/(rss*(varcnt-1)) );
   SStat->Results->Lines->Add(buff);

   sprintf(buff,"Residual      %4g    %11.6g      %11.6g",
      N-varcnt, rss, rss/(N-varcnt));
   SStat->Results->Lines->Add(buff);


   if (beta) delete[] beta;
   if (y)    delete[] y;
   if (XP)   delete[] XP;
   if (tval) delete[] tval;

}


