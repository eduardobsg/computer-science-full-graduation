/*
   Crie uma função que receba 2 pilhas (P1 e P2) cujos campos de informação são formados 
por 1 campo inteiro. Estas pilhas estão ordenadas pelos campos de valor inteiro (ordem 
crescente a partir da base da pilha). A função deve retornar uma terceira pilha que contenha 
todos os elementos das 2 pilhas originais. A terceira pilha deverá estar, também, ordenada, 
em ordem crescente.

   A função deve usar somente os procedimentos/funções do TAD "Pilha.h"

   1. Faça um programa principal para testar a função com o exemplo abaixo:

Pilha 1:
6
5
2

Pilha 2:
7
4
3
1

Pilha 3 (união das pilhas 1 e 2):
7
6
5
4
3
2
1

*/

#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"


int main ()
{  
    TipoPilha *P1, *P2, *P_ordenada;
    TipoInfo dado;
    
    P1=InicializaPilha(P1);
    
    P1 = PushPilha(P1,2);
    P1 = PushPilha(P1,5);
    P1 = PushPilha(P1,6);
    
    ImprimirPilha(P1);
    
    P2=InicializaPilha(P2);
    P2 = PushPilha(P2,1);
    P2 = PushPilha(P2,3);
    P2 = PushPilha(P2,4);
    P2 = PushPilha(P2,7);
  
    ImprimirPilha(P2);
    
    P_ordenada = ordena(P1,P2);
  
    ImprimirPilha(P_ordenada);
          
    system("pause");
}
