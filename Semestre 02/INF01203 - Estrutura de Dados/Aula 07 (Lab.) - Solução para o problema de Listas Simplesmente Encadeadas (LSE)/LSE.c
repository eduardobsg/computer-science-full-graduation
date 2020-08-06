#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  //necessaria para o malloc
#include "LSE.h"



TipoPtNo* cria_lista(void)
{
       return NULL;
}

TipoPtNo* insere_fim (TipoPtNo* l, TipoInfoNo dados)
{
       TipoPtNo *novo; //novo elemento
       TipoPtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoPtNo*) malloc(sizeof(TipoPtNo));
       
       /*insere a informação no novo nodo*/
       novo->info = dados;
     
       novo->prox=NULL; //o novo é o último, logo não tem próximo.  
       
       if (l==NULL) //se a lista esta vazia o novo elemento será o primeiro
          l = novo;
       else
       { 
           //achando o final da lista      
           for (ptaux=l; ptaux->prox != NULL; ptaux=ptaux->prox); 
           
           //encadeia com o anterior
           ptaux->prox=novo;            
       }

       return l;
}
void imprime(TipoPtNo* l)
{
     TipoPtNo* ptaux;
     if (l)
       for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
           printf("\nTitulo = %s \nISBN = %s \nNumero de paginas= %d \n",ptaux->info.titulo,ptaux->info.isbn, ptaux->info.numpag);
     else
       printf("\nLista Vazia\n");
}         

TipoPtNo* destroi(TipoPtNo* ptLista)
{
   TipoPtNo *ptaux; //ponteiro auxiliar para percorrer a lista
   while (ptLista != NULL)
   {
         ptaux = ptLista;
         ptLista = ptLista->prox;
         free(ptaux);
   }
   free(ptLista);   
   printf("\nLista Destruida\n");
   return NULL;            
}   
