//------------------------------------------------------------------------+
//  PROGRAMMER: Chris Strickland                                          |
//              New Horizons Software (c) 1991,1992,1994                  |
//  PROGRAM:    SStat.cpp                                                 |
//                                                                        |
//  This is the driver module for SStat, formally copyrighted under the   |
//  name OS9STAT, this is the version ported to run under a windows       |
//  environment and is still under the copyright provisions of OS9Stat.   |
//                                                                        |
//  WINSTAT is not public domain software.                                |
//                                                                        |
//  Version 1.x.x is freely copyable.         ALPHA Version               |
//  Version 2.x.x is shareware.               BETA Version                |
//  Version 3.x.x and up will be commercial.  Commerical Version          |
//                                                                        |
//       The following terms are agreed to upon useage of this software:  |
//       1)  All references to the original author: Chris Strickland      |
//           will be left in the original software.                       |
//       2)  Version 1.x.x will not be sold for a profit.                 |
//       3)  Suggested changes be provided to Chris Strickland for future |
//           releases.                                                    |
//                                                                        |
//  EMAIL: cstrick@iu.net                                                 |
//========================================================================|
//  Modification History:                                                 |
//  PROGRAMMER: Chris Strickland                                          |
//                                                                        |
// 29 Apr 91 - Modified the way the parameters are passed to the os9stat  |
//              commands routines.  I also made data,row & col global     |
//              parameters.                                               |
//                                                                        |
//  24 Nov 91 - Added the following routines to OS9STAT                   |
//              ttest.c                                                   |
//                                                                        |
//  21 Dec 91 - Added the following routines to OS9STAT                   |
//              freq.c, corr.c                                            |
//                                                                        |
//  27 Dec 91 - Fixed the sign routine, was call then sin routine, and    |
//              sort.  Added: div.c mult.c, subt.c,del.c                  |
//              Changed <os9stat.h> to "os9stat.h"                        |
//------------------------------------------------------------------------|
//            5 Jan 91 - UPLOADED VERSION 1.3.0 OF OS9STAT                |
//------------------------------------------------------------------------|
//  26 Jan 92 - Up'ed MAXROW to 500 from 100 due to problems THIB on      |
//              Delphi was having with one of his data sets.              |
//              Also started splitting up start_stat to tty_stat and      |
//              wind_stat so I could get windows working under OS9        |
//   2 Feb 92 - Changed the way the data[] is handled from an array to a  |
//              direct access data file.                                  |
//  24 Apr 92 - Fixed up the regression routines to allow passing only the|
//              variables to do the regression on.                        |
//              Also wrote an ANOVA routine, need to implement it.        |
//   6 Sep 92 - Added the getenv routine to allow auto startup of window  |
//              types.                                                    |
//  17 Sep 92 - Added the ability to pass command line files the this     |
//              program, so the user can override the window type in      |
//              env.file.                                                 |
//   6 Oct 92 - Added the get arg options to start_stat so the user can   |
//              control the terminal environment.                         |
//------------------------------------------------------------------------|
// Below are the comments from the tty_stat.c module which are now being  |
// merged with WINDSTAT, since windows is not limited by the 64K memory   |
// boundaries of OS9 Level II (6809).                                     |
//------------------------------------------------------------------------+
//  PROGRAMMER: Chris Strickland                                          |
//              New Horizons Software (c) 1991                            |
//  PROGRAM:    tty_stat.c - Top Level driver for tty interface.          |
//                                                                        |
//   2 Feb 92 - Changed the data[] to read from a disk workfile.          |
//  26 Apr 92 - Took out all of the ifdefs for MM1, let the diskarray     |
//              handle whether used by memory, or read from disk.         |
//  11 Jun 92 - Modified the prompt to have an extra LF, for when         |
//              input is entered all at once.                             |
//  30 Jun 92 - Change the strncmp(command to strncmp(&command[0] in      |
//             in hopes to fix the stack errors I'm getting.              |
//   6 Sep 92 - Added, the GUI variable to determine if in windows        |
//              mode.  Added the cd and pwd commands.                     |
//  24 Oct 92 - Added count command.                                      |
//  25 Oct 92 - Added splot command.                                      |
//   9 Nov 92 - Modified the calls to Mathfunc to be an external call     |
//  20 Feb 93 - Made changes to add #ifdef BIG, for future ports to       |
//              OS's allowing more than 64k.  Also moved add, div, mul    |
//              and div to mathfunc utility.                              |
//  22 Mar 93 - Coverted command[80], pathname[80] to *command,*pathname. |
//  16 Apr 93 - Modified os9forks to pass pathname as a parameter so      |
//              mathfunc would know where working.os9 is.                 |
//  25 Apr 93 - Added error checking capabilities for the mallocs on      |
//              command, pathname, and parmval.                           |
//9-12 May 93 - Modified all os9fork calls to close working.os9 and       |
//              reopen after return.  Did this by creating a fake         |
//              mathfunc subroutine.                                      |
//  30 May 93 - Changed debug printf to fprintf.                          |
//   1 Jun 93 - Added the ability to pass the rest of the command line    |
//              entries to mathfunc.                                      |
//   9 Jun 93 - Took out the close/open on before calls mathfunc.         |
//  29 Jun 93 - Added the inv function.                                   |
//  10 Jul 93 - Moved, freq and rand to external mathfunc, also moved     |
//              a FILEOPEN check to the internal mathfunc.                |
//-----------------------------------------------------------------------*/
//                    START OF WINDOWS Version                            /
//                       Version 2.0                                      /
//------------------------------------------------------------------------|
//  28 Dec 94 - Started the port from OS9 C to Borland Visual C++ under   /
//              windows                                                   /
//  16 Jul 95 - Added the TInputDialog input inside this driver for the   /
//              mathematical functions.                                   /
//  11 Feb 96 - Started converting the mathematical functions over to     /
//              the MATHSS class                                          /
//-----------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#include <vcl\vcl.h>

