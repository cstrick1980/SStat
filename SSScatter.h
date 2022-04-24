//---------------------------------------------------------------------------
#ifndef SSScatterH
#define SSScatterH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\graphics.hpp>
#include "xyGraph.hpp"

//---------------------------------------------------------------------------
class TScatterPlot : public TForm
{
__published:	// IDE-managed Components
	TxyGraph *xyScatter;
	TButton *IsOk;
private:	// User declarations
public:		// User declarations
	__fastcall TScatterPlot(TComponent* Owner);
    void BuildPlot(void);
    void InsertVariables(void);
};
//---------------------------------------------------------------------------
extern TScatterPlot *ScatterPlot;
//---------------------------------------------------------------------------
#endif
