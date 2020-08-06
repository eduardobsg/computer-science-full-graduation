#include "caminhamentos.h"

int main()
{
    int i, j; 
    int grafo[max+1][max+1]; //mariz de adjacência
    int vis[max+1]; //vetor de vértices visitados
  
    //para inicializar o gráfo com 0
    for (i = 1; i <= max; i++)
        for (j = 1; j <= max; j++)
            grafo[i][j] = 0;  

    //inicializando vetor de vertices visitados
    for (i = 1; i <= max; i++)
        vis[i] = false; 

    //inicializando matriz de adjacência    
    grafo[1][2]=1;
    grafo[1][3]=1;
    grafo[2][4]=1;
    grafo[3][4]=1;
    grafo[3][5]=1;
    grafo[4][5]=1;
    grafo[4][6]=1;
    grafo[4][8]=1;
    grafo[6][5]=1;
    grafo[8][7]=1;
    grafo[7][2]=1;
    
    i = 1;
    puts ("DFS"); //imprime na tela "DFS"
    DFS (grafo, i, vis); //grafo: matriz de adjacência, i = 1, vis: vetor de vértices visitados
    
    //inicializando vetor de vertices visitados
    for (i = 1; i <= max; i++)
        vis[i] = false;

    puts ("BFS");
    i = 1;
    BFS (grafo, i, vis);

    system("pause");	
    return 0;
}
