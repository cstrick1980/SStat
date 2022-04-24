//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "TestData1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
TTestData1 *TestData;
void Unit2(void);
void Unit3(void);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   TestData = new TTestData1;

   TestData->row = 10;
   TestData->col = 25;

   Form1->Edit1->Text=TestData->row;

   Unit2();

   Form1->Edit3->Text=TestData->row;

   Unit3();

   delete TestData;

}
//---------------------------------------------------------------------------