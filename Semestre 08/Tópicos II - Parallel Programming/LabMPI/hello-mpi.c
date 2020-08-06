#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
   int p, r ;
   MPI_Init(&argc, &argv) ;
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Comm_rank(MPI_COMM_WORLD, &r);
   printf("Hello world! From process %d, running in a team of %d processes!\n", r, p) ;
   MPI_Finalize();
   return 0 ;
}
