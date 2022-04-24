//---------------------------------------------------------------------------
#ifndef SSGetVarListH
#define SSGetVarListH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TGetVarList : public TForm
{
__published:	// IDE-managed Components
	TListBox *VarXList;
	TListBox *VarYList;
	TLabel *YLabel;
	TLabel *XLabel;
	TButton *IDOk;
	TButton *IDCancel;
	void __fastcall VarYListClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TGetVarList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TGetVarList *GetVarList;
//---------------------------------------------------------------------------
#endif
