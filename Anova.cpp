/*------------------------------------------------------------------+
| ANOVA - Computes an Analysis of Variance for Equal Sample Sizes   |
|         One Way Classification - Equal Sample Sizes.              |
| Called By:  wind_stat, tty_stat                                   |
| Calls    :  meanstats, midstr, bldstr                             |
+-------------------------------------------------------------------+
| Created 23 Apr 92                                                 |
| 6 Mar 93 - Started adding the ability to parse the model string.  |
|            Also added void def for ANSI compatibility.            |
|18 Mar 93 - Modified the routine to accept only certain variables  |
|            from the command line for the ANOVA.                   |
| 7 Apr 93 - Finally got the variable choice parsing working.       |
|29 Apr 93 - Added a free statement for varstr, was causing memory  |
|            problems when running large programs.                  |
|10 May 93 - Fixed problem with box being too large in some spots.  |
|15 May 93 - Worked on input problem that allows user to input      |
|            null string.                                           |
|23 Jun 93 - Added readln to help fix input problem.                |
|28 Nov 97 - Ported to C++ Builder
+------------------------------------------------------------------*/
/* Need to double check on for's about using <varcnt or <= varcnt */
/* Also may not need to switch y to end of list, like in regr     */

#include <stdlib.h>
#include <stdio.h>
#include "WebStat.h"
#include "TSSData.h"
#include "mathss.h"
#include "TSStat.h"

void meanstats (double *, double *, double *);

void anova(int *varlst, int varcnt)
{

   char buff[255];

   double Ybar;
   double s;
   double ss;
   double ssa;
   double ssr;
   double sst;
   double mean;
   double msa;
   double msr;
   double emt;
   double F;
   double std;

   int dfa;
   int dfr;
   int dft;
   int j;
   int i;

   mathss math;

   double *Means = new double[MAXCOL];
   double *x = new double[MAXCOL];

/* Need to finish this up computing each col mean, var and total */
/* mean and var.                                                 */

   s=0;
   ss=0;

   for (j=0;j<varcnt;j++){
      for (i=0; i<SSData->row; i++) {
	     x[i] = SSData->GetData(i,varlst[j]);
         s=s + x[i];
         ss=ss + x[i] * x[i];
      }
      meanstats (x, &mean, &std);
      Means[j] = mean;
   }

   Ybar=s/((SSData->row + 1)*(varcnt + 1));

   ssa=0;
   ssr=0;
   sst=0;

   for(i=0;i<varcnt;i++) {
      ssa=ssa + ( Means[i] - Ybar) * ( Means[i] - Ybar);
   }

   ssa=(SSData->row + 1) * ssa;      /* Sum of Squares           */
   dfa=varcnt;                       /* Degrees of Freedom for a */
   msa=ssa/dfa;                      /* Mean Square              */

   for (j=0;j<varcnt;j++)
      for (i=0; i<=SSData->row; i++){
	   ssr=ssr + (SSData->GetData(i,(varlst[j]-1))
	    - Means[j] ) * (SSData->GetData(i,(varlst[j]-1))
        - Means[j] );
       }

   dfr=(varcnt+1) * SSData->row;
   msr=ssr/dfr;

   emt=msr+ssa/varcnt;                  /* Expected Mean Square */
   F=msa/msr;

   for(i=0; i<varcnt; i++)
      for(j=0; j<=SSData->row; j++){
   	     sst=sst + (SSData->GetData(j,(varlst[i]-1)) - Ybar)
	        * (SSData->GetData(j,(varlst[i]-1)) - Ybar);
      }

   dft=(varcnt+1) * (SSData->row + 1)-1;

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"            ONE-WAY ANALYSIS OF VARIANCE (EQUAL SAMPLE SIZES)");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,
      "     +---------------------------------------------------------------+");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"     | Source of       SS      df      MS        EMS    Computed F   |");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"     | Variation                                                     |");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,
      "     +---------------------------------------------------------------+");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"     | Due to      %7.4e %3d  %7.4e  %7.4e  %7.4e|",
           ssa,dfa,msa,emt,F);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"     | Treatment                                                     |");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"     |                                                               |");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,
      "     | Residual    %7.4e %3d %7.4e                        |",
         ssr,dfr,msr);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,
      "     +---------------------------------------------------------------+");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,
      "     | Total       %7.4e %3d                                   |",
         sst,dft);
   SStat->Results->Lines->Add(buff);
   printf("     +---------------------------------------------------------------+");

   if (Means) delete [] Means;
   if (x) delete [] x;
}

