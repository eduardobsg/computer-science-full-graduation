#include <stdio.h>
#include <stdlib.h>
#include "tad.avl.h"

//Declaração do tipo de dados (Tipo Nodo)
struct TNodoA
{
    TipoInfo info;
    int FB; //fator
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA; //struct TNodoA foi chamada de pNodoA

//Implementação das Funções

//Rotação para a Direita
pNodoA* rotacao_direita (pNodoA* pt)
{
    pNodoA *ptu;
    ptu = pt->esq; 
    pt->esq = ptu->dir; 
    ptu->dir = pt; 
    pt->FB = 0;
    pt = ptu; 
    return pt;
}

//Rotação para a Esquerda
pNodoA* rotacao_esquerda (pNodoA *pt)
{
    pNodoA *ptu;
    ptu = pt->dir; 
    pt->dir = ptu->esq; 
    ptu->esq = pt; 
    pt->FB = 0;
    pt = ptu; 
    return pt;
}

//Dupla Rotação para a Direita
pNodoA* rotacao_dupla_direita (pNodoA* pt)
{
    pNodoA *ptu, *ptv;
    ptu = pt->esq; 
    ptv = ptu->dir; 
    ptu->dir = ptv->esq; 
    ptv->esq = ptu; 
    pt->esq = ptv->dir; 
    ptv->dir = pt; 
    if (ptv->FB == 1)   
       pt->FB = -1;
    else 
       pt->FB = 0;
    if (ptv->FB == -1)  
       ptu->FB = 1;
    else 
       ptu->FB = 0;
    pt = ptv; 
    return pt;
} 

//Dupla Rotação para a Esquerda
pNodoA rotacao_dupla_esquerda (pNodoA *pt)
{
    pNodoA *ptu, *ptv;
    ptu = pt->dir; 
    ptv = ptu->esq; 
    ptu->esq = ptv->dir; 
    ptv->dir = ptu; 
    pt->dir = ptv->esq; 
    ptv->esq = pt; 
    if (ptv->FB == -1) 
       pt->FB = 1;
    else 
       pt->FB = 0;
    if (ptv->FB == 1) 
       ptu->FB = -1;
    else 
       ptu->FB = 0;
    pt = ptv; 
    return pt;
}

//Calcula a altura da árvore
int altura (pNodoA a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL) //ponto de parada
       return 0;  
    else
        Alt_Esq = altura (a->esq);
        Alt_Dsq = altura (a->dir);        
        if (Alt_Esq > Alt_Dir)
           return (1 + Alt_Esq);
        else
           return (1 + Alt_Dir);
}

//Calcula fator de um nodo
int calcula_fator (pNodoA a)
{
    return (altura (a->esq) - altura (a->dir));
}

//Vê se a árvore é AVL. 
//retorna 1: é AVL, retorna 0: não é AVL (mais de dois níveis de diferença)
int teste_AVL (pNodoA a) 
{ 
    int alt_esq, alt_dir; 
    if (a!=NULL) 
    { 
       alt_esq = Altura(a->esq); 
       alt_dir = Altura(a->dir); 
       return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) && (funcaoB (a->esq)) && (funcaoB (a->dir))); 
    } 
    else 
       return 1; 
}
