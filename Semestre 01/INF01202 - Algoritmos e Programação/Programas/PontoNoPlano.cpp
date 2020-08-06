//Localizacao de ponto no plano
#include <stdio.h>
#include <stdlib.h>
int main  (  )
{
   float x , y;     
   printf("\n Coordenadas: x = ");
   scanf("%f", &x);
   printf("  y = ");
   scanf("%f", &y);
   if ( x == 0  &&  y == 0 )
      printf("\n Ponto na origem\n");
   if ( x > 0  &&  y > 0 )
      printf("\n Ponto no quadrante 1\n");
   if ( x < 0  &&  y > 0 )
      printf("\n Ponto no quadrante 2\n");
   if ( x < 0  &&  y < 0 )
      printf("\n Ponto no quadrante 3\n");
   if ( x > 0  &&  y < 0 )
      printf("\n Ponto no quadrante 4\n");
   if ( x == 0  &&  y  != 0 )
      printf("\n Ponto no eixo dos y\n");
   if ( x != 0  &&  y  == 0 )
      printf("\n Ponto no eixo dos x\n");
   system("pause");
   return 0;
} 
