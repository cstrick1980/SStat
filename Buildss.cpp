/*----------------------------------------------------------------+
| PROGRAM: BuildSS.cpp                                            |
| This routine builds X'X, X'y and SSy.                           |
| Calls: bldstr, rarray, midstr                                   |
| Called By: regr                                                 |
|                                                                 |
| 29 Apr 91 - Modified to handle data,row,col as global variables |
|  9 Jun 91 - Modified XP to work as a pointer.                   |
|  1 Feb 92 - Changed <os9stat.h> to "os9stat.h"                  |
|  2 Feb 92 - Changed method of using data[] to file working.osd  |
| 24 Apr 92 - Add the ability to use a selected set of values for |
|             the regression choice (ex: 5 3 7 - 11 15 . ).       |
|             Took out the MM1 def's, will handle all arrrays in  |
|             the dataarray routine (including in memory).        |
| 31 May 92 - Changed varlst to a ptr so the result could be      |
|             passed back to the calling routine.                 |
| 30 Dec 92 - Used malloc to allocate memory for varstr, also     |
|             added routine name to error messages, along with    |
|             using fprintf(stderr )                              |
|  6 Mar 93   Added void for ANSI compatibility.                  |
| 10 May 93   Fixed the example shown for the regression string.  |
| 17 May 93   Added fflush(0),fflush(1) to clear up some I/O      |
|             buffer problems.                                    |
| 23 Jun 93   Added readln, hope to fixed input string problem.   |
| 26 Jun 93   Took out the fflush, and readln, put gets back in   |
|             having trouble getting the input line correctly.    |
| 25 Jul 93   MAJOR MOD:  Moved the bldstr, and varcnt to regr so |
|             XP would only be allocated when needed.  Including  |
|             all code that dealt with these routines.            |
|  5 Jul 97   Converted over to C++, with C++ Builder.            |
+----------------------------------------------------------------*/

#include "WebStat.h"
#include "TSSData.h"
#include "mathss.h"

void buildss (double *XP, int varcnt, int *varlist)
{
   double *x;
   int i,j,k,n;

   n=varcnt+1;

   x = new double[MAXCOL];
   for (i=0;i<MAXCOL;i++) x[i]=0;

   x[0]=1; /* setup the column of 1's for your intercept */

   for(k=0; k<=SSData->row; k++){
      for(i=1;i<n;i++){                  /* Get only the variables */
         x[i] = (double) SSData->GetData(k,varlist[(i-1)]);
      }
      for(i=0;i<n;i++){
         for(j=i;j<n;j++){
            XP[i+(j*n)] = XP[i+(j*n)] + x[i] * x[j];
         }
      }
   }
   if (x) delete[] x;

}

