/*
  Name: João Luiz Grave Gross
  Exercício: Fixação 7.1
  Date: 21/03/09 16:56
  Description: Fazer um programa em C que leia um inteiro N, maior que -1, 
  e determine o máximo divisor comum de 2 números inteiros x e y. 

    Como fazer:
    1º) dividimos o número maior pelo número menor;
            48 / 30 = 1 (com resto 18)

    2º) dividimos o divisor 30, que é divisor da divisão anterior, por 18, que é 
    o resto da divisão anterior, e assim sucessivamente;
            30 / 18 = 1 (com resto 12)

            18 / 12 = 1 (com resto 6)

            12 / 6 = 2 (com resto zero - divisão exata)

    3º) O divisor da divisão exata é 6. Então m.d.c.(48,30) = 6.

   Objetivo: Determinar o máximo divisor comum de 2 números inteiros x e y
*/

#include<stdlib.h>
#include<stdio.h>

int main ()
{
    int x, y, num, aux1, aux2, flag=1;
    printf ("Digite dois valores: ");
    scanf ("%i%i",&x,&y);
    if (x > y)
    {                                   
       aux1 = x % y;                     //calcula o resto da divisão              
       num = y;                          //y será o numerador da primeira divisão do while
    }
    if (y > x)
    {
       aux1 = y % x;                     //calcula o resto da divisão
       num = x;                          //x será o numerador da primeira divisão do while
    }
    if (x == y)
    {  
       num = x;
       flag = 0;
    }
    if (aux1 == 0)
       flag = 0;
    while (flag)
    {
       aux2 = num % aux1;                //aux2 = 30 % 18 = 12
       num = aux1;                       //num = 18
       aux1 = aux2;                      //aux1 = 12 -> próxima divisão -> aux2 = 18 % 12
       if (aux2 == 0)
          flag = 0;                 
    }
    printf ("Maximo divisor comum: %d\n\n",num);
    system ("pause");
    return 0;
}
