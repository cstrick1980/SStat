//---------------------------------------------------------------------------
#ifndef TestData1H
#define TestData1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};

class TTestData1
{
private:
public:
   int row;
   int col;
};

//---------------------------------------------------------------------------
extern TForm1 *Form1;
extern TTestData1 * TestData;
//---------------------------------------------------------------------------
#endif
