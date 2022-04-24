//---------------------------------------------------------------------------
#ifndef SSAboutH
#define SSAboutH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TBevel *Bevel1;
	TLabel *AboutTitle;
	TLabel *VerisonLabel;
	TLabel *CopyrightLabel;
	TBitBtn *BitBtnOk;
	TLabel *CompanyName;
	TLabel *WebLabel;
	TLabel *EmailLabel;
	void __fastcall AboutExitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TAboutBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAboutBox *AboutBox;
//---------------------------------------------------------------------------
#endif
