/*-----------------------------------------------------------+
| DOMODE - Computes the first mode in an array.              |
| CREATED: 19 Jun 93                                         |
| CALLED : stats.c                                           |
|                                                            |
| 24 Jun 93 - Added actual code to do mode, instead of being |
|             a stub program.                                |
| 24 May 98 - Ported to BCB.                                 |
+-----------------------------------------------------------*/

double domode(double *x, int row)
{
   double mode,omode;
   int count,ocount,i;
   register int j;

   omode=0;
   ocount=0;

   /* Loop through each value to get counts */

   for (i=0;i<=row;i++){
      mode = *(x+i);
      count=1;

      /* Loop through starting at next value and count matches */

      for(j=i+1;j<row;++j) {/* If match, increment count */
         if(mode == *(x+j)) count++;

      }

      if(count > ocount) {  /* If largest count, get new mode, count */
         omode=mode;
         ocount=count;
      }
   }
   return omode;
}