#pragma hdrstop

#include <new.h>
#include "TSStat.h"
#include "SSAbout.h"
#include "SSMathEntry.h"
#include "TSSData.h"
#include "mathss.h"
#include "SSGetVarList.h"
#include "SSGetSingleList.h"
#include "SSScatter.h"
#include "SSBar.h"
#include "GetPlot.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"

// External Functions

int ReadData(char *filename);
int ListData();

// Global Variables

TSSData *SSData;
TSStat *SStat;

//---------------------------------------------------------------------------
__fastcall TSStat::TSStat(TComponent* Owner)
	: TForm(Owner)
{
   SSData = new TSSData;
   set_new_handler(0);
}
//---------------------------------------------------------------------------
void __fastcall TSStat::FileExitClick(TObject *Sender)
{
   if (SSData) delete SSData;
   Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TSStat::FileOpen(TObject *Sender)
{
   int errchk;

   OpenDialog->FileName = "";
   if (OpenDialog->Execute())
      errchk = ReadData(OpenDialog->FileName.c_str());
      if ( errchk !=0 ) cout << "Error Reading File";
   }
//---------------------------------------------------------------------------
void __fastcall TSStat::ListClick(TObject *Sender)
{
   int err=ListData();
   if (err !=0) cout << "Error Listing File";
}
//---------------------------------------------------------------------------
void __fastcall TSStat::AddValClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     float dnum=atof(buf);
     math.add(var,dnum);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::About1Click(TObject *Sender)
{
   AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TSStat::DivideValClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     float dnum=atof(buf);
     math.divide(var,dnum);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::MultiplyValClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     float dnum=atof(buf);
     math.mult(var,dnum);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::SubtractValClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     float dnum=atof(buf);
     math.subt(var,dnum);
  }
}

