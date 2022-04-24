//---------------------------------------------------------------------------
#ifndef TVerticalLabelH
#define TVerticalLabelH
//---------------------------------------------------------------------------
#include <vcl\SysUtils.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Forms.hpp>
#include <vcl\StdCtrls.hpp>


//---------------------------------------------------------------------------
class TVerticalLabel : public TCustomLabel
{
public:
private:
	enum VAlignment{vaTop, vaBottom};

   TAlignment 	FJustify;
   VAlignment	FVertical;
   int			FHSpacing;
   int			FVSpacing;
   bool		FReverse;
   int			FFontAngle;

  	void _fastcall SetJustify(Classes::TAlignment justify);
  	void _fastcall SetVertical(VAlignment justify);
   void _fastcall SetHSpacing(int spacing);
   void _fastcall SetVSpacing(int spacing);
   void _fastcall SetReverse(bool reverse);
   void _fastcall SetFontAngle(int angle);

protected:

	virtual void __fastcall Paint(void);
public:

	__fastcall TVerticalLabel(TComponent* Owner);
__published:
	__property Align;
   __property Alignment;
//   __property AutoSize;
	__property Caption;
	__property Color;
   __property Cursor;
   __property Enabled;
	__property Font;
	__property int FontAngle = {read=FFontAngle, write=SetFontAngle, default=0};
   __property int HorizontalSpacing = {read=FHSpacing, write=SetHSpacing, default=0};
   __property Classes::TAlignment HorizTextAlign = {read=FJustify, write=SetJustify, default = taCenter};
   __property Hint;
   __property Name;
   __property ParentColor;
   __property ParentFont;
   __property ParentShowHint;
   __property bool Reverse={read=FReverse, write=SetReverse, default=false};
   __property ShowHint;
   __property Tag;
   __property Transparent;
   __property int VerticalSpacing = {read=FVSpacing, write=SetVSpacing, default=0};
   __property VAlignment VerticalAlignment = {read=FVertical, write=SetVertical, default=vaTop};
   __property Visible;

   __property OnClick;
   __property OnDblClick;
   __property OnMouseDown;
   __property OnMouseMove;
   __property OnMouseUp;
};
//---------------------------------------------------------------------------
#endif
