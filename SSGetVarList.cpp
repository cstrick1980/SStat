//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "SSGetVarList.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TGetVarList *GetVarList;

extern col;
//---------------------------------------------------------------------------
__fastcall TGetVarList::TGetVarList(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------------------------------------------------------------
void __fastcall TGetVarList::VarYListClick(TObject *Sender)
{
   VarXList->Visible = true;
   VarYList->Enabled = false;
}
//---------------------------------------------------------------------------