//---------------------------------------------------------------------------
void __fastcall TSStat::Count1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=False;
  MathEntry->VarVal->Visible=False;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     float increment=atof(buf);
     math.count(increment);
  }

}
//---------------------------------------------------------------------------
void __fastcall TSStat::AbsClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fabs(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::Exp1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fexp(var);
  }

}
//---------------------------------------------------------------------------
void __fastcall TSStat::Integer1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fint(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::Logn1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.flog(var);
  }

}
//---------------------------------------------------------------------------
void __fastcall TSStat::Power1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     float dnum=atof(buf);
     math.fpow(var,dnum);
  }

}
//---------------------------------------------------------------------------
void __fastcall TSStat::Regression1Click(TObject *Sender)
{
   int i;
   int j;

   char val[10];
   void regr (int *, int);

   int *varlist = new int[MAXCOL];

   GetVarList->VarYList->Visible=True;
   GetVarList->VarXList->Visible=True;

   for (i=0;i<MAXCOL;i++) varlist[i]=0;

   if (SSData->col > 0) {
      GetVarList->VarXList->Items->Clear();
      GetVarList->VarYList->Items->Clear();
      for (i=0;i<=SSData->col;i++) {
         sprintf(val,"Var %d",i+1);
         GetVarList->VarYList->Items->Insert(i,val);
         GetVarList->VarXList->Items->Insert(i,val);
      }
   }
   GetVarList->ShowModal();
   j=0;
   if (GetVarList->ModalResult == mrOk) {
      for (i=0;i<=SSData->col;i++) {
         if (GetVarList->VarXList->Selected[i]) {
            *(varlist+j)= i;
            j++;
         }
         *(varlist+j) = GetVarList->VarYList->ItemIndex;
      }
      regr(varlist, GetVarList->VarXList->SelCount+1);
   }
   GetVarList->VarXList->Visible = false;
   GetVarList->VarYList->Enabled = true;
   if (varlist) delete[] varlist;
}

