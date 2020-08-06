#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

//define a estrutura de uma pilha de inteiros
struct TPtPilha
{
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

/*
Passos:
   1) Pega o topo da pilha 1 e 2
   2) Compara o topo da pilha 1 e 2
      2.1) Se forem iguais -> elimina os dois das pilhas 1 e 2 e copia-o na pilha 3 e prossegue
      2.2) Se Topo1 != Topo 2 -> pilhas diferentes
*/

//compara se duas pilhas são iguais, se forem retorna 1
//se as pilhas forem diferentes, retorna 0 
int ComparaPilhas (TipoPilha *Topo1, TipoPilha *Topo2)
{
      TipoInfo Dado1, Dado2;      
      int i1, i2;
      do
      {
         i1 = PopPilha (&Topo1, &Dado1); //Se i=1, excluiu, se i=0, pilha esá vazia
         i2 = PopPilha (&Topo2, &Dado2); //Se i=1, excluiu, se i=0, pilha esá vazia
         if (Dado1 != Dado2)
            return 0;
      } while (i1 && i2);
      return 1;
}
          



    

