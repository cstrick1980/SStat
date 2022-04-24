//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "SSBar.h"
#include "TSSData.h"
#include "GetPlot.h"
//---------------------------------------------------------------------------
#pragma link "Xyhist"
#pragma resource "*.dfm"
#include "SSScatter.h"

TBarChart *BarChart;

void minmax(double *, double *, double *, int);

//---------------------------------------------------------------------------
__fastcall TBarChart::TBarChart(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TBarChart::BuildBar (void)
{
   int i;
   int xval;
   int yval;

   double x1;
   double x2;
   double y1;
   double y2;

   double *x = new double[MAXROW];
   double *y = new double[MAXROW];


//   BarChart->SSHistogram->Appearance->CaptionFont->Size = 16;
   BarChart->SSHistogram->Appearance->GraphTitle = PlotInput->PlotTitle->Text;
//   BarChart->SSHistogram->Appearance->LabelFont->Size = 10;
   BarChart->SSHistogram->XAxis->Title = PlotInput->XAxisTitle->Text;
   BarChart->SSHistogram->YAxis->Title = PlotInput->YAxisTitle->Text;

   for ( i=0; i<SSData->col; i++ ) {
      if (PlotInput->XValue->Selected[i]) xval = i;
      if (PlotInput->YValue->Selected[i]) yval = i;
   }

//   BarChart->SSHistogram->Series[1]->AllowDuplicates = true;
//   BarChart->SSHistogram->Series[1]->Clear();
//   BarChart->SSHistogram->Series[1]->DrawLine = false;

   for (i=0; i<SSData->row; i++) {
      x[i]= (double) SSData->GetData(i,xval);
      y[i]= (double) SSData->GetData(i,yval);
   }

   minmax(x,&x1,&x2,SSData->row);
   minmax(y,&y1,&y2,SSData->row);

//   BarChart->SSHistogram->XAxis->Min = x1;
//   BarChart->SSHistogram->XAxis->Max = x2;
//   BarChart->SSHistogram->YAxis->Min = y1;
//   BarChart->SSHistogram->YAxis->Max = y2;


//   for (i=0;i<SSData->row;i++){
//      ScatterPlot->xyScatter->Series[1]->ValueAt[x[i]] = y[i];
//      BarChart->hookdataseries(xyScatter[1],false);
//   }

 }