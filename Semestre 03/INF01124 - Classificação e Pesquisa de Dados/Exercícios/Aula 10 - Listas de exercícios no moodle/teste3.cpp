#include <stdio.h>
#include <stdlib.h>

int main()
{
     int n = 5, v[] = {5, 2, 8, 1, 3};
     int i, j, min, x, m;
     for (i = 1; i < n-1; ++i) 
     {
         printf ("\nIteracao %d\n", i);
         min = i;
         for (j = i+1; j < n; ++j)
             if (v[j] <= v[min]) 
                min = j;
         x = v[i]; 
         v[i] = v[min]; 
         v[min] = x;
         for (m = 0; m < n; m++)
             printf ("%d ", v[m]);
         printf ("\n");
     } 
     system ("pause");
     return 0;
}
