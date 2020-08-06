#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"


void colore (int grafo[max+1][max+1], int Vcor[max+1], int v)
{
     int i, cor, usada;
     cor = 1;
     do 
     {
        usada = 0;
        for (i = 1; i <= max; i++)
            if ((grafo[v][i] == 1) && (Vcor[i] == cor))
            usada = 1;
        if (usada == 1)
           cor++;
     } while (usada == 1);
     Vcor[v] = cor;
     printf ("vertice %d - cor %d\n", v, Vcor[v]); 
}

void DFS (int grafo[max+1][max+1], int v, int Vcor[max+1])
{
    int w;
    colore (grafo, Vcor, v);
    for (w = 1; w <= max; w++)    //percorre os vértices adjacentes a v
      if ((grafo[v][w] == 1) && (Vcor[w] == 0))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
         DFS(grafo, w, Vcor); //chamada recursiva para o vértice adjacente a v
}


void BFS (int grafo[max+1][max+1], int v, int Vcor[max+1])
{
    int w;
    TipoFila *FV;

    colore (grafo, Vcor, v);
    FV = cria_fila();
    FV = insere(FV, v);
    while (!vazia(FV))
    {
       v = remove (&FV);
       for(w = 1; w <= max; w++)    //percorre os vértices adjacentes a v
          if ((grafo[v][w] == 1) && (Vcor[w] == 0))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
          {
              FV = insere (FV, w);
              colore (grafo, Vcor, w);
           }
   
    }
}