//---------------------------------------------------------------------------
void __fastcall TSStat::Scatter1Click(TObject *Sender)
{
   ScatterPlot->InsertVariables();
   PlotInput->ShowModal();
   if (PlotInput->ModalResult == mrOk) {
      ScatterPlot->BuildPlot();
      ScatterPlot->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::Sign1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fsign(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::SqrtClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fsqrt(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::AcosClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.facos(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::AsinClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fasin(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::AtanClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
//     math.setdim(row,col);
     math.fatan(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::CosClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fcos(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::SinClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.fsin(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::TanClick(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=False;
  MathEntry->NumVal->Visible=False;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->VarVal->Text.c_str());
     int var=atoi(buf)-1;
     math.ftan(var);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::ContentsClick(TObject *Sender)
{
   Application->HelpFile = "Ssstat.hlp";
   Application->HelpCommand(HELP_CONTENTS, 0);
}
//---------------------------------------------------------------------------
void __fastcall TSStat::TTestClick(TObject *Sender)
{
   int i;

   char val[10];
   void Ttest (int , int);

   if (SSData->col > 0) {
      GetVarList->VarXList->Items->Clear();
      GetVarList->VarYList->Items->Clear();
      for (i=0;i<SSData->col;i++) {
         sprintf(val,"Var %d",i+1);
         GetVarList->VarYList->Items->Insert(i,val);
         GetVarList->VarXList->Items->Insert(i,val);
      }
   }
   GetVarList->ShowModal();
   if (GetVarList->ModalResult == mrOk) {
      Ttest(GetVarList->VarXList->ItemIndex,
         GetVarList->VarYList->ItemIndex);
   }
   GetVarList->VarXList->Visible = false;
   GetVarList->VarYList->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TSStat::BarClick(TObject *Sender)
{
   ScatterPlot->InsertVariables();
   PlotInput->ShowModal();
   if (PlotInput->ModalResult == mrOk) {
      BarChart->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::AnovaClick(TObject *Sender)
{
   int i;
   int j;

   char val[10];
   void anova (int *, int);

   int *varlist = new int[MAXCOL];
   for (i=0;i<MAXCOL;i++) varlist[i]=0;

   if (SSData->col > 0) {
      GetVarList->VarXList->Items->Clear();
      GetVarList->VarYList->Items->Clear();
      for (i=0; i<=SSData->col; i++) {
         sprintf(val,"Var %d",i+1);
         GetVarList->VarYList->Items->Insert(i,val);
         GetVarList->VarXList->Items->Insert(i,val);
      }
   }
   GetVarList->ShowModal();
   j=0;
   if (GetVarList->ModalResult == mrOk) {
      for (i=0; i<=SSData->col ;i++) {
         if (GetVarList->VarXList->Selected[i]) {
            *(varlist+j)= i;
            j++;
         }
         *(varlist+j) = GetVarList->VarYList->ItemIndex;
      }
      anova(varlist, GetVarList->VarXList->SelCount+1);
   }
   GetVarList->VarXList->Visible = false;
   GetVarList->VarYList->Enabled = true;
   if (varlist) delete[] varlist;

}
//---------------------------------------------------------------------------
void __fastcall TSStat::Stats1Click(TObject *Sender)
{
   char val[10];

   int *varlist = new int[MAXCOL];
   int i;

   void stats (int *, int);

   GetSingleList->VarList->Visible=True;

   for (i=0;i<MAXCOL;i++) varlist[i]=0;

   if (SSData->col > 0) {
      GetSingleList->VarList->Items->Clear();
      for (i=0;i<=SSData->col;i++) {
         sprintf(val,"Var %d",i+1);
         GetSingleList->VarList->Items->Insert(i,val);
      }
   }

   GetSingleList->ShowModal();
   int j=0;

   if (GetSingleList->ModalResult == mrOk) {
      for (i=0;i<=SSData->col;i++) {
         if (GetSingleList->VarList->Selected[i]) {
            varlist[j]= i;
            j++;
         }
         varlist[j] = GetSingleList->VarList->ItemIndex;
      }
      stats(varlist, GetSingleList->VarList->SelCount);
   }

   if (varlist) delete[] varlist;

}
//---------------------------------------------------------------------------
void __fastcall TSStat::Uniform1Click(TObject *Sender)
{
  char buf[32];

  mathss math;

  MathEntry->EntVar->Visible=False;
  MathEntry->VarVal->Visible=False;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf,MathEntry->NumVal->Text.c_str());
     int Max = atoi(buf)-1;
     math.Urand(Max);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSStat::Normal1Click(TObject *Sender)
{
  char buf[32];
  char Label1[32];
  char Label2[32];

  mathss math;

  strcpy(Label1,MathEntry->EntVar->Caption.c_str() );
  strcpy(Label2,MathEntry->EntVal->Caption.c_str() );
  MathEntry->EntVar->Caption = "Enter Mean";
  MathEntry->VarVal->Text="0";
  MathEntry->EntVal->Caption = "Enter Std Dev:";
  MathEntry->NumVal->Text="1";
  MathEntry->EntVar->Visible=True;
  MathEntry->VarVal->Visible=True;
  MathEntry->EntVal->Visible=True;
  MathEntry->NumVal->Visible=True;

  MathEntry->ShowModal();
  if (MathEntry->ModalResult == mrOk) {
     strcpy(buf, MathEntry->VarVal->Text.c_str());
     float mean = atoi(buf)-1;
     strcpy(buf, MathEntry->NumVal->Text.c_str());
     float std = atoi(buf)-1;

     math.Unorm(mean,std);
  }

  MathEntry->EntVar->Caption = Label1;
  MathEntry->VarVal->Text="";
  MathEntry->EntVal->Caption = Label2;
  MathEntry->NumVal->Text="";

}
//---------------------------------------------------------------------------
