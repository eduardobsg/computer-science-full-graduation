#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SIZE 5 /* tamanho do vetor */

int main ( int argc, char **argv ) {
	int occurrences; /* número de ocorrências do número alvo */
	int target; /* número a ser buscado */
	int *vec, *parc; /* vetor no qual o número será buscado */
	int i; /* iterador */
	int max, size, rank;
	
	/* initialize random seed: */
	srand (time(NULL));
	
	/* Initialize MPI */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	max = SIZE * size;
	parc = (int *) malloc(SIZE * sizeof(int));
	
	if( rank == 0 ) {
	
		printf("Vetor foi inicializado com %d valores.\n", max);
		vec = (int *) malloc(max * sizeof(int));
		for(i = 0; i < max; i++) {
			vec[i] = rand() % 10 + 1;
			printf("%d ", vec[i]);			
		}

		target = rand() % 10 + 1;
		printf("\nValor a ser buscado: %d\n", target);
		
		MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);			
		MPI_Scatter(vec, SIZE, MPI_INT, parc, SIZE, MPI_INT, 0, MPI_COMM_WORLD);	
	}
	else {	
		MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatter(vec, SIZE, MPI_INT, parc, SIZE, MPI_INT, 0, MPI_COMM_WORLD);	
	}	

	//printf("rank: %d, target: %d\n", rank, target);
	MPI_Barrier(MPI_COMM_WORLD);

	occurrences = 0;
	for(i = 0; i < SIZE; i++) {
		if(parc[i] == target) {
			occurrences++;
		}
		//printf("rank: %d, vec[%d]: %d, occurrences: %d\n", rank, rank*SIZE+i, parc[i], occurrences);
	}

	//printf("rank: %d, occurrences: %d\n", rank, occurrences);
	MPI_Gather(&occurrences, 1, MPI_INT, vec, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	if( rank == 0 ) {		
		for(i = 1; i < size; i++) {
			vec[0] += vec[i];
			//printf("vec[%d]: %d\n", i, vec[i]);
		}
	
		printf("\nFinalizado.\nNumero de vezes em que %d aparece no vetor: %d\n", target, vec[0]);
	}
	
	/* Shut down MPI */
	MPI_Finalize();
	
	return 0;
}

