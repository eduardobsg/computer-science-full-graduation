/*
Name: TrabGrafos.c
Author: Hélio Brauner, João Gross
Date: 14/06/10 19:07
Description: Desenvolver um programa que calcule a cintura (menor ciclo) e o diâmetro (maior caminho entre dois vértices)
de um grafo com até 15 vértices.
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 20
#define INFINITO 999999

typedef struct listaciclo{
	int tamanho; /* armazena de arestas do ciclo */
	int first_vertice; /* armazena o vértices de partida para a leitura do ciclo */
	int *ciclo; /* armazena o ciclo em si */
} ListaCiclo;

typedef struct maior_caminho{
	int maior_caminho;
	int *caminho;
} MaiorCaminho;

/* Protótipo das funções */
int **LeArquivo (char *, int *, int **);
void ImprimeMatriz (int **, int);

/* Cálculo de Cintura */
void CalculaCintura (int **, int);
int InsereVerticeLista (ListaCiclo *, int);
void ExcluiVerticeLista (ListaCiclo *, int); 
void CalculaCiclo (ListaCiclo *, ListaCiclo *, int, int, int **);

/* Cálculo do Diâmetro */
void CalculaDiametro (int **, int);
void AchaCaminhos (int, int, int **, int *, int **, int *);
void PegaMaiorCaminho(int, int, int *, int **, MaiorCaminho *);

int main (void){
	
	int n_vertices; /* auto-explicativo, contém o número de vértices do grafo; valor máximo = 15 */
	int **matriz; /* ponteiro para gerar dinamicamente a matriz de adjacência conforme o número de vértices */
	int aux1, aux2; /* contador auxiliar */
	
	if ( matriz = LeArquivo ("TrabGrafos.txt", &n_vertices, matriz) ){
		
		ImprimeMatriz (matriz, n_vertices);	
		CalculaCintura (matriz, n_vertices);		
		CalculaDiametro (matriz, n_vertices);
		getchar();
		exit(1);
	}
	else{
		printf ("Erro ao abrir o arquivo.\n");
		getchar();
		exit(1);
	}
}

int **LeArquivo (char *nome_arquivo, int *n_vertices, int **matriz){
/*
	return matriz: arquivo carregado com sucesso
	return NULL: erro ao abrir o arquivo
*/
	FILE *arq; /* descritor para o arquivo que será lido */
	char buffer[TAMANHO]; /* buffer que contém a string lida do arquivo */
	char *buffer_vertice;
	int vertice1; /* captura o segundo vértice de cada linha para ligar a aresta */
	int vertice2; /* captura o segundo vértice de cada linha para ligar a aresta */
	int arestas; /*  conta o número de arestas do grafo */
	int aux1, aux2; /* contadores auxiliares */
	
	if ((arq = fopen(nome_arquivo, "r")) == NULL){
		fclose(arq);
		return NULL; /* main reconhece que houve erro ao abrir o arquivo */
    }
	else{	
		printf("Arquivo aberto.\n\n");
		printf("Preparando criacao do grafo.\n");
		printf("Caracteristicas do grafo:\n");
		memset(buffer,'\0',strlen(buffer)); /* zera buffer */
		fgets(buffer, sizeof(buffer), arq);
		*n_vertices = atoi(buffer); /* transforma o conteúdo de buffer em um inteiro */
		if( 1 <= *n_vertices && *n_vertices <= 15 )
			printf("\t-> Numero de vertices: %d\n\n", *n_vertices);
		else{
			printf("\t-> Numero de vertices fora dos limites permitidos.\n\n");
			system("pause");
			exit(1);
		}
		
		/* Gerando matriz de adjacência */
		matriz = malloc(*n_vertices * sizeof(int));
		for (aux1 = 0; aux1 < *n_vertices; aux1++)
			matriz[aux1] = malloc(*n_vertices * sizeof(int));
		/* Iniciaizando a matriz de adjacência */
		for (aux1 = 0; aux1 < *n_vertices; aux1++)	
			for (aux2 = 0; aux2 < *n_vertices; aux2++)
				matriz[aux1][aux2] = 0; /* inicialmente todos os vértices são desconexos */
			
		printf("Matriz de adjacencia gerada com sucesso!.\n");
		printf("Inicializando matriz de adjacentia.\n");
		printf("Vertices adjacentes (que contem uma aresta entre eles):\n");
		
		arestas = 0;
		while (1){ 
			memset(buffer,'\0',strlen(buffer)); /* zera buffer */
			fgets(buffer, sizeof(buffer), arq); /* pega a linha que o ponteiro arq esta apontando e coloca em "buffer" */
			if ( strcmp(buffer,"@\n") == 1 ){ /* se a condição do if for verdade buffer contém o caractere '@' */
				break; /* sai do while */
			}
			else{
				buffer_vertice = strtok(buffer," ");
				vertice1 = atoi(buffer_vertice);
				buffer_vertice = strtok(NULL,"\n");
				vertice2 = atoi(buffer_vertice);
				if (1 <= vertice1 && vertice1 <= *n_vertices && 1 <= vertice2 && vertice2 <= *n_vertices){
					arestas++;
					printf ("\t%d) u: %d, v: %d\n", arestas, vertice1, vertice2);
					/* Inserindo aresta na matriz */
					if (matriz[vertice1-1][vertice2-1] < 1)
						matriz[vertice1-1][vertice2-1] = matriz[vertice1-1][vertice2-1] + 1;
					if (matriz[vertice2-1][vertice1-1] < 1)	
						matriz[vertice2-1][vertice1-1] = matriz[vertice2-1][vertice1-1] + 1;
                }
				else
					printf ("\t-> par de vertices invalido\n");	
			}	
		}	
	}
	fclose(arq);
	return matriz; /* sucesso na leitura do arquivo */		
}

