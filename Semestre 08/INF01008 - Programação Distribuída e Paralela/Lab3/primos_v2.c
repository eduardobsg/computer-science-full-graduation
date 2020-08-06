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
	pc, /* prime counter */
	limit, /* maior número a ser testado */
	myrank, /* identificador do processo */
	size, /* quantidade de processos */
	*vector, /* valores de inicialização do for de cada processo */
	nIni; /* valor de inicialização do for de cada processo */
	
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
		
		/* Calcula o vetor de envio */
		vector = (int *) malloc(size*sizeof(int));
		int i; 
		for(i = 0; i < size; i++)
			vector[i] = 1 + i * 2;
		
		/* Envia o valor de inicialização do for de cada processo */
		MPI_Scatter(vector, 1, MPI_INT, &nIni, 1, MPI_INT, 0, MPI_COMM_WORLD);
		
		/* Realiza as computações */
		for (pc = 1, n = nIni; n <= limit; n += size * 2) {
			if (isprime(n)) {
				pc++;
			}
		}
	}
	else {
		MPI_Scatter(vector, 1, MPI_INT, &nIni, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
		/* Realiza as computações */
		for (pc = 0, n = nIni; n <= limit; n += size * 2) { 
			if (isprime(n)) {
				pc++;
			}
		}
	}	

	MPI_Gather(&pc, 1, MPI_INT, vector, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if( myrank == 0 ) {		
		int i;
		for(i = 1; i < size; i++) {
			vector[0] = vector[0] + vector[i];
		}
	
		printf("\nFinalizado.\nTotal de primos encontrados %d\n", vector[0]);
	}
	
	/* Shut down MPI */
	MPI_Finalize();
}
