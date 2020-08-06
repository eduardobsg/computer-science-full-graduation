#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

/* função que decide se n é primo, sendo n maior do que 1
retorna 1 caso o número seja primo, e 0 caso não seja */
int isprime(int n)
{
	int i, squareroot;
	
	if (n > 1) {
		squareroot = (int) sqrt((double) n);
	
		for (i = 3; i <= squareroot; i = i + 2) {
			if ((n % i) == 0) {
				return 0;
			}
		}
	
		return 1;
	} 
	else {
		return 0;
	}
}

int main(int argc, char **argv)
{
	int n, /* numero a ser testado */
	pc1, pc2, /* prime counter */
	limit, /* maior número a ser testado */
	myrank, /* identificador do processo */
	size; /* quantidade de processos */
	
	/* Initialize MPI */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); //mpirun -np 10 ./executável
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	if(argc < 2 && myrank == 0) {
		printf("Digite o numero a ser testado\n");
		return 0;
	} 
	else {
		sscanf(argv[1], "%d", &limit);
	}
		
	if( myrank == 0 ) {
		printf("\nEncontrar numeros primos entre 2 e %d (inclusive).\nCalculando...", limit);
		for (pc1 = 1, n = 1; n <= limit; n += size * 2) {
			/* testa sequencialmente se um número é primo ou nao */
			if (isprime(n)) {
				pc1++;
			}
		}
	
		int i;
		for( i = 1; i < size; i++ ) {
			MPI_Recv(&pc2, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pc1 += pc2;
		}
	}
	else {
		for (pc2 = 0, n = 1 + myrank * 2; n <= limit; n += size * 2) { 
			/* testa sequencialmente se um número é primo ou nao */
			if (isprime(n)) {
				pc2++;
			}
		}
		
		MPI_Send(&pc2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}	

	if( myrank == 0 ) {		
		printf("\nFinalizado.\nTotal de primos encontrados %d\n", pc1);
	}
	
	/* Shut down MPI */
	MPI_Finalize();
}
