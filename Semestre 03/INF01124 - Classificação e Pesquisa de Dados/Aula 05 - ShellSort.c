#include <stdio.h>
#include <stdlib.h>

int main()
{
   int i , j , k, h = 1, value, numero = 10;
   int vetor[] = {7, 2, 5, 6, 3, 1, 0, 8, 9, 4};
    
   printf("Vetor Nao Ordenado \n");    
   for (k = 0; k < numero; k++) 
       printf ("%d ", vetor[k]);
   system("pause");

   do { h = 3 * h + 1;  } while ( h < numero );
   printf ("\nOrdenando\n");
   do 
   {     
         h /= 3;  
         for (i = h; i < numero; i++) 
         {     
                value = vetor [i];
                j = i - h;
                while (j >= 0 && value < vetor [j])
                {     
                       vetor [j+h] = vetor [j];
                       j = j - h;
                }
                vetor [j+h] = value;
                for (k = 0; k < numero; k++) 
                    printf ("%d ", vetor[k]);       
                printf ("\b, h = %d\n", h);
           } 
   } while (h > 1);

   printf("\nVetor Ordenado \n");    
   for (k = 0; k < numero; k++) 
       printf ("%d ", vetor[k]);
   system("pause");
}  
