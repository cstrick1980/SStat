//---------------------------------------------------------------------------
#ifndef SSMathEntryH
#define SSMathEntryH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TMathEntry : public TForm
{
__published:	// IDE-managed Components
	TLabel *EntVar;
	TEdit *VarVal;
	TLabel *EntVal;
	TEdit *NumVal;
	TButton *IsOk;
	TButton *IsCancel;
private:	// User declarations
public:		// User declarations
	__fastcall TMathEntry(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMathEntry *MathEntry;
//---------------------------------------------------------------------------
#endif