void ImprimeMatriz (int **matriz, int n_vertices){
	/* Imprime matriz de adjacência na tela */
	int aux1, aux2;
	printf ("\nMatriz de adjacencia preenchida:\n");
	printf ("    ");
	for (aux1 = 1; aux1 <= n_vertices; aux1++)
		if (aux1 < 10)
			printf("%d  ", aux1);
		else 
			printf("%d ",aux1);
	for (aux1 = 1; aux1 <= n_vertices; aux1++){
           if (aux1 < 10)
			printf("\n%d   ", aux1);
		else 
			printf("\n%d  ", aux1);
		for (aux2 = 1; aux2 <= n_vertices; aux2++){
			if (matriz[aux1-1][aux2-1] == 0)
				printf ("-  ");
			else
				printf ("%d  ", matriz[aux1-1][aux2-1]);
		}
	}	
	printf ("\n**O caractere '-' foi utilizado no lugar do valor 0 para facilitar a visualização da matriz\n\n");
}

void CalculaCintura (int **matriz, int n_vertices ){
	ListaCiclo ciclo_calculando, ciclo_definitivo;
	int aux1, aux2;
	
	/* Inicializando as estruturas de ciclo */
	ciclo_calculando.ciclo = malloc ( n_vertices * sizeof(int) );
	ciclo_definitivo.ciclo = malloc ( n_vertices * sizeof(int) );
	ciclo_definitivo.tamanho = INFINITO;
	for (aux1 = 0; aux1 < n_vertices; aux1++){ 
		ciclo_definitivo.ciclo[aux1] = -1; /* inicializado apenas uma vez, pois depois terá resultados de ciclos */
		ciclo_calculando.ciclo[aux1] = -1;
    }
	
	/* Procurando os ciclos */	
	for (aux1 = 0; aux1 < n_vertices; aux1++){
		printf ("Vertice de origem: %d\n", aux1+1);
		ciclo_calculando.tamanho = 0;
		ciclo_calculando.first_vertice = aux1;
		InsereVerticeLista (&ciclo_calculando, aux1);
		CalculaCiclo (&ciclo_calculando, &ciclo_definitivo, aux1, n_vertices, matriz);		
		if ( ciclo_definitivo.tamanho == 3 )
			break; /* sai do for */
		ExcluiVerticeLista (&ciclo_calculando, aux1);			
	}			
	
	/* Ciclos já calculados - mostrar caminho do ciclo */ 	
	if ( ciclo_definitivo.tamanho == INFINITO )
		printf ("O grafo nao tem ciclos.");
	else{   
        printf ("\nA cintura do grafo tem tamanho: %d\n", ciclo_definitivo.tamanho);
        printf ("Caminho da cintura: ");
		for (aux2 = 0; aux2 < ciclo_definitivo.tamanho; aux2++)
    	    printf ("%d - ", ciclo_definitivo.ciclo[aux2]+1);
		printf ("%d\n", ciclo_definitivo.ciclo[0]+1);
    	getchar();
    }
}

