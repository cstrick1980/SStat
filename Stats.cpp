/*--------------------------------------------------------------------+
| STATS - This routine prints out statistical information on each of  |
| the variables loaded into os9stat.                                  |
| Called by: wind_stat, tty_stat                                      |
| Calls    : minmax, meanstats, medianstats                           |
|---------------------------------------------------------------------|
| 29 Apr 91 - Modified the routine to handle data,row,col as globals. |
|  5 Jan 92 - Changed <os9stat.h> to "os9stat.h"                      |
|  2 Jan 92 - Changed data handling from data[] to working.osd        |
| 14 Jun 92 - Extracted minmax into a separate routine.               |
|  9 Aug 92 - Changed mean, std, *x from float to double,to handle    |
|             the new call to meanstats from anova.c                  |
|  6 Oct 92 - Added the mode as one of the output items.              |
| 13 Feb 93 - Added hardcopy option, added void for ANSI.             |
| 11 Mar 93 - Added the row and col counts to the information printout|
| 23 Jun 93 - Made mode an separate function to domode.c              |
| 24 May 98 - Ported to BCB.                                          |
+--------------------------------------------------------------------*/

#include <stdio.h>
#include "WebStat.h"
#include "TSSData.h"

double domode(double *, int);
void minmax(double *, double *, double *, int);
void medianstats(double *,double *, double *, double *);
void meanstats(double *, double *, double *);

void stats(int *varlist, int varcnt)
{
   double mean;
   double std;
   double max;
   double min;
   double median;
   double iq;
   double range;
   double mode;

   char buff[255];

   int j;
   int i;

   double *x = new double[MAXROW];

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);

   sprintf(buff,"                         Statistical Information");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"NOTE: Mode is first mode found, there may be multiple modes");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"Total Observations=%d  Total Variables=%d",
      SSData->row+1, SSData->col+1);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"%-8s%-7s%-7s%-7s%-7s%-7s%-7s%-10s%-10s",
      "Var","Min","Max","Median","IQ","Range","Mode","Mean","Std Dev");
   SStat->Results->Lines->Add(buff);

   for(j=0;j<varcnt;j++) {
      for(i=0;i<=SSData->row;i++) x[i]=SSData->GetData(i,varlist[j]);

      minmax(x,&min,&max,SSData->row);
      medianstats(x,&median,&iq,&range);
      meanstats(x,&mean,&std);
      mode = domode(x,SSData->row);

      sprintf(buff,"Var%-2.2d%7.3g%7.3g%7.3g%7.3g%7.3g%7.3g   %7.3g   %7.3g",
         varlist[j]+1,min,max,median,iq,range,mode,mean,std);
      SStat->Results->Lines->Add(buff);
   }

   if  (x) delete[] x;

}



