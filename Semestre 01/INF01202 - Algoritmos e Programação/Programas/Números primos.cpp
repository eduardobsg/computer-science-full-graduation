/*
  Name: Números primos
  Author: João Luiz Grave Gross
  Date: 31/03/09 13:38
  Description: Calcular os primeiros n números primos (n pode variar de 1 a 20)
*/

#include<stdlib.h>
#include<stdio.h>

int main ()
{
    int n, div, resultado, i, num, j;
    printf ("Digite a quantidade de numeros primos que deseja ver: ");
    scanf ("%d", &n);
    
    if(n > 0)
    {
        for (i = 0, num = 2; i < n; i++)
        {
           for (div = 1, j = 0; div <= num; div++)       
           {
               resultado = num / div;                    
               if (num == (resultado * div))             
               {
                  j++;
                  if (j > 2)
                  {
                     div = num + 1;
                     i--;
                     num++;
                  }    
                  else       
                     if (div == num)                        
                     {
                        printf ("%d ", num);
                        //quer gravar os primos em um arquivo? Pode gravar aqui!
                        num++;
                        div = num + 1;
                     }
               }
           } 
        } 
    }
    
    
    
    printf ("\n\n");
    system ("pause");
    return 0;
    
}
