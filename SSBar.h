//---------------------------------------------------------------------------
#ifndef SSBarH
#define SSBarH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Xyhist.hpp"
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBarChart : public TForm
{
__published:	// IDE-managed Components
	THistogram *SSHistogram;
private:	// User declarations
public:		// User declarations
	__fastcall TBarChart(TComponent* Owner);
    void BuildBar(void);
};
//---------------------------------------------------------------------------
extern TBarChart *BarChart;
//---------------------------------------------------------------------------
#endif
