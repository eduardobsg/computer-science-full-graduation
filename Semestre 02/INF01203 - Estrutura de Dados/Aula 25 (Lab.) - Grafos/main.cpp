#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main ()
{
    TipoFila *l;
    int mat[8][8] = {0};
    
    //Inicializando matriz de adjacência
    mat[0][1] = 1;
    mat[0][2] = 1;
    mat[1][3] = 1;
    mat[2][3] = 1;
    mat[2][4] = 1;
    mat[3][4] = 1;
    mat[3][5] = 1;
    mat[3][7] = 1;
    mat[5][4] = 1;
    mat[6][1] = 1;
    mat[7][6] = 1;
    
    //Caminhamento por Abrangência
    printf ("Caminhamento por Abrangencia:\n\n");    
    /* Inicializa lista */
    l = cria_fila(); 
    /* Insere o primeiro valor na lista */    
    l = insere (l, 1); 
    printf ("1 ");    
    cam_abrangencia (l, 0, mat); 
    
    //Caminhamento por Profundidade
    printf ("\n\nCaminhamento por Profundidade:\n\n");
    /* Inicializa lista */
    l = cria_fila();
    /* Insere o primeiro valor na lista */        
    l = insere (l, 1); 
    printf ("1 ");    
    cam_profundidade (l, 0, mat);
    
    printf ("\n\n");
    system ("pause"); 
    return 0;
}
