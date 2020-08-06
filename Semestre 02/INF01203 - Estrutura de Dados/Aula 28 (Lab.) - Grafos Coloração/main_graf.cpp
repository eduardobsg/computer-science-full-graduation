#include <stdio.h>
#include <stdlib.h>
#include "tad_graf.h"

int main ()
{
    TipoFila *l;
    int mat[6][6]; //matriz de adjacência
    int i, j; //inicialização da matriz de adjacência
    char cor; //
    
    //Inicializando a matriz
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
            mat[i][j] = 0;
    
    //Inicializando matriz de adjacência
    mat[0][1] = 1;
    mat[0][5] = 1;
    mat[1][0] = 1;
    mat[1][2] = 1;
    mat[1][3] = 1;    
    mat[2][1] = 1;
    mat[2][3] = 1;
    mat[2][4] = 1;
    mat[3][1] = 1;
    mat[3][2] = 1;
    mat[3][4] = 1;
    mat[3][5] = 1;
    mat[4][2] = 1;
    mat[4][3] = 1;
    mat[4][5] = 1;
    mat[5][0] = 1;
    mat[5][3] = 1;
    mat[5][4] = 1;   
    
    //Caminhamento por Profundidade
    printf ("Caminhamento por Profundidade:\n\n");
    l = cria_fila(); //inicializa lista de nodos já coloridos
    l = insere (l, 0, 1); //insere o primeiro valor na lista de nodos coloridos
    printf ("Nodo inserido: 0, cor: 1\n");   
    cam_profundidade (l, 0, mat);
    
    //Caminhamento por Profundidade
    printf ("\n\nCaminhamento por Adjacencia:\n\n");
    l = cria_fila(); //inicializa lista de nodos já coloridos
    l = insere (l, 0, 1); //insere o primeiro valor na lista de nodos coloridos
    printf ("Nodo inserido: 0, cor: 1\n");   
    cam_adjacencia (l, 0, mat);
    
    printf ("\n\n");
    system ("pause"); 
    return 0;
}

