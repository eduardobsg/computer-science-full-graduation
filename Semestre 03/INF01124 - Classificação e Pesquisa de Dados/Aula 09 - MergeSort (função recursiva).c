#include <stdio.h>
 
void intercala(int p, int q, int r, int v[])
{
     int i, j, k, *w;
     w = malloc( (r - p) * sizeof (int) );
     i = p;
     j = q;
     k = 0;
 
     while (i < q && j < r)
     {
           if (v[i] <= v[j])
              w[k++] = v[i++];
           else
               w[k++] = v[j++];
     }
 
     while (i < q) w[k++] = v[i++];
     while (j < r) w[k++] = v[j++];
 
     for (i = p; i < r; i++)
         v[i] = w[i - p];
 
     free(w);
}
 
void ordenarMergeSort(int p, int r, int v[])
{
     if (p < r - 1)
     {
        int q = (p + r) / 2;   
        ordenarMergeSort(p, q, v); //o e 2 //
        ordenarMergeSort(q, r, v); //2 e 4 //3 4
        intercala(p, q, r, v);
     }
}


int main()
{
    int i, numeros[] = {10, 20, 55, 3};
    int n = 4;

    printf ("Vetor nao ordenado\n");
    for (i = 0; i < n; i++)
        printf("%d ", numeros[i]);
    ordenarMergeSort(0, n, numeros);
 
    printf ("\n\nVetor nao ordenado\n");
    for (i = 0; i < n; i++)
        printf("%d ", numeros[i]);
    getchar();
}
