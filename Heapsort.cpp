/* This subroutine sorts an array of type float */
// 24 May 98 - Ported to BCB C++

void adjust (double *, int, int );

void heapsort (double *x,int size)
{
int i;
double hold;

for (i=size/2;i>=0;i--) adjust (x,i,size);
   for (i=size-1;i>=0;i--) {
      hold=*(x+i+1);
      *(x+i+1)=*x;
      *x=hold;
      adjust(x,0,i);
   }
}

void adjust(double *x,int i, int size)
{
int j;
float value;

value=*(x+i);
j=2*i;
while (j <= size) {
   if (( j < size) && (*(x+j) < *(x+j+1))) j++;
   if (value >= *(x+j)) {
      *(x+(j/2))=value;
      return;
   }
   *(x+(j/2))=*(x+j);
   j=2*j;
}
*(x+(j/2))=value;
}

