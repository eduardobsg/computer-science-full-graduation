#include <stdio.h>
#include <stdlib.h>
#include "caminhamentos.h"

void visita (int vis[max+1], int v) //v: vértice visitado
{
     printf ("%d\n", v);
     vis[v] = true;
}

//Depth First Search - Cainhamento por Profundidade
void DFS (int grafo[max+1][max+1], int v, int vis[max+1]) //v: vértice visitado
{
    int w;
    visita (vis, v); //insere no vetor de vértices visitados o vértice visitado de valor "v"
    for (w = 1; w <= max ; w++) //percorre os vértices adjacentes a v
      if ((grafo[v][w] == 1) && (vis[w] == false))  //encontra um vértice adjacente a "v" que ainda nao tenha sido visitado
         DFS (grafo, w, vis); //chamada recursiva para o vértice adjacente a v
}

void BFS (int grafo[max+1][max+1], int v, int vis[max+1]) //v: vértice visitado
{
    int w;
    TipoFila *FV;
    visita (vis, v); 
    
    FV = cria_fila();
    FV = insere(FV, v); //insere vértice "v" na lista à qual FV aponta
    while (!vazia(FV)) //retorna 0: FV == NULL, retorna 1: FV != NULL
    {
       v = remove (&FV); //remove o primeiro elemento da lista à qual FV aponta e retorna o valor nodo removido
       for (w = 1; w <= max; w++) //percorre os vértices adjacentes a v
          if ((grafo[v][w] == 1) && (vis[w] == false))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
          {
              FV = insere(FV,w);
              visita (vis,w);
           }
   
    }
}