int InsereVerticeLista (ListaCiclo *ciclo, int vertice_ciclo){ 
/* 	retorno 1: sucesso na inclusão do vertice_ciclo 
	retorno 0: vertice_ciclo já está na lista, logo aquela aresta não pode ser contabilizada no ciclo
*/
	int aux1;
	for (aux1 = 0; aux1 < ciclo->tamanho+1; aux1++){ /* Primeiro testa se o vertice_ciclo está na lista 'ciclo' da struct */
		if (ciclo->ciclo[aux1] == vertice_ciclo){
            printf ("Vertice %d ja foi visitido.\n", vertice_ciclo+1);                      
			return 0; /* vertice_ciclo já está na lista */
        }
		if (ciclo->ciclo[aux1] == -1){
			ciclo->ciclo[aux1] = vertice_ciclo;
			ciclo->tamanho = ciclo->tamanho + 1;
			break; /* sai do laço for */
		}
	}
	for (aux1 = 0; aux1 < ciclo->tamanho; aux1++)
	    printf ("%d - ", ciclo->ciclo[aux1]+1);
    printf ("\b\b  \n"); //getchar();
       
	return 1; /* vertice_ciclo foi inserido na lista do ciclo */
}

void ExcluiVerticeLista (ListaCiclo *ciclo, int vertice_ciclo){ 
	int aux1;
	for (aux1 = 0; aux1 < ciclo->tamanho; aux1++){ /* Primeiro testa se o vertice_ciclo está na lista 'ciclo' da struct */
		if (ciclo->ciclo[aux1] == vertice_ciclo){
			ciclo->ciclo[aux1] = -1;
			ciclo->tamanho = ciclo->tamanho - 1;
			break; /* sai do laço for */
		}
	}
}

void CalculaCiclo (ListaCiclo *ciclo, ListaCiclo *ciclo_definitivo, int vertice, int n_vertices, int **matriz){
	int aux1, aux2;
	
	for (aux1 = 0; aux1 < n_vertices; aux1++){
		if ( matriz[vertice][aux1] == 1 ){
			/* Foi encontrado uma aresta de ligação entre os vértices, logo deve inserir aux1 na lista e começar a ver as adjacências de aux1 */
			if ( InsereVerticeLista (ciclo, aux1) ){ /* Se o if tiver true como resultado, então inseriu com sucesso, logo pode chamar a recursão  */
				CalculaCiclo (ciclo, ciclo_definitivo, aux1, n_vertices, matriz);
				ExcluiVerticeLista (ciclo, aux1);
			}
			else /* retorno de InsereElementoLista foi zero, ou seja, a aresta não pôde ser inserida, logo tem que ver se fechou um ciclo ou se deve procurar outro vértice */
				if (ciclo->first_vertice == aux1 && ciclo->tamanho > 2){
                    printf ("\nCalculaCiclo: achou um ciclo\n");
					printf("\tTamanho do ciclo anterior: %d.\n", ciclo_definitivo->tamanho);
                    printf("\tTamanho do recem calculado: %d.\n", ciclo->tamanho);                       
					if (ciclo->tamanho < ciclo_definitivo->tamanho){
						printf ("Ciclo menor encontrado. Salva novo ciclo.\n\n");
						ciclo_definitivo->tamanho = ciclo->tamanho; /* coloca o menor ciclo no ciclo definitivo */
						ciclo_definitivo->first_vertice = ciclo->first_vertice;
						for (aux2 = 0; aux2 < ciclo->tamanho; aux2++)
						    ciclo_definitivo->ciclo[aux2] = ciclo->ciclo[aux2];						
						break; /* sai do laço for */
                    }
                }
				else
					continue; /* a aresta não pode ser inserida, então procura outra */
		}
	}	
}

