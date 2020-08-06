#include <stdio.h>
#include <stdlib.h>

#define SIZE 1600 /* tamanho do vetor */

int main ( int argc, char **argv ) {
	int occurrences; /* número de ocorrências do número alvo */
	int target; /* número a ser buscado */
	int vec[SIZE]; /* vetor no qual o número será buscado */
	int i; /* iterador */
	
	printf("Digite o vetor a ser analisado separando cada elemento em uma linha diferente: ");

	for(i = 0; i < SIZE; i++)
		vec[i] = rand()
		scanf("%d", &vec[i]); /* leitura do vetor */

	printf("\nDigite o valor a ser buscado: ");
	scanf("%d", &target); /* leitura do número a ser buscado */

	occurrences = 0;
	for(i = 0; i < SIZE; i++) {
		if(vec[i] == target) {
			occurrences++;
		}
	}
	
	/* busca sequencial pelo número */
	/* ocorrência encontrada */
	printf("\nFinalizado\n\nNumero de vezes em que %d aparece no vetor e: %d\n", target, occurrences);
	
	return 0;
}

