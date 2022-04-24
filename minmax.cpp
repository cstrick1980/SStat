/*--------------------------------------------------------------------+
| MINMAX - Returns the Max/Min values in an array.                    |
| Called by: stats, regr                                              |                                                           |
|                                                                     |
| 14 Jun 92 - Extracted from Stats.                                   |
| 13 Aug 92 - Changed the floats to doubles.                          |
|  5 Jul 97 - Convert to C++, using C++ Builder.                      |
+--------------------------------------------------------------------*/

void minmax (double *x, double *min, double *max, int row)
{
   double hold,val;
   int i;

/*-------------------------------------------*/
#ifdef DEBUG
   printf("MINMAX: Entering minmax\n");
#endif
/*-------------------------------------------*/
   hold=*x;

   *min=hold;

   *max=hold;

   for(i=0;i<row;i++) {
      val=*(x+i);
      if(val<*min) *min=val;
      if(val>*max) *max=val;
   }

/*-------------------------------------------*/
#ifdef DEBUG
   printf("MINMAX: Exiting minmax\n");
#endif
/*-------------------------------------------*/
}

