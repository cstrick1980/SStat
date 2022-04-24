//---------------------------------------------------------------------------
#ifndef SSGetSingleListH
#define SSGetSingleListH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TGetSingleList : public TForm
{
__published:	// IDE-managed Components
	TListBox *VarList;
	TLabel *Label1;
	TButton *IDOk;
	TButton *IDCancel;
private:	// User declarations
public:		// User declarations
	__fastcall TGetSingleList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TGetSingleList *GetSingleList;
//---------------------------------------------------------------------------
#endif
