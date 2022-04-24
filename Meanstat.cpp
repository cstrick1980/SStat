/*------------------------------------------------------------------------+
| PROGRAM: meanstats                                                      |
| Compute the mean and standard deviation of a data array                 |
| Called by: stats, anova                                                 |
| Returns -1 on error, 0 otherwise.                                       |
| Entry Variables: x    - contains the data array                         |
| Exit Variables : mean - the mean of x                                   |
|                : std  - the std of x                                    |
|-------------------------------------------------------------------------|
| 29 Apr 91 - Modified the routine to handle row as a global variable.    |
|  2 Feb 92 - Changed method of data handling from data[] to working.osd  |
| 25 Apr 92 - Added an error check (44) on the sqrt function to keep it   |
|             from bombing out with error 44.                             |
|  9 Aug 92 - Changed the input, output parameters to double.             |
| 23 Jul 95 - Ported to C++ under Windows.                                |
| 28 Nov 97 - Ported to C++ Builder.                                      |                               |
+------------------------------------------------------------------------*/

#include <math.h>
#include "TSSData.h"
#include "mathss.h"

// extern int row;

void meanstats (double *x, double *mean, double *std)
{

   double sx;
   double ssx;
   int i;

   sx=0;
   ssx=0;
   for (i=0; i<=SSData->row; i++) {
      sx=sx + *(x+i);
      ssx=ssx + *(x+i) * *(x+i);
   }

   *mean=sx/(SSData->row+1);
   *std=sqrt((ssx - sx*sx/(SSData->row+1))/SSData->row);
}

