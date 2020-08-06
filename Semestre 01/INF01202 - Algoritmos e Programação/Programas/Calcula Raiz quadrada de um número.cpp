/*
  Name: João Luiz Grave Gross
  Copyright: 
  Author: 
  Date: 08/03/09 14:31
  Description: Calcula da raiz quadradda de um dado valor
*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main ()
{
    float raiz;
    printf("Digite um valor para saber sua raiz: ");
    scanf("%f",&raiz);
    raiz = sqrt(raiz);   
    printf("Raiz = %.2f\n",raiz);
    system("pause");
    return 0;
}
