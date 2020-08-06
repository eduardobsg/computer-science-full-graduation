#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N       10

int main (int argc, char *argv[]) {
int tid, i;
double a[N], b[N], c[N];

for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
printf("End of sequential initialization.\n");

#pragma omp parallel for 
   for (i=0; i<N; i++) {
       tid = omp_get_thread_num();
       c[i] = a[i] + b[i];
       if (tid == 0) printf("Thread 0 computing i = %d.\n",i);
   }
}


