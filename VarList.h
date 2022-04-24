//---------------------------------------------------------------------------
#ifndef VarListH
#define VarListH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TGetVarList : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListXVar;
	TListBox *ListYVar;
	TLabel *Label1;
	TLabel *Label2;
private:	// User declarations
public:		// User declarations
	__fastcall TGetVarList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TGetVarList *GetVarList;
//---------------------------------------------------------------------------
#endif
