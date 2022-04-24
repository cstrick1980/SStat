//-------------------------------------------------------------+
//  PROGRAMMER: Chris Strickland                               |
//              New Horizons Software (c) 1997                 |
//  PROGRAM:    SSScatter.cpp                                  |
//                                                             |
//  This routine produces an XY Scatter Plot.                  |
//  It replaces the splot.c and plot.c routines                |
//  Creation Date: 25 Oct 92                                   |
//  15 Dec 92 - Added the ability to enter a title line.       |
//  23 Jan 93 - Fixed problems with title be truncated.        |
//  24 Jan 93 - Noted problem with passing of x array          |
//              Also changed from 20 to 18 rows.               |
// 6-7 Feb 93 - Continued working on x & y axis titles.        |
//10-12Feb 93 - Fixed problem with scaling of data to the x&y  |
//              axises                                         |
//13-14Feb 93 - Worked on printing Varible along y-axis.  Had  |
//              problems                                       |
//              with const char assignment.                    |
//15-19Feb 93 - Finished getting the variable number input into|
//              the yvariable title.                           |
//   5 Jun 93 - Added *, + ^ for values >9, >24, >49           |
//  23 Jun 93 - Moved title to splot, to save user wait.       |
//  22 Jul 97 - Ported both splot and plot over to SSScatter   |
//              under C++ Builder.                             |
//  22 Mar 98 - Added BuildPlot and GetValues to the SSScatter |
//              class.
//-------------------------------------------------------------+
#include <vcl\vcl.h>
#pragma hdrstop

#include "SSScatter.h"
#include "GetPlot.h"
#include "mathss.h"
#include "TSSData.h"

void minmax(double *, double *, double *, int);

//----------------------------------------------------------------------
#pragma link "TVerticalLabel"
#pragma link "xyGraph"
#pragma resource "*.dfm"

TScatterPlot *ScatterPlot;
//----------------------------------------------------------------------
__fastcall TScatterPlot::TScatterPlot(TComponent* Owner)
	: TForm(Owner)
{
}
//----------------------------------------------------------------------

void TScatterPlot::InsertVariables(void)
{
   char val[10];
   int i;

   if (SSData->col > 0) {
      PlotInput->XValue->Items->Clear();
      PlotInput->YValue->Items->Clear();
      for (i=0;i<=SSData->col;i++) {
         sprintf(val,"Var %d",i+1);
         PlotInput->XValue->Items->Insert(i,val);
         PlotInput->YValue->Items->Insert(i,val);
      }
   }
}
//----------------------------------------------------------------------

void TScatterPlot::BuildPlot(void)
{
   double x1;
   double x2;
   double y1;
   double y2;

   int i;
   int xval;
   int yval;

   double *x = new double[MAXROW];
   double *y = new double[MAXROW];

   ScatterPlot->xyScatter->Appearance->CaptionFont->Size = 16;
   ScatterPlot->xyScatter->Appearance->GraphTitle = PlotInput->PlotTitle->Text;
   ScatterPlot->xyScatter->Appearance->LabelFont->Size = 10;
   ScatterPlot->xyScatter->XAxis->Title = PlotInput->XAxisTitle->Text;
   ScatterPlot->xyScatter->YAxis->Title = PlotInput->YAxisTitle->Text;

   for (i=0;i<SSData->col;i++) {
      if (PlotInput->XValue->Selected[i]) xval = i;
      if (PlotInput->YValue->Selected[i]) yval = i;
   }

   ScatterPlot->xyScatter->Series[1]->AllowDuplicates = true;
   ScatterPlot->xyScatter->Series[1]->Clear();
   ScatterPlot->xyScatter->Series[1]->DrawLine = false;

   for (i=0;i<MAXROW;i++) {
      x[i]=0;
      y[i]=0;
   }

   for (i=0; i<SSData->row; i++) {
      x[i]= (double) SSData->GetData(i,xval);
      y[i]= (double) SSData->GetData(i,yval);
   }

   minmax(x,&x1,&x2,SSData->row);
   minmax(y,&y1,&y2,SSData->row);

   ScatterPlot->xyScatter->XAxis->Min = x1;
   ScatterPlot->xyScatter->XAxis->Max = x2;
   ScatterPlot->xyScatter->YAxis->Min = y1;
   ScatterPlot->xyScatter->YAxis->Max = y2;


   for (i=0;i<SSData->row;i++)
      ScatterPlot->xyScatter->Series[1]->ValueAt[x[i]] = y[i];
}
