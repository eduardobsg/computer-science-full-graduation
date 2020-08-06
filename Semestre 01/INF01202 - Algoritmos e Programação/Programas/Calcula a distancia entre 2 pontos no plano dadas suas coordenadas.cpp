/* Name Prog.: ProgExe2-5.cpp
   Author: Cida Souto
   Date: 16/01/2008
   Description: Calcula a distancia entre 2 pontos no plano dadas suas coordenadas
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main ()
{
/* Declaracao das Variaveis   */
   float x1, y1, x2, y2, lado1, lado2, d;
/* Comandos para a leitura dos dados manipulados pelo programa  */
   printf ("Forneca x1, y1:\n");
   scanf  ("%f%f", &x1, &y1);
   printf ("Forneca x2, y2:\n");
   scanf  ("%f%f", &x2, &y2);
/* Calculo dos lados do triangulo ret. e da distancia */
   lado1 = x2 - x1;
   lado2 = y2 - y1;
   d = sqrt (lado1 * lado1 + lado2 * lado2);
/* Impressao da Distancia */
   printf ("Distancia = %f\n", d);
/* Comandos de encerramento do programa */
   system ("pause");
   return 0;
}
