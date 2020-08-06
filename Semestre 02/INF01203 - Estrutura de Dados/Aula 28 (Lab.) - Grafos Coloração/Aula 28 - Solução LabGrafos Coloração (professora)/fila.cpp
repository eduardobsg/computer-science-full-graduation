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
       TipoFila *ant = NULL; //ponteiro auxiliar para a posição anterior
       TipoFila *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoFila*) malloc(sizeof(TipoFila));
       
       /*insere a informação no novo nodo*/
       novo->info = dado;
       novo->prox = NULL;
       
       /*achando o final da fila*/
       while (ptaux!=NULL) 
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }
       
       /*encaeia o elemento*/
       if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
       {
               novo->prox = l;
               l = novo;
       }
       else 
           ant->prox = novo;
       
       return l;
}

int vazia (TipoFila* l)
{
     if (l == NULL) return 1;
     else return 0;
}


int remove(TipoFila **l)
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


  
       
