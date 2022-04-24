//---------------------------------------------------------------------------
#ifndef GetPlotH
#define GetPlotH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TPlotInput : public TForm
{
__published:	// IDE-managed Components
	TListBox *YValue;
	TListBox *XValue;
	TButton *IsOk;
	TButton *IsCancel;
	TEdit *PlotTitle;
	TLabel *YLabel;
	TLabel *TitleLabel;
	TLabel *XLabel;
	TEdit *XAxisTitle;
	TLabel *XTitleLabel;
	TLabel *YTitleLabel;
	TEdit *YAxisTitle;
private:	// User declarations
public:		// User declarations
	__fastcall TPlotInput(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPlotInput *PlotInput;
//---------------------------------------------------------------------------
#endif
