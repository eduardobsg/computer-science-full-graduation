#include <stdio.h>
#include <stdlib.h>

#define NRA 62                 /* number of rows in A */
#define NCA 15                 /* number of columns in A */
#define NCB 7                  /* number of columns in B */

int main (int argc, char *argv[]) {
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* A  */
	b[NCA][NCB],           /* B  */
	c[NRA][NCB];           /* C (result of A x B) */

  /* Inicializations */
  
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
 
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;

  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /* Main computation */
  for (i=0; i<NRA; i++)    {
    for(j=0; j<NCB; j++)       
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
  }

/*** Print the result C */
printf("******************************************************\n");
printf("Result:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
  printf("\n"); 
  }
printf("******************************************************\n");
printf ("Done.\n");

}