void CalculaDiametro ( int **matriz, int n_vertices ){
	int **route2;   //é uma matriz n_vertices x n_vertices
	int *menor_caminho;  /*  */
	int *visited;  /* array que armazena os vertices visitados */ 
	int first_time = 1;
	int aux1, aux2, aux3;
	MaiorCaminho caminho;

	/* Inicializando estrutura caminho */
	caminho.maior_caminho = 0;
	caminho.caminho = malloc( n_vertices * sizeof(int) ); /* aloca dinamicamente 'n_vertices posições no vetor da estrutura caminho' */
	
	for (aux1 = 0; aux1 < n_vertices; aux1++){	
		if (first_time){
			first_time = 0;
			menor_caminho = malloc( n_vertices * sizeof(int) ); 
			visited = malloc( n_vertices * sizeof(int) );
			route2 = malloc( n_vertices * sizeof(int) );
			
			for (aux2 = 0; aux2 < n_vertices; aux2++){
				route2[aux2] = malloc( n_vertices * sizeof(int) );
			}
		}
		
		/* Inicializa matriz de caminhos */
		for (aux2 = 0; aux2 < n_vertices; aux2++){
			visited[aux2] = 0; /* todos os vértices são inicializados como não visitados */
			menor_caminho[aux2] = INFINITO; /* define inicialemnte que a excentricidade de cada vértice do grafo é infinita */
			for (aux3 = 0; aux3 < n_vertices; aux3++)
				route2[aux2][aux3] = -1;
		}
		
		AchaCaminhos(aux1, n_vertices, matriz, visited, route2, menor_caminho);
		PegaMaiorCaminho(aux1, n_vertices, menor_caminho, route2, &caminho);
	}
	
	/* Mostrando resultado para o usuario */
	printf ("\nO diametro do grafo tem comprimento: %d\n", caminho.maior_caminho);
	printf ("Caminho do diametro: ");
	for (aux1 = 0; aux1 < n_vertices; aux1++)
	    if (caminho.caminho[aux1] != -1)
	       printf ("%d - ",caminho.caminho[aux1]);
	printf ("\b\b  \n");
}

void AchaCaminhos(int vertice_fonte, int n_vertices, int **matriz, int *visited, int **route2, int *menor_caminho){
	int i, j, k;
	int ek;

	menor_caminho[vertice_fonte] = 0;

	i=0;
	while( i++ < n_vertices ){
		//we will decide to which vertex is closer that is not in Y (not visited)
		for(j=0; j<n_vertices; j++){
			//if we find a vertex that is not Y, lets work on it
			if( visited[j] == 0 ){
				//if there is a connection with the vertexes
				if( matriz[vertice_fonte][j] != 0 ){
					//decide the shortest paths
					if( menor_caminho[j] > matriz[vertice_fonte][j] + menor_caminho[vertice_fonte] ){
						//we found more shortest way.. change the old one
						menor_caminho[j] = matriz[vertice_fonte][j] + menor_caminho[vertice_fonte];
						//printf ("menor_caminho: %d\n", menor_caminho[j]);
						for(k=0; k<n_vertices; k++){
							route2[j][k] = route2[vertice_fonte][k];
						}
						k=0;
						while(route2[j][k] != -1 ){
							k++;
						}
						route2[j][k] = vertice_fonte;	
					}
				}
			}
		}
		ek = INFINITO;
		for( j=1; j<n_vertices; j++){
			if( visited[j] == 0 ){
				if( menor_caminho[j] < ek ){
					ek = menor_caminho[j];
					vertice_fonte = j;
				}
			}
		}
		visited[ vertice_fonte ] = 1;
	}
	
	for( i=0; i<n_vertices; i++){
		if( route2[i][0] != -1 || vertice_fonte == i){
			k=0;
			while(route2[i][k] != -1 ){
				k++;
			}
			route2[i][k] = i;
		}
	}
}

/* Procura o maior dos menores caminhos e coloca em caminho.maior_caminho caso ele seja o maior */
void PegaMaiorCaminho(int vertice_fonte, int n_vertices, int *menor_caminho, int **route2, MaiorCaminho *caminho){
	int aux1, aux2;

	for (aux1 = 0; aux1 < n_vertices; aux1++){ 
		if( aux1 != vertice_fonte){
			if (menor_caminho[aux1] > caminho->maior_caminho){
				caminho->maior_caminho = menor_caminho[aux1];
                for (aux2 = 0; aux2 < n_vertices; aux2++)
                    if (route2[aux1][aux2] != -1)
			           caminho->caminho[aux2] = route2[aux1][aux2]+1;
                    else
                       caminho->caminho[aux2] = -1; 
            }
		}
	}
}






























