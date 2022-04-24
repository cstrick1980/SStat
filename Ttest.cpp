//--------------------------------------------------------------------+
// TTEST - This routine will determine the t-value for the difference  |
//         in means between two variables.                             |
// Called By: tty_stat, wind_stat                                      |
// Input Parameters:                                                   |
// data - a row by col array of data type flow.  Values can change.    |
// row  - is the number of rows in data.                               |
// col  - is the number of columns in data.  Values can change.        |
//                                                                     |
//  2 Feb 92 - Changed data handling from data[] to working.osd        |
// 13 Feb 93 - Added hardcopy option, and void for ANSI compatability  |
//             Took out data[] in memory options.                      |
//======================================================================
//  9 Apr 95 - Started conversion to Windows.
// 11 Oct 97 - Ported to BCB.
// 24 May 98 - Fixed some problems with the variable selection from
//             the input dialog box.
//--------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include "WebStat.h"
#include "mathss.h"
#include "TSSData.h"

//extern float data[];
// extern int row,col;

void Ttest(int x, int y)

{
   register int i;

   char buff[255];

   double SumX;
   double SumY;
   double SumSquaresX;
   double SumSquaresY;
   double meanx;
   double meany;
   double varx;
   double vary;
   double psd;
   double t;
   double n;

   SumX=0;
   SumY=0;
   SumSquaresX=0;
   SumSquaresY=0;

   for ( i=0; i <= SSData->row; i++ ) {

      SumX += SSData->GetData(i,x);
      SumSquaresX +=  SSData->GetData(i,x) *
         SSData->GetData(i,x);

      SumY += SSData->GetData(i,y);
      SumSquaresY += SSData->GetData(i,y) *
         SSData->GetData(i,y);
   }

   n=double (SSData->row+1);
   meanx=SumX/n;
   meany=SumY/n;
   varx=(SumSquaresX-SumX*SumX/n)/(n-1);
   vary=(SumSquaresY-SumY*SumY/n)/(n-1);

   psd = double (sqrt(((n-1)*varx+(n-1)*vary)/((n+n)-2)));
   t=(meanx-meany)/(psd*sqrt(1/n+1/n));

   sprintf(buff,"");
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"The t-value for the comparison of means is: %7.4g",t);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   sprintf(buff,"Variable %d mean %7.4g",x+1,meanx);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   sprintf(buff,"Variable %d mean %7.4g",y+1,meany);
   SStat->Results->Lines->Add(buff);
   sprintf(buff,"");
   sprintf(buff,"With %d degrees of freedom",
      (SSData->row+1)+(SSData->row+1)-2);
   SStat->Results->Lines->Add(buff);
}



