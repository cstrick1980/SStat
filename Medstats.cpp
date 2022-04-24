/*------------------------------------------------------------------+
| MEDIANSTATS - Compute the median of a data element                |
|                                                                   |
|29 Apr 91 - Modified the routine to handle row as a global         |
|            variable.                                              |
|27 Dec 91 - Changed <os9stat.h> to "os9stat.h".  Fixed the         |
|            interquartile range to the correct value.              |
| 2 Feb 92 - Changed method of data[] to working.osd                |
| 6 Oct 92 - Fixed some problems with the range and made iq the     |
|            proper value.  Added the selection of the mode.        |
|19 Jun 93 - Removed the mode calucation and made it a separate     |
|            routine.                                               |
|24 May 98 - Ported to BCB.                                         |
+------------------------------------------------------------------*/

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#include <math.h>
#include "TSSData.h"
#include "mathss.h"

void heapsort( double *, int);

void medianstats (double *x, double *median, double *iq, double *range)
{
   int aptr;
   int EVEN;
   int uq;
   int lq;
   int ROW;

   EVEN=FALSE;

   ROW=SSData->row;

   if (((ROW/2) - floor(ROW/2))==0) EVEN=TRUE;

   heapsort(x,SSData->row);

   if (EVEN) {
      aptr=ROW/2;
      *median=(*(x+aptr) + *(x+(aptr-1)))/2;
   }
   else {
      aptr=(ROW-1)/2;
      *median=*(x+aptr);
   }

   *range=*(x+SSData->row) - *x;

   if (*range < 0) *range=-*range;
   if (ROW <=4) *iq=*range;
   else {
      lq=floor(ROW*.25);             /* Round Down */
      uq=floor((ROW+.5)-lq);         /* Round Up   */
      *iq=*(x+uq)-*(x+lq);

   }
}



