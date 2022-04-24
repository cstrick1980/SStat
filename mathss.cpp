//-------------------------------------------------------------------------
//  CLASS     : mathss.cpp                                                                                                                                 |
//              This class provides the calls to the mathematical functions
//
//  Created   : 11 Feb 96
//-------------------------------------------------------------------------


#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TSSData.h"
#include "mathss.h"

mathss::mathss(void)
{
}

//------------------------------------------------------------------------
//  METHOD: mathss::add                                                                                                                                  |
//           This method will add a scalar to a vector.
//------------------------------------------------------------------------

void mathss::add(int c, float dnum)
{
  int i;

   for (i=0;i<=SSData->row;i++) {
      SSData->PutData(SSData->GetData(i,c) + dnum, i, c);
   }

}
//-------------------------------------------------------------------+
// PROGRAM: div.c - This program will subtract a scalar from a vector.|
//-------------------------------------------------------------------*/

void mathss::divide(int c, float dnum)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData(SSData->GetData(i,c)/dnum,i,c);
}


//-------------------------------------------------------------------+
// PROGRAM: mult.c                                                   |
//                                                                   |
// This program will subtract a scalar from a vector.                |
//------------------------------------------------------------------*/

void mathss::mult(int c, float dnum)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData(SSData->GetData(i,c) * dnum,i,c);
}

//----------------------------------------------------------------
// METHOD: MATHSS::SUBT - This method will subtract a scalar from
//                        a vector.
//-------------------------------------------------------------

void mathss::subt(int c, float dnum)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData(SSData->GetData(i,c) - dnum,i,c);
}

//-------------------------------------------------------------
// Math -function calls
//-------------------------------------------------------------

void mathss::fabs(int c)
{
   register int i;
   for (i=0;i<=SSData->row;i++)
      if (SSData->GetData(i,c) < 0)
         SSData->PutData(SSData->GetData(i,c)*-1,i,c);
}

void mathss::count(float increment)
{

   float HighVal = 0;

   SSData->col++;

   for (int i = 0; i<=SSData->row;i++) {
      HighVal = HighVal+increment;
      SSData->PutData(HighVal, i, SSData->col); \
   }
}

void mathss::fexp(int c)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData((float) exp ((double) SSData->GetData(i,c)),i,c);

}

void mathss::fint(int c)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData((float) ceil ((double) SSData->GetData(i,c)),i,c);
}

void mathss::flog(int c)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData(log ((double) SSData->GetData(i,c)),i,c);
}

void mathss::fpow(int c, float dnum)
{
   register int i;
   float tmpval;

   for (i=0;i<=SSData->row;i++) {
      tmpval=SSData->GetData(i,c);
      tmpval = tmpval*tmpval;
      SSData->PutData(tmpval,i,c);
   }
}

void mathss::fsign(int c)
{
   register int i;
   float tmpval;

   for (i=0;i<=SSData->row;i++) {
      tmpval=SSData->GetData(i,c);
      if ( tmpval > 0)
         tmpval = 1.0;
      else
         if ( tmpval < 0)
            tmpval = -1.0;
         else tmpval = 0;
      SSData->PutData(tmpval, i, c);
   }
}

void mathss::fsqrt(int c)
{
   register int i;

   float tmpval;

   for (i=0;i<=SSData->row;i++) {
      tmpval=SSData->GetData(i,c);
      if ( tmpval >= 0)
         tmpval = sqrt(tmpval);
      else
         tmpval = -1114113;
      SSData->PutData(tmpval, i,c);
   }
}

//-------------------------------------------------------------
// Trig - function calls
//-------------------------------------------------------------

void mathss::facos(int c)
{
   for (int i=0;i<=SSData->row;i++)
      SSData->PutData(acos(SSData->GetData(i,c)),i,c);
}

void mathss::fasin(int c)
{
   for (int i=0;i<=SSData->row;i++)
      SSData->PutData(asin(SSData->GetData(i,c)),i,c);
}

void mathss::fatan(int c)
{
   for (int i=0;i<=SSData->row;i++)
      SSData->PutData(atan(SSData->GetData(i,c)),i,c);
}


void mathss::fcos(int c)
{
   register int i;

   for (i=0;i<=SSData->row;i++)
      SSData->PutData(cos(SSData->GetData(i,c)),i,c);
}

void mathss::fsin(int c)
{
   for (int i=0;i<=SSData->row;i++)
      SSData->PutData(sin(SSData->GetData(i,c)),i,c);
}

void mathss::ftan(int c)
{
   for (int i=0;i<=SSData->row;i++)
         SSData->PutData(tan(SSData->GetData(i,c)),i,c);
}

void mathss::Urand(float max)
{

   void randomize(void);
   int random(int);

   SSData->col++;

   randomize();
   for (int i=0;i<=SSData->row;i++)
      SSData->PutData(random(max),i,SSData->col);
}

void mathss::Unorm(float mean, float std)
{

   void randomize(void);
   int random(int);

   double Un1;
   double Un2;
   double pi;
   float NormNum;

   SSData->col++;

   pi = 4 * atan(1);
   randomize();
   for (int i=0;i<=SSData->row;i++) {
      Un1 = ( double ( random(1000) ) + 1 ) /1000;
      Un2 = ( double ( random(1000) ) + 1 ) /1000;

      double x = -2.0 * log (Un1);
      double y = cos ( 2.0 * pi * Un2);

      if ( x < 0 ) x = 0;

      NormNum = sqrt ( x ) * y;

      NormNum = NormNum * std + mean;

      SSData->PutData( (float) NormNum ,i,SSData->col);
  }
}

//------------------------

void mathss::setdim(int rowcnt, int colcnt)
{
   cout << "Enter setdim\n";
   SSData->row=rowcnt;
   SSData->col=colcnt;
}

mathss::~mathss(void)
{
}




