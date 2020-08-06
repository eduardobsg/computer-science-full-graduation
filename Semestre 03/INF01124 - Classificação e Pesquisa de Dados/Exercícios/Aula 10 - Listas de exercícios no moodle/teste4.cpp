#include <stdio.h>
#include <stdlib.h>

int main()
{
     int n = 7, v[] = {10,9,8,5,4,3,2};
     int i, j, min, x, m;
     for (m = n; m >= 2; --m) 
     {
         x = v[0];
         printf ("\nIteracao %d, x = %d\n", m, x);
         for (j = 0; j < m; ++j) 
             v[j] = v[j+1];
         v[m-1] = x;
         for (i = 0; i < n; i++)
             printf ("%d ", v[i]);
         printf ("\n");
     }
     for (i = 0; i < n; i++)
         printf ("%d ", v[i]);
     printf ("\n");
     system ("pause");
     return 0;
}
