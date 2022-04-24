//---------------------------------------------------------------------------
#ifndef matrixssH
#define matrixssH
//---------------------------------------------------------------------------
class matrixss
{
public:
   double *Matrix;
   int varcnt;
   int *varlist;

   matrixss(void);
   double *buildss(void);
   ~matrixss(void);
};


#endif
