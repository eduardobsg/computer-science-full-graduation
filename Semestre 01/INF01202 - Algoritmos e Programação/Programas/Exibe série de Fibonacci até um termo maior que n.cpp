/*
  Name: João Luiz Grave Gross
  Exercícios de Fixação 7.2 - Algoritmos Iterativos e Comando do-while
  Date: 21/03/09 21:02
  Description: 
  Mostra os valores da série de Fibonacci menores que n 
  Série de Fibonacci: 1 1 2 3 5 8 13 ............ 
  
num1=1
num2=1
soma=2

soma=3
num1=num2
num2=soma

*/

#include<stdlib.h>
#include<stdio.h>

int main ()
{
    int n, num1=1, num2=1, soma, flag=1, flag2=1;
    while (flag)
    {
       printf ("Digite um valor: ");
       scanf ("%i",&n);
       if (n < 0)
          flag2 = 0;
       else   
          printf ("1 1 ");   
          
       while (flag2)
       {
          soma = num1 + num2;
          num1 = num2;
          num2 = soma;
          if (soma < n)
             printf ("%d ",soma);
          else
             flag2 = 0;      
       }   
    flag == 1? printf ("\n1 - Reiniciar\n0 - Finalizar\n"):flag=0;
    scanf ("%d",&flag);
    num1=1;
    num2=1;
    soma=0;
    flag2=1;
    }
    system ("pause");
    return 0;
}
