//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include "TSSData.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USERES("SimpleStat.res");
USEUNIT("Bordinv.cpp");
USEUNIT("Buildss.cpp");
USEUNIT("Listdata.cpp");
USEUNIT("mathss.cpp");
USEUNIT("Meanstat.cpp");
USEUNIT("minmax.cpp");
USEUNIT("Readfile.cpp");
USEUNIT("Regr.cpp");
USEUNIT("TSSData.cpp");
USEUNIT("Ttest.cpp");
USEUNIT("Anova.cpp");
USEUNIT("Medstats.cpp");
USEUNIT("Heapsort.cpp");
USEUNIT("Stats.cpp");
USEUNIT("Domode.cpp");
USEFORM("GetPlot.cpp", PlotInput);
USEFORM("SSScatter.cpp", ScatterPlot);
USEFORM("SSGetVarList.cpp", GetVarList);
USEFORM("SSMathEntry.cpp", MathEntry);
USEFORM("SSBar.cpp", BarChart);
USEFORM("SSAbout.cpp", AboutBox);
USEFORM("TSStat.cpp", SStat);
USEFORM("SSGetSingleList.cpp", GetSingleList);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	try
	{
		Application->Initialize();
		Application->Title = "Simple Stat";
		Application->CreateForm(__classid(TSStat), &SStat);
		Application->CreateForm(__classid(TPlotInput), &PlotInput);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TScatterPlot), &ScatterPlot);
		Application->CreateForm(__classid(TGetVarList), &GetVarList);
		Application->CreateForm(__classid(TMathEntry), &MathEntry);
		Application->CreateForm(__classid(TBarChart), &BarChart);
		Application->CreateForm(__classid(TGetSingleList), &GetSingleList);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
