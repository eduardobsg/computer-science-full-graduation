#include <stdio.h>
#include <stdlib.h>

void heapSort(int numbers[], int array_size)
{
  int i, temp;
 
  for (i = array_size - 1; i >= 0; i--)
    siftDown(numbers, i, array_size - 1);
 
  for (i = array_size-1; i >= 1; i--)
  {
    temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDown(numbers, 0, i-1);
  }
}
 
 
void siftDown(int numbers[], int root, int bottom)
{
  int done, maxChild, temp;
 
  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (numbers[root * 2] > numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
 
    if (numbers[root] < numbers[maxChild])
    {
      temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}


int main()
{
    //int vetor[] = {9, 8, 10, 7, 3, 1, 5, 2, 6, 8, 4};
    int vetor[] = {5, 2, 8, 1, 3};
    int i, tamanho=5;

    heapSort (vetor, tamanho);

    printf("\nVetor Ordenado \n");    
    for (i = 0; i < tamanho; i++) 
       printf ("%d ", vetor[i]);
    system("pause");
}


