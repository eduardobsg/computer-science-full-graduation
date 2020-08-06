/* Comunicação coletiva - Uso de MPI_Gather

- é primitiva responsável por agrupar em
apenas um processo dados que estão
distribuídos em n processos;

- faz o inverso da Scatter;

- o processo emissor e os receptores
executam a mesma primitiva, com os
mesmos argumentos.

*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10

/* todos enviam para o processo zero */
int main(int argc, char **argv){
	int size, rank, i;
	int *num, *result;
	
	/* área origem e destino */
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	/* processo zero precisa de área com N dados */
	if (rank == 0) {
		num = (int *) malloc(N*sizeof(int));

		result = (int *) malloc(N*sizeof(int));
		num = (int *) malloc(N/size*sizeof(int));
		
		for (i = 0; i < N; i++)
			result[i] = rank;
	}
	else
		num = (int *) malloc(N/size*sizeof(int));
		
	/* todos inicializam área de send, cada um com seu ID */
	for (i = 0; i < N/size; i++)
		num[i] = rank;

	/* zero envia e recebe da/na mesma área */
	MPI_Gather(num, N/size, MPI_INT, result, N/size, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Gather(num, N/size, MPI_INT, num, N/size, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
		for (i = 0; i < N; i++)
			printf("%d\n", result[i]);

	MPI_Finalize();
	return(0);
}
