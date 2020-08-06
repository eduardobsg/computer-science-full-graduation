#include <stdio.h>
#include <mpi.h>

#define NBTASKS 47
#define END -1

int tag    =110;
int tag_res=111;

int calcula(int i) {
   return( i ) ;
}

void master() {
   int task=0;
   int res;
   int sinal;
   int nb_slaves;
   int total_res = 0;
   MPI_Status stat;

   MPI_Comm_size(MPI_COMM_WORLD, &nb_slaves);
   nb_slaves--;
   /* Send one task to each slave */
   for (task=0 ; task<nb_slaves ; task++) {
      printf("Sending task %d to slave %d\n", task, task+1);
      MPI_Send(&task, 1, MPI_INT, task+1, tag, MPI_COMM_WORLD);
   }

   /* Wait for results and send new tasks to the guy who is finished.
    */
   while (task < NBTASKS) {
      MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, tag_res, MPI_COMM_WORLD, &stat);
      total_res += res;
      printf("Sending task %d to slave %d\n", task, stat.MPI_SOURCE);
      MPI_Send(&task, 1, MPI_INT, stat.MPI_SOURCE, tag, MPI_COMM_WORLD);
      task++;
   }
   /* There are still nb_slaves results to receive */
   for (task=0 ; task<nb_slaves ; task++) {
      MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, tag_res, MPI_COMM_WORLD, &stat);
      total_res += res;
      /* ... and send a signal to the slave in order to have it stop */
      sinal = END;
      MPI_Send(&sinal, 1, MPI_INT, stat.MPI_SOURCE, tag, MPI_COMM_WORLD);
   }
   printf("And the result is: %d\n", total_res);
}

void  slave() {
   int task=0;
   int res;
   int r;
   MPI_Status stat;

   MPI_Comm_rank(MPI_COMM_WORLD, &r);
   while (task != END) {
      MPI_Recv(&task, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &stat);
      printf("slave %d: processing task %d.\n", r, task);
      res = calcula(task);
      MPI_Send(&res, 1, MPI_INT, 0, tag_res, MPI_COMM_WORLD);
   }
   printf("Slave %d stopping...\n", r);
}

int main(int argc, char* argv[]) {
   int p, r ;
   int tag = 103;
   MPI_Status stat;
   double valor ;

   MPI_Init(&argc, &argv) ;
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Comm_rank(MPI_COMM_WORLD, &r);

   if (r==0) {
      printf("Process 0 is the master.\n");
      master();
   }
   else {
      printf("Process %d is a slave.\n", r);
      slave();
   }
   MPI_Finalize();
   return 0 ;
}
