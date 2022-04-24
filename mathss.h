//-------------------------------------------------------------------------
//  CLASS     : mathss.h                                                                                                                                 |
//              This class provides the calls to the mathematical functions
//  Calls     :
//  Created   : 11 Feb 96
//-------------------------------------------------------------------------


#ifndef MATHSS_H
#define MATHSS_H 1
#include <math.h>
#include <errno.h>

class mathss
{
public:

   mathss(void);

   void setdim (int rowcnt, int colcnt);
   void add    (int colnum, float value);
   void count  (float value);
   void divide (int colnum, float value);
   void mult   (int colnum, float value);
   void subt   (int colnum, float value);

   void fabs   (int colnum);
   void facos  (int colnum);
   void fasin  (int colnum);
   void fatan  (int colnum);
   void fcos   (int colnum);
   void fexp   (int colnum);
   void fint   (int colnum);
   void flog   (int colnum);
   void fpow   (int colnum, float value);
   void fsign  (int colnum);
   void fsin   (int colnum);
   void fsqrt  (int column);
   void ftan   (int colnum);

   void Urand  (float Max);
   void Unorm  (float mean, float std);

   int getrow  (void);
   int getcol  (void);
   void putrow  (int rowval);
   void putcol  (int colval);

   ~mathss(void);
};

#endif
