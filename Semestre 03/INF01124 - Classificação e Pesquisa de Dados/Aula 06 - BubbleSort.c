#include <stdio.h>
#include <stdlib.h>

int main()
{
    int vetor[] = {13, 11, 25, 10, 18, 21, 23};
    int tamanho=7, i, j, temp, k;
	
	 printf("Vetor Nao Ordenado\n");    
	 for (i = 0; i < tamanho; i++)
          printf ("%d ", vetor[i]);
     system("pause");
   
     printf ("\nOrdenando\n");
     for (i = tamanho - 1; i > 0; i--)
     {
           printf ("\nIteracao %d\n", i);
           for (j = 0; j < i; j++)
           {
                 if(vetor[j] > vetor[j+1]) /* compara elementos vizinhos */
                 {
                    temp = vetor[j];    /* troca vetor[j] e vetor[j+1] */
                    vetor[j] = vetor[j+1];
                    vetor[j+1] = temp;
                 }
                 for (k = 0; k < tamanho; k++) 
                     printf ("%d ", vetor[k]);      
                 printf ("\n");       
           }
     
     }

     printf("\nVetor Ordenado \n");               
     for (i = 0; i < tamanho; i++) 
         printf ("%d ", vetor[i]);
     system("pause");
}

