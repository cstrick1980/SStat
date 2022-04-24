//---------------------------------------------------------------------------
#ifndef TSSDataH
#define TSSDataH
#define MAXCOL 10
#define MAXROW 100
#define EPSILON 1.0e-36

//---------------------------------------------------------------------------

class TSSData
{
private:
   float data[MAXROW][MAXCOL];

public:
   int row;
   int col;

   TSSData(void);
   float GetData(int, int);
   void PutData(float, int, int);
   ~TSSData(void);
};

extern TSSData *SSData;

#endif
