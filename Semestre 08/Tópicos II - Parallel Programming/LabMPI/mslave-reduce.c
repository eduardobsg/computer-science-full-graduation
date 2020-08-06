#include <stdio.h>
#include <mpi.h>

#define NBTASKS 120
#define END -1

#define RAIZ 0

int calcula(int i) {
   return( i ) ;
}

int main(int argc, char* argv[]) {
   int p, r, i ;
   int* tasks;
   int* res_local;
   int res = 0;

   MPI_Init(&argc, &argv) ;
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Comm_rank(MPI_COMM_WORLD, &r);
 
   if (r == RAIZ) {
      tasks = (int*)malloc(sizeof(int)*NBTASKS);
      for (i=0; i<NBTASKS;i++) tasks[i] = i;
   }
   else
      tasks = (int*)malloc(sizeof(int)*(NBTASKS/p));
   MPI_Scatter(tasks, NBTASKS/p, MPI_INT, tasks, NBTASKS/p, MPI_INT, RAIZ, MPI_COMM_WORLD);

   /* Cada processo calcula sobre seu pool local de tarefas */
   res_local = (int*)malloc(sizeof(int)*NBTASKS/p);
   for (i=0 ; i< NBTASKS/p ; i++) {
       res_local[i] = calcula(tasks[i]); 
   }
   MPI_Reduce(res_local, &res, NBTASKS/p, MPI_INT, MPI_SUM, RAIZ, MPI_COMM_WORLD);

   if (r==RAIZ) {
      printf("O resultado vale %d\n", res);
      printf("Ele devia ser igual a %d\n.", (NBTASKS*(NBTASKS-1)/2));
   }
   MPI_Finalize();
   return 0 ;
}
