/* Simple, Hello World! program */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[]) {
int t_id;
#pragma omp parallel private(t_id)
  {
     t_id = omp_get_thread_num();
     printf("Hello world! from thread number %d\n", t_id);
  }  
  printf("This should be printed by only one thread thread.\n");
}

