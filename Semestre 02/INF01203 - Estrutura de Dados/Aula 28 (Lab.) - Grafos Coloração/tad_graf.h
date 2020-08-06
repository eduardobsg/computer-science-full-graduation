//Estrutura de dades de um nodo do grafo
struct TipoFila
{
       int info; //número do nodo
       int cor; //número da cor
       TipoFila* prox;
};

//Retorna NULL
TipoFila* cria_fila(void);

//Insere um elemento em uma LSE
TipoFila* insere (TipoFila *l, int dado, char cor);

//Consulta se o nodo está na LSE. Se estiver retorna 1, caso contrário retorna 0
int consulta (TipoFila *l, int dado);

int consulta_cor (TipoFila *l, int nodo, int cor, int mat[6][6]);

//Caminhamento por Profundidade (DFS - Depth First Search)
void cam_profundidade (TipoFila *l, int dado, int mat[6][6]);

//Caminhamento por Adjacência (BFS - Breadth First Search)
void cam_adjacencia (TipoFila *l, int dado, int mat[6][6]); 

//Conta número de elementos pintados
int conta_nodos (TipoFila *l);

