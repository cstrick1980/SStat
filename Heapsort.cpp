/* This subroutine sorts an array of type float */
// 24 May 98 - Ported to BCB C++




{
int i;
double hold;




      *(x+i+1)=*x;
      *x=hold;
      adjust(x,0,i);
   }
}


{
int j;
float value;



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