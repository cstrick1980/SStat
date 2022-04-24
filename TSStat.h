//---------------------------------------------------------------------------
#ifndef TSStatH
#define TSStatH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TSStat : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *New1;
	TMenuItem *Open1;
	TMenuItem *List;
	TMenuItem *FileExit;
	TMenuItem *FileMenu;
	TMenuItem *MathMenu;
	TMenuItem *Abs;
	TMenuItem *AddVal;
	TMenuItem *Count1;
	TMenuItem *DivideVal;
	TMenuItem *Exp1;
	TMenuItem *Integer1;
	TMenuItem *Logn1;
	TMenuItem *MultiplyVal;
	TMenuItem *Power1;
	TMenuItem *Sign1;
	TMenuItem *Sqrt;
	TMenuItem *SubtractVal;
	TMenuItem *GraphicsMenu;
	TMenuItem *Scatter1;
	TMenuItem *Bar;
	TMenuItem *StatisticsMenu;
	TMenuItem *Anova;
	TMenuItem *Correlation1;
	TMenuItem *Frequency1;
	TMenuItem *Random1;
	TMenuItem *Regression1;
	TMenuItem *Stats1;
	TMenuItem *TTest1;
	TMenuItem *Normal1;
	TMenuItem *Uniform1;
	TMenuItem *TrigMenu;
	TMenuItem *Acos;
	TMenuItem *Asin;
	TMenuItem *Atan;
	TMenuItem *Cos;
	TMenuItem *Sin;
	TMenuItem *Tan;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TMenuItem *Help1;
	TMenuItem *Contents;
	TMenuItem *About1;
	TMenuItem *Edit1;
	TMenuItem *Replace1;
	TMenuItem *Find1;
	TMenuItem *PasteSpecial1;
	TMenuItem *Paste1;
	TMenuItem *Copy1;
	TMenuItem *Cut1;
	TMenuItem *Repeatcommand1;
	TMenuItem *Undo1;
	TMemo *Results;

	void __fastcall FileExitClick(TObject *Sender);
	void __fastcall FileOpen(TObject *Sender);
	void __fastcall ListClick(TObject *Sender);
	void __fastcall AddValClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);

	void __fastcall DivideValClick(TObject *Sender);
	void __fastcall MultiplyValClick(TObject *Sender);
	void __fastcall SubtractValClick(TObject *Sender);
	void __fastcall Count1Click(TObject *Sender);
	void __fastcall AbsClick(TObject *Sender);
	void __fastcall Exp1Click(TObject *Sender);
	void __fastcall Integer1Click(TObject *Sender);
	void __fastcall Logn1Click(TObject *Sender);
	void __fastcall Power1Click(TObject *Sender);

	void __fastcall Regression1Click(TObject *Sender);

	void __fastcall Scatter1Click(TObject *Sender);

	void __fastcall Sign1Click(TObject *Sender);
	void __fastcall SqrtClick(TObject *Sender);
	void __fastcall AcosClick(TObject *Sender);
	void __fastcall AsinClick(TObject *Sender);
	void __fastcall AtanClick(TObject *Sender);
	void __fastcall CosClick(TObject *Sender);
	void __fastcall SinClick(TObject *Sender);
	void __fastcall TanClick(TObject *Sender);
	void __fastcall ContentsClick(TObject *Sender);
	void __fastcall TTestClick(TObject *Sender);
	void __fastcall BarClick(TObject *Sender);
	void __fastcall AnovaClick(TObject *Sender);


	void __fastcall Stats1Click(TObject *Sender);
	void __fastcall Uniform1Click(TObject *Sender);
	void __fastcall Normal1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSStat(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSStat *SStat;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif
