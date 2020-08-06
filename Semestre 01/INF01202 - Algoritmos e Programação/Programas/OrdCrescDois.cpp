//Apresenta dois valores lidos em ordem crescente
#include <stdio.h>
#include <stdlib.h>
int main(  )
{
   int a , b , aux; 
   printf("\n O primeiro numero: ");
   scanf("%d", &a);
   printf("\n O segundo numero: ");
   scanf("%d", &b);
   if  (a > b)
        printf("\n Em ordem crescente: %d e %d \n", b , a); 
   else 
        if  (b > a) 
              printf("\n Em ordem crescente: %d e %d \n", a , b);
        else     
              printf("\n %d e %d sao iguais\n", a , b);
   system("PAUSE");
   return 0;
}
