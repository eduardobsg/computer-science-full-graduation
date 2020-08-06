// Verifica se um valor lido eh par ou impar 
#include <stdio.h>
#include <stdlib.h>
int main (   )
{
  int valor;	
  printf("Forneca o valor a ser testado : ");
  scanf ( "%d", &valor );
  // O numero eh par se o resto de sua divisao (inteira) por 2 for nulo 
  if (valor % 2   ==  0) 
     printf ("Eh par!\n" );
  else  
    printf( "Eh impar !\n");
    system("pause");
  return 0;
}
