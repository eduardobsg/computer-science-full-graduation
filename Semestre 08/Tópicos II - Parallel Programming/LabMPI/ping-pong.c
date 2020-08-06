#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
   int p, r ;
   int tag = 103;
   MPI_Status stat;
   double valor ;

   MPI_Init(&argc, &argv) ;
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Comm_rank(MPI_COMM_WORLD, &r);

   if (r==0) {
      printf("Process 0 sends a message to 1\n");
      valor = 3.14 ;
      MPI_Send(&valor, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
   }
   else {
      printf("Process 1 receives a message from 0\n");
      MPI_Recv(&valor, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &stat);
      printf("The received value is %.2lf\n", valor);
   }
   MPI_Finalize();
   return 0 ;
}
