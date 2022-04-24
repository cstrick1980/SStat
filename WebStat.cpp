//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "WebStat.h"
#include "TSSData.h"

//---------------------------------------------------------------------------
//USERES("Project1.res");
USEFORM("TSStat.cpp", SStat);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TSStat), &SStat);
	Application->Run();

	return 0;
}