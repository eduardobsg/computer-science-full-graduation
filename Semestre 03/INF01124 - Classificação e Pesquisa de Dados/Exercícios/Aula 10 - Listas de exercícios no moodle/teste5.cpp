#include <stdio.h>
#include <stdlib.h>

#define MAX 9

void quick_S (int v[], int p, int r) 
{
    int c, i, j, t, k;
    if (p < r) 
    { 
        c = v[(p+r)/2];
        printf("Pivo: %d \n", c);
        i = p, j = r;
        while (i <= j) 
        {
            while (v[i] < c) 
                  ++i;
            while (c < v[j]) 
                  --j;
            if (i <= j) 
            {
               t = v[i], v[i] = v[j], v[j] = t;
               ++i, --j;
            }
        }
        for (k = 0; k<MAX; k++)
            printf("%d ", v[k]);
        printf ("\n");
        quick_S (v, p, j);
        quick_S (v, i, r);
    }
}

int main()
{
   int k, v[]= {17, 21, 9, 3, 11, 19, 15, 18, 20} ;

   printf("\nVetor Entrada (nao ordenado):\n");
   for(k=0; k<MAX; k++)
      printf("%d ", v[k]);

   printf("\n\nOrdenando:\n");    
   quick_S(v, 0, MAX-1);
    
   printf("\nVetor Ordenado:\n");
   for(k=0;k<MAX;k++)
       printf("%d ", v[k]);
   system("pause");
}
