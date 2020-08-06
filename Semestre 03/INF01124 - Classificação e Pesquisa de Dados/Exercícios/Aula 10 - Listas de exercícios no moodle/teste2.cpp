#include <stdio.h>
#include <stdlib.h>

int main()

{
     int n = 5, v[] ={5, 2, 8, 1, 3};
     int i, j, x, h, m;
     
     printf("Vetor Nao Ordenado\n");  
     for (m = 0; m < n; m++)
         printf ("%d ", v[m]);
     printf ("\n");
         
     for (j = 1; j < n; j++) 
     {
         x = v[j]; //chave
         printf ("\nIteracao %d\n", j);
         for (h = 0; h < j && v[h] <= x; ++h); //
         for (i = j-1; i >= h; --i)
         {
             v[i+1] = v[i];
             for (m = 0; m < n; m++)
                 printf ("%d ", v[m]);
             printf ("\n");
         }
         v[h] = x;
         for (m = 0; m < n; m++)
             printf ("%d ", v[m]);
         printf ("\n");
     }
     system ("pause");
     return 0;
}
