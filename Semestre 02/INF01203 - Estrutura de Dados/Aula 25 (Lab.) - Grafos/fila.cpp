#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h> //necessaria para o malloc
#include "fila.h"

TipoFila* cria_fila(void)
{
       return NULL;
}

TipoFila* insere (TipoFila *l, int dado)
{
       TipoFila *novo; //novo elemento
       TipoFila *ptaux; //*ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoFila*) malloc(sizeof(TipoFila));
       novo->info = dado;
       novo->prox = NULL;
                  
       if (l == NULL)
          l = novo;
       else
       {
          for (ptaux = l; ptaux->prox != NULL; ptaux = ptaux->prox); //acha o final da lista
          ptaux->prox = novo;          
       }
       return l;
}

//Consulta se o nodo está na LSE. Se estiver retorna 1, caso contrário retorna 0
int consulta (TipoFila *l, int dado)
{
    TipoFila *ptaux;
    ptaux = l;
    for (;ptaux != NULL; ptaux = ptaux->prox)
        if (ptaux->info == dado)
           return 1; //elemento está na lista
    return 0; //ptaux chegou a NULL, logo int dado não está na lista
}


//Caminhamento por Abrangência
void cam_abrangencia (TipoFila *l, int dado, int mat[8][8]) 
{ 
     for (int i = 0; i <= 7; i++) 
         if (mat[dado][i] == 1) 
            if (!(consulta (l, i+1))) //se for true, o retorno foi 0, e i não está na lista
            {
               l = insere (l, i+1); 
               printf ("- %d ", i+1); 
               cam_abrangencia (l, i, mat); 
            }
} 

//Caminhamento por Profundidade
void cam_profundidade (TipoFila *l, int dado, int mat[8][8]) 
{ 
     for (int i = 0; i <= 7; i++) 
         if (mat[dado][i] == 1) 
            if (!(consulta (l, i+1))) //se for true, o retorno foi 0, e i não está na lista
            {
               l = insere (l, i+1); 
               printf ("- %d ", i+1);
               cam_profundidade (l, dado, mat);                 
               cam_profundidade (l, i, mat); 
            }
} 



int vazia (TipoFila* l)
{
     if (l == NULL) 
        return 1;
     else 
        return 0;
}


int remove (TipoFila **l)
{
    TipoFila *rem = *l;
    int aux;
    
    if (!vazia(*l))
    {
      aux = (*l)->info;
      *l = (*l)->prox;
      free(rem);
      return (aux); 
    }  
    else return -1;
}

void imprime(TipoFila* l)
{
     TipoFila* ptaux;
     for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
         printf(" %d \n",ptaux->info);
}         


  
       
