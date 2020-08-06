#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void quickSort(int *vetor, int esq, int dir)
{
   int i, j, k;
   int pivo, troca;
  
   i=esq; j=dir;
   pivo=vetor[(esq+dir)/2];

   printf("Pivo: %d \n", pivo);

   do 
   {
        while(vetor[i]<pivo && i<dir) i++;
        while(pivo<vetor[j] && j>esq) j--;
        if(i<=j) 
        {
          troca = vetor[i];
          vetor[i] = vetor[j];
          vetor[j] = troca;
          i++; j--;
        }
   }while(i<=j);
   for(k=0;k<MAX;k++)
        printf("%d ", vetor[k]);
   printf ("\n");
    
   if(esq<j) quickSort(vetor, esq, j);
   if(i<dir) quickSort(vetor, i, dir);
}

int main()
{

// Ordena - max 6
 // int i, k, vetor[]= {15, 18, 4, 5, 14, 1} ;

// Exercicio 01 - max 9
   int i, k, vetor[]= {17, 21, 9, 3, 11, 19, 15, 3, 18, 20} ;


// Exercicio 02 - max 7 - caso m&eacute;dio
// int i, k, vetor[]= {1, 2, 1, 2, 1, 2, 1} ;

// Exercicio 04 - max 10 -  melhor caso
// int i, k, vetor[]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} ;

// Exercicio 05 - max 10 -  pior caso
   //int i, k, vetor[]= {10, 9, 8, 7, 6, 5, 4, 3, 2, 1} ;

// Exercicio 08 - max 10
// int i, k, vetor[]= {1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ;


    printf("\nVetor Entrada (nao ordenado):\n");
    for(k=0; k<MAX; k++)
       printf("%d ", vetor[k]);

    printf("\n\nOrdenando:\n");    
    quickSort(vetor, 0, MAX-1);
    
    printf("\nVetor Ordenado:\n");
    for(k=0;k<MAX;k++)
        printf("%d ", vetor[k]);
    system("pause");
}
