#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

//define a estrutura de uma pilha de inteiros
struct TPtPilha{
        TipoInfo dado;
        struct TPtPilha *elo;        
};


//função que inicializa a pilha retornando NULL
TipoPilha* InicializaPilha (TipoPilha *Topo)
{
    return NULL;
}


//função que testa se a pilha está vazia (1) ou não (0)
int Vazia (TipoPilha *Topo)
{
    if (Topo==NULL)
       return 1;
    else
       return 0;
}

//função que mostra todos os elementos da pilha
void ImprimirPilha (TipoPilha *Topo)
{
     TipoPilha *ptaux;
     
     if (Topo != NULL)
     {
        puts("---Imprimindo pilha---");      
        for (ptaux=Topo; ptaux!=NULL; ptaux=ptaux->elo)
            printf("%d\n",ptaux->dado);
        puts("-------Fim pilha------");
     }
     else
       puts("Pilha vazia");

}

//função que insere na pilha apontada por Topo o dado recebido como parêmetro. 
//A pilha alterada é retornada ao programa principal
TipoPilha* PushPilha (TipoPilha *Topo, TipoInfo Dado)
{
       TipoPilha *novo; //novo elemento
       TipoPilha *ptaux = Topo; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoPilha*) malloc(sizeof(TipoPilha));
       novo->elo = NULL;
       
       /*insere a informação no novo nodo*/
       novo->dado = Dado;
       
       /*encaeia o elemento*/
       novo->elo = Topo;
       Topo = novo;
       return Topo;
}

//função que remove o elemento do topo da pilha
//o dado removido é retornado no parâmetro Dado
//a função retorna 1 caso tenha conseguido remover e 0 caso contrário
int PopPilha (TipoPilha **Topo, TipoInfo *Dado) //retorna 1 se exclui e zero se não exclui
{
   TipoPilha* ptaux;
   
   if (*Topo == NULL)
     return 0;   //não tem nada na pilha 
   else
   {
        *Dado = (*Topo)->dado;     // devolve o valor do topo 
        ptaux = *Topo;          //guarda o endereço do topo 
        *Topo = (*Topo)->elo;     //o próximo passa a ser o topo 
        free(ptaux);           //libera o que estava no topo 
        ptaux=NULL;
        return 1;    
   }
}
//função devolve o dado que está no topo da pilha
TipoInfo ConsultaPilha (TipoPilha *Topo)
{
 if (Topo==NULL)
   return 0;
 else
   return Topo->dado;
     
}

//função que libera todas as posições de memória ocupadas pela pilha retornando NULL
TipoPilha* DestroiPilha (TipoPilha *Topo)
{
        TipoPilha *ptaux;
        while (Topo != NULL)
        {
          ptaux = Topo;          //guarda o endereço do topo 
          Topo = Topo->elo;     //o próximo passa a ser o topo 
          free(ptaux);           //libera o que estava no topo   
        }  
        return NULL;
}
    
//função que recebe 2 pilhas ordenadas e retorna uma terceira pilha com todos os elementos, na mesma ordem
TipoPilha* ordena (TipoPilha *p1, TipoPilha *p2)
{
  TipoPilha  *ptaux3, *ptaux4;
  ptaux3=NULL;
  ptaux4=NULL;
  int v1,v2,v;

  while (ConsultaPilha(p1) || (ConsultaPilha(p2))) //enquanto pelo menos 1 das pilhas tiver dados
  {
        v1 = ConsultaPilha(p1);
        v2 = ConsultaPilha(p2);
        if (v1 > v2) //desempilha o maior elemento
          PopPilha(&p1,&v);
        else
          PopPilha(&p2,&v);
        if (v > 0) 
           ptaux3=PushPilha(ptaux3,v); //coloca o maior elemento em v3
  }
  while (ConsultaPilha(ptaux3))//transfere os elementos para a pilha final
  {
        PopPilha(&ptaux3,&v);
        ptaux4=PushPilha(ptaux4,v);
  }
 return ptaux4;
        
}      



    

