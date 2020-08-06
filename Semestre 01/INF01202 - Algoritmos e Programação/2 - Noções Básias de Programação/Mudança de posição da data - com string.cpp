/*
  Name: João Luiz Grave Gross        
  Copyright: 
  Author: 
  Date: 08/03/09 18:02
  Description: Faça um algoritmo que leia uma data no formato ddmmaa e imprima:
               • O dia, mês e ano separados.
               • A mesma data no formato mmddaa.
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

char data[6];

int main()
{
    printf ("\nDigite a data: ");
    scanf ("%s",&data);
    printf("Dia: %c%c\n", data[0], data[1]);
    printf("Mes: %c%c\n", data[2], data[3]);
    printf("Ano: %c%c\n", data[4], data[5]);
    system("pause");
    return 0;
}


