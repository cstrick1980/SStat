/*----------------------------------------------------------------
| PROGRAM: borderinv.cpp                                         |
| Inverts a symmetric Matrix by the border method.               |
|                                                                |
| 29 Apr 91 - Modified the routine to handle col as an external  |
|             variable                                           |
|  9 Jun 91 - Fixed XP and V to work as pointer.                 |
|  1 Feb 92 - Changed <os9stat.h> to "os9stat.h"                 |
|  2 Feb 92 - Changed method of getting row,col info to file.    |
| 25 May 92 - Modified the array size from col to varcnt because |
|             of the use of bldstr to build XP                   |
|  5 Jul 97 - Converted to C++, using C++ Builder                |
+---------------------------------------------------------------*/

#include "WebStat.h"
#include "TSSData.h"
void borderinv (double *XP,int varcnt)
{
   double *V;
   int i;
   int j,k,l,m,n;

#ifdef DEBUG
   printf("BORDERINV: Enter borderinv\n");
   fprintf(stderr,"BORDERINV: varcnt=%d\n",varcnt);
#endif

   n=varcnt+1;  /* End of row in matrix XP[2,1]=XP[1+2*n]*/

   V = new double[MAXCOL];

   *XP = 1.0 / *XP;

   for (k=1; k<varcnt;k++) {
      for (i=0; i<=k; i++)
         V[i]=0.0;
      m=k-1;

      for (i=0; i<=m; i++) {
         for (j=0; j<=i; j++)
            V[i] = V[i] + *(XP+j+i*n) * *(XP+j+k*n);
         if (i != m) {
            l=i+1;
            for (j=l; j<=m; j++)
               *(V+i) = *(V+i) + *(XP+i+j*n) * *(XP+j+k*n);
         }
      }

      for (j=0; j<=m; j++)
         *(V+k) = *(V+k) + *(XP+j+k*n) * *(V+j);
      *(XP+k+k*n) = 1.0/(*(XP+k+k*n) - *(V+k));

      for (j=0; j<=m; j++) {
         for (i=0; i<=j; i++)
            *(XP+i+j*n) = *(XP+i+j*n) + *(XP+k+k*n) * *(V+i) * *(V+j);
      }

      for (i=0; i<=m; i++)
         *(XP+i+k*n) = - *(XP+k+k*n) * *(V+i);
   }

   if (V) delete[] V;

#ifdef DEBUG
   fprintf(stderr,"BORDERINV: Exit borderinv\n");
#endif
}

