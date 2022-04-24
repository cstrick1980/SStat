//---------------------------------------------------------------------------
#ifndef SSDataDef
#define SSDataDef

class TSSData {
   public:
      int row;
      int col;
      void TSSData();
      void ~TSSData();
};

#ifndef EXTERN
#define EXTERN
extern TSSData* SSData;
#endif
//---------------------------------------------------------------------------
#endif
 