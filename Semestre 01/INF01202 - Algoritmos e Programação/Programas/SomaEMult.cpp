//soma ou multiplica dois valores inteiros lidos
#include <stdio.h>
#include <stdlib.h>
int main (   )
{  
   int codigo, valor1, valor2, resultado;
   printf("\n Digite o codigo (1 - Soma; 2 - multiplicacao): ");
   scanf("%d", &codigo);
   printf("\n Digite o valor 1: ");
   scanf("%d", &valor1);
   printf("\n Digite o valor 2: ");
   scanf("%d", &valor2);
   if (codigo == 1)
       {
       resultado = valor1 + valor2;       
       printf("\n Resultado da soma: %d\n", resultado);
       }
   if (codigo == 2)
       {
       resultado = valor1 * valor2;       
       printf("\n Resultado da multiplicacao: %d\n", resultado);
       }
   system("PAUSE");
   return 0;   
}    
