#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

pNodoA* InsereArvore(pNodoA *a, int val)
{
     if (a == NULL)
     {
         a = (pNodoA*) malloc(sizeof(pNodoA));
         a->info = val;
         a->esq = NULL;
         a->dir = NULL;
         return a;
     }
     else 
          if (val < a->info)
              a->esq = InsereArvore(a->esq,val);
          else if (val > a->info)
              a->dir = InsereArvore(a->dir,val);          
     return a;
}

void preFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          printf("%c\n",a->info);
          preFixado(a->esq);
          preFixado(a->dir);
      }
}

void Central(pNodoA *a)
{
     if (a!= NULL)
     {
          Central(a->esq);
          printf("%c\n",a->info);
          Central(a->dir);
      }
}

void posFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          posFixado(a->esq);
          posFixado(a->dir);
          printf("%c\n",a->info);
      }
}

pNodoA* consultaABP(pNodoA *a, char chave) {
 
    while (a!=NULL){
          if (a->info == chave )
             return a; //achou então retorna o ponteiro para o nodo
          else
            if (a->info > chave)
               a = a->esq;
            else
               a = a->dir;
            }
            return NULL; //se não achou
}

pNodoA* consultaABP2(pNodoA *a, char chave) {
    if (a!=NULL) {
          

       if (a->info == chave)
         return a;
       else 
           if (a->info > chave)
                return consultaABP2(a->esq,chave);
            if (a->info < chave)
                return consultaABP2(a->dir,chave);
                
            else return a;
       }
       else return NULL;
}

//Calcula a altura da árvore
int altura (pNodoA *a, int *fator)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL) //ponto de parada
       return 0;  
    else
        Alt_Esq = altura (a->esq, fator);
        Alt_Dir = altura (a->dir, fator);     
        if (abs (Alt_Esq - Alt_Dir) > *fator)   
            *fator = abs (Alt_Esq - Alt_Dir);
        if (Alt_Esq > Alt_Dir)
           return (1 + Alt_Esq);
        else
           return (1 + Alt_Dir);
}

//Devolve o maior fator em módulo de uma ABP
void fator_ABP (pNodoA *a, int *fator)
{
    int fat;
    fat = altura (a, fator);
}
