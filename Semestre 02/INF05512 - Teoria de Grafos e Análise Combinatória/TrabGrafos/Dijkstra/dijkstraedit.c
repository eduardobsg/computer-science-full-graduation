#include <stdio.h>
#include <stdlib.h>       
#include <string.h>      
#include <time.h> 
 
#define MALLOC(t,n)    (t *) malloc( n*sizeof(t) ) 
#define MALLOC2D(t,n)  (t **) malloc(n*sizeof(t) )
#define CHECKPTR(p)    if (!p) Error("Out of memory")

#define INFINITO 999999999

int n_vertices;
int **paths;    //é uma matriz n_vertices x n_vertices
int **route2;   //é uma matriz n_vertices x n_vertices
int *menor_caminho;  //o vertex in baslangica en kisa yolu
int *visited;   //Y a dahil olanlarý isaretlenmis gibi gosterecegiz
int first_time = 1;

typedef struct maior_caminho{
	int maior_caminho;
	int *caminho;
} MaiorCaminho;

MaiorCaminho caminho;

void Error (char *str){ 
	printf("\nERROR: %s\n", str);
	return;
}

//////////////////////////////////////
//  rmy_vertexs the file and built the synamic structure 
//////////////////////////////////////
void readFileBuiltStruct(char *str){
	FILE *fpRead;
	int i,j;
	int num;
			
	if (first_time)	{
		first_time = 0;
		printf("Entrou no first\n");	

		fpRead = fopen(str,"r"); //abre o arquivo com o nome str e o referencia pelo descritor 'fpRead'
	
		//começa a leitura do arquivo de entrada (nesse caso input.txt)
		rewind(fpRead);
		fscanf(fpRead, "%d", &n_vertices); //pega o valor da primeira linha do arquivo e salva em 'n_vertices' (número de vértices do grafo)
		
		//faz mallocs e procura erros
		menor_caminho = MALLOC( int, n_vertices ); //MALLOC: macro definida logo após a inclusão das headers
		CHECKPTR( menor_caminho ); //se o ponteiro 'menor_caminho' for null então indica erro

		visited = MALLOC( int, n_vertices );
		CHECKPTR( visited );

		paths = MALLOC2D( int , n_vertices );
		CHECKPTR( paths );

		route2 = MALLOC2D( int , n_vertices );
		CHECKPTR( route2 );

		for(i=0; i<n_vertices; i++){
			paths[i] =  MALLOC( int , n_vertices );
			CHECKPTR( paths[i] );

			route2[i] = MALLOC( int , n_vertices );
			CHECKPTR( route2[i] );
			
			for(j=0; j<n_vertices; j++){
				fscanf ( fpRead, "%d", &num);
				paths[i][j] = num;
			}
		}
		fclose( fpRead );
	}
	//lê as informações de peso das arestas no arquivo e salva na matriz path
	for(i=0; i<n_vertices; i++){
		visited[i] = 0; //todos os vértices são inicializados como não visitados
		menor_caminho[i] = INFINITO; //define inicialemnte que a excentricidade de cada vértice do grafo é infinita
		for(j=0; j<n_vertices; j++){
			route2[i][j] = -1;
		}
	}
	
}

//////////////////////////////////////
//  find the shortest paths for the beginnig vertex
//  and store the routines that on which vertex can we go..
//////////////////////////////////////
void findTheRotutines(int source){
	int i, j, k;
	int my_vertex;
	int ek;

	menor_caminho[source] = 0;
	my_vertex = source; //o anda uzerinde islem yaptigimiz dugum..

	i=0;
	while( i++ < n_vertices ){
		//we will decide to which vertex is closer that is not in Y (not visited)
		for(j=0; j<n_vertices; j++){
			//if we find a vertex that is not Y, lets work on it
			if( visited[j] == 0 ){
				//if there is a connection with the vertexes
				if( paths[my_vertex][j] != -1 ){
					//decide the shortest paths
					if( menor_caminho[j] > paths[my_vertex][j] + menor_caminho[my_vertex] ){
						//we found more shortest way.. change the old one
						menor_caminho[j] = paths[my_vertex][j] + menor_caminho[my_vertex];
						for(k=0; k<n_vertices; k++){
							route2[j][k] = route2[my_vertex][k];
						}
						k=0;
						while(route2[j][k] != -1 ){
							k++;
						}
						route2[j][k] = my_vertex;	
					}
				}
			}
		}
		ek = INFINITO;
		for( j=1; j<n_vertices; j++){
			if( visited[j] == 0 ){
				if( menor_caminho[j] < ek ){
					ek = menor_caminho[j];
					my_vertex = j;
				}
			}
		}
		visited[ my_vertex ] = 1;
	}
	
	for( i=0; i<n_vertices; i++){
		if( route2[i][0] != -1 || source == i){
			k=0;
			while(route2[i][k] != -1 ){
				k++;
			}
			route2[i][k] = i;
		}
	}
}

/* Procura o maior dos menores caminhos e coloca em caminho.maior_caminho caso ele seja o maior */
void PegaMaiorCaminho(int source){
	int aux1, aux2;

	for (aux1 = 0; aux1 < n_vertices; aux1++){ 
		if( aux1 != source){
			if (menor_caminho[aux1] > caminho.maior_caminho){
				caminho.maior_caminho = menor_caminho[aux1];
                for (aux2 = 0; aux2 < n_vertices; aux2++)
                    if (route2[aux1][aux2] != -1)
			           caminho.caminho[aux2] = route2[aux1][aux2]+1;
                    else
                       caminho.caminho[aux2] = -1; 
            }
		}
	}
}
 
int main(void){
	FILE *arq;
	int aux;
	
	arq = fopen( "input.txt" , "r" );
	rewind(arq);
	fscanf(arq, "%d", &n_vertices); //pega o valor da primeira linha do arquivo e salva em 'n_vertices' (número de vértices do grafo)
	fclose( arq );

	/* Inicializando estrutura caminho */
	caminho.maior_caminho = 0;
	caminho.caminho = MALLOC( int, n_vertices ); /* aloca dinamicamente 'n_vertices posições no vetor da estrutura caminho' */
	
	for (aux = 0; aux < n_vertices; aux++){	
		readFileBuiltStruct("input.txt");
		findTheRotutines( aux );
		PegaMaiorCaminho(aux);
	}
	
	/* Mostrando resultado para o usuario */
	printf ("Comprimento do maior caminho: %d\n", caminho.maior_caminho);
	printf ("Caminho: ");
	for (aux = 0; aux < n_vertices; aux++)
	    if (caminho.caminho[aux] != -1)
	       printf ("%d ",caminho.caminho[aux]);
	
    system("pause");
		
	return 0;
}
