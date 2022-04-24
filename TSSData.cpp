//--------------------------------------------------------------
//  PROGRAMMER: Chris Strickland                               |
//              New Horizons Software (c) 1997                 |
//  PROGRAM:    TSSData.cpp                                    |
//                                                             |
//  This routine replaces the global variables and array used  |
//  by Simple Stat.  It contains all methods required for      |
//  accessing the data arrays.                                 |
//--------------------------------------------------------------

#include <vcl\vcl.h>
#pragma hdrstop

#include "TSSData.h"

TSSData::TSSData(void)
{
   row=0;
   col=0;
};

float TSSData::GetData(int i, int j)
{
   float value = data [i][j];
   return value;
};

void TSSData::PutData(float value, int i, int j)
{
   data[i][j] = value;

};

TSSData::~TSSData(){};
//---------------------------------------------------------------------------
