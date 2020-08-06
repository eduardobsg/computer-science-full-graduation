#include <stdio.h>
#include <stdlib.h>
#include "TAD_arvore.h"

/* Funções Exportadas para TAD_arvore.h */

//Função que inicializa a ABP, ou seja, o endereço da raiz é NULL
pNodoA* InicializaABP(pNodoA *raiz)
{
        return NULL;
}

//Função que Insere um nodo em uma ABP, valor inteiro
pNodoA* InsereNodoABP(pNodoA *raiz, int val)
{
    if (raiz == NULL)
    {
        raiz = (pNodoA*) malloc(sizeof(pNodoA));
        raiz->info = val;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    else
        if (val < (raiz->info))
           raiz->esq = InsereNodoABP(raiz->esq, val);
        if (val > (raiz->info))
            raiz->dir = InsereNodoABP(raiz->dir, val);
    return raiz;
}

//Função que imprime os nodos de uma ABP, usando caminhamento pré-fixado
void ImprimeABP(pNodoA *raiz)
{
     if (raiz)
     {
        printf ("%d\n", raiz->info);
        ImprimeABP(raiz->esq);    
        ImprimeABP(raiz->dir);     
        printf ("\n");
     }
}

//Função que determina a altura de um determinado nodo
int AlturaNodoABP(pNodoA *raiznodo)
{
    if (!raiznodo)
       return 0;
    else   
    {    
       if (AlturaNodoABP(raiznodo->esq) > AlturaNodoABP(raiznodo->dir))
          return AlturaNodoABP(raiznodo->esq) + 1;  
       else 
          return AlturaNodoABP(raiznodo->dir) + 1;      
    }
        
}

//Função que consulta se um determinado nodo está na ABP
pNodoA* ConsultaABP(pNodoA *raiz, int val) 
{
    while (raiz!=NULL)
    {
        if (raiz->info == val)
           return raiz; //achou retorna o ponteiro para o nodo
        else
            if (raiz->info > val)
               raiz = raiz->esq;
            if (raiz->info < val)
               raiz = raiz->dir;
    }
    return NULL; //não achou, retorna null
}

//Função que conta o número d nodos de uma ABP
int ContaNodosABP (pNodoA *raiz, int ch)
{
        if (raiz == NULL)
           return 0;
        else 
           return (1 + ContaNodosABP (raiz->esq, ch) + ContaNodosABP (raiz->esq, ch));
}

//Dado um valor, achar o pai do nodo que contém esse valor
pNodoA* AchaPai (pNodoA *raiz, int ch)
{
        if (raiz == NULL)
           return NULL;
        if (raiz->esq != NULL)
           if (raiz->esq->info == ch)
              return raiz;
        if (raiz->dir != NULL)
           if (raiz->dir->info == ch)
              return raiz;
        if (ch > raiz->info)
           return AchaPai (raiz->dir, ch);
        if (ch < raiz->info)
           return AchaPai (raiz->esq, ch);
        return NULL;
}

/*
Exclusão - Tratar:
a)  Quando o nó a ser excluído não contenha filhos:  
O nó simplesmente é removido.  
b)  Quando o nó a ser excluído contenha somente um dos filhos:  
O pai do nó a ser excluído passa a apontar para este filho e o nó é removido. 
c)  Quando o nó a ser excluído contenha os dois filhos:  
Busca-se o maior elemento da sub-árvore da esquerda (a partir da raiz da sub-árvore esquerda caminha-se sempre 
para a direita até achar um nó cujo filho à direita é nulo).  
Transfere-se a informação deste nó para o nó a ser removido e remove-se este novo nó, que cairá no caso (a) ou (b). 
Vamos deixar a cargo do aluno, como exercício, a implementação desta rotina.  
*/

pNodoA* ExcluiNodoABP (pNodoA *raiz, int ch)
{
}







