#include <stdio.h>
#include <stdlib.h>

int main()
{
     int n = 4;
     int v[]= {5, 2, 8, 1};
//     int v[]={2,1,3,4,5};
     
     int i, j, x, k;
     
     printf("Vetor Nao Ordenado\n");    
	 for (k = 0; k < n; k++)
          printf ("%d ", v[k]);
     system("pause");
     
     for (j = 1; j < n; j++) 
     {
         printf ("\nIteracao %d\n", j);
         x = v[j];
         for (i = j-1; i >= 0 && v[i] >= x; --i)
         {
             v[i+1] = v[i];
             for (k = 0; k < n; k++)
                 printf ("%d ", v[k]);
             printf ("\n");
         }v[i+1] = x;
         for (k = 0; k < n; k++)
             printf ("%d ", v[k]);
         printf ("\n");
     }
     system("pause");
     return 0;
}
