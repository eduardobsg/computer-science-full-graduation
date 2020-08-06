#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h> //necessaria para o malloc
#include "tad_graf.h"

TipoFila* cria_fila(void)
{
       return NULL;
}

TipoFila* insere (TipoFila *l, int dado, char cor)
{
       TipoFila *novo; //novo elemento
       TipoFila *ptaux; //*ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoFila*) malloc(sizeof(TipoFila));
       novo->info = dado;
       novo->cor = cor;
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

//Caminhamento por Profundidade
void cam_profundidade (TipoFila *l, int dado, int mat[6][6]) 
{ 
     int cor, i;
     if (conta_nodos (l) < 6) //se for V ainda há elementos não pintados na lista
     {
         for (i = 0; i < 6; i++) 
             if (mat[dado][i] == 1) //pega "i" para colorir
             {
                if (!(consulta (l, i))) //vê se "i" já foi pintado, ou seja, se está na lista de nodos pintados
                {                       //se o if for true, o retorno foi 0, e i não está na lista
                   cor = 1; //primeira cor                     
                   while (consulta_cor (l, i, cor, mat))
                         cor++;
                   l = insere (l, i, cor); 
                   printf ("Nodo inserido: %d, cor: %d\n", i, cor);
                   cam_profundidade (l, i, mat);
                }     
             }       
         cam_profundidade (l, dado, mat);                 
     }
} 

//Caminhamento por Adjacência
void cam_adjacencia (TipoFila *l, int dado, int mat[6][6]) 
{ 
     int cor, i;
     if (conta_nodos (l) < 6) //se for V ainda há elementos não pintados na lista
     {
         for (i = 0; i < 6; i++) 
             if (mat[dado][i] == 1) //pega "i" para colorir
             {
                if (!(consulta (l, i))) //vê se "i" já foi pintado, ou seja, se está na lista de nodos pintados
                {                       //se o if for true, o retorno foi 0, e i não está na lista
                   cor = 1; //primeira cor                     
                   while (consulta_cor (l, i, cor, mat))
                         cor++;
                   l = insere (l, i, cor); 
                   printf ("Nodo inserido: %d, cor: %d\n", i, cor);
                   cam_profundidade (l, dado, mat);
                   cam_profundidade (l, i, mat);      
                }     
             }            
     }
} 

int consulta_cor (TipoFila *l, int nodo, int cor, int mat[6][6])
{
    TipoFila *ptaux, *ptaux2;
    for (ptaux = l; ptaux != NULL; ptaux = ptaux->prox)
        if (ptaux->cor == cor)
           if (mat[nodo][(ptaux->info)] == 1) //
              return 1; //cor não pode ser usada
           else
           {
               for (ptaux2 = ptaux->prox; ptaux2 != NULL; ptaux2 = ptaux2->prox)
                   if (ptaux2->cor == cor)
                      if (mat[nodo][(ptaux2->info)] == 1) 
                         return 1; //cor não pode ser usada
               return 0;
           }
    return 0; //ptaux chegou a NULL, logo a cor pode se usada
}

//Conta número de elementos pintados
int conta_nodos (TipoFila *l)
{
    TipoFila *ptaux;
    int cont;
    for (ptaux = l, cont = 0; ptaux != NULL; ptaux = ptaux->prox)
        cont++;
    return cont;
        
}
       
