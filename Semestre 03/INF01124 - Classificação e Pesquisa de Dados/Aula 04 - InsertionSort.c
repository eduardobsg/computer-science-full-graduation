#include <stdio.h>
#include <stdlib.h>

int main()
{
    //int vetor[] = {9, 8, 10, 7, 3, 1, 5, 2, 6, 8, 4};
    int vetor[] = {5, 2, 8, 1, 3};
    int i, j, tamanho=5, k, chave, copia=0, comp=0;

   printf("Vetor Nao Ordenado\n");    
   for (k = 0; k < tamanho; k++) 
       printf ("%d ", vetor[k]);
   system("pause");
	
   printf ("\nOrdenando\n");
   for(j = 1; j < tamanho; j++) 
   {   
       printf ("\nIteracao %d\n", j);
       chave = vetor[j];
       i = j - 1; 
       while(i >= 0 && vetor[i] > chave)
       {
               vetor[i+1] = vetor[i];
               i = i - 1;
               for (k = 0; k < tamanho; k++) 
                   printf ("%d ", vetor[k]);       
               printf ("\n");
       }		
       vetor[i+1] = chave;
       for (k = 0; k < tamanho; k++) 
              printf ("%d ", vetor[k]);       
       printf ("\n");
  }
   printf("\nVetor Ordenado \n");    
   for (k = 0; k < tamanho; k++) 
       printf ("%d ", vetor[k]);
   system("pause");
}


