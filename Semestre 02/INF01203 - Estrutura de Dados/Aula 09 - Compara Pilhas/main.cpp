/*
   Crie uma função que receba 2 pilhas (P1 e P2) cujos campos de informação são formados 
por 1 campo inteiro. A função deve comparar as 2 pilhas e retornar 1 caso elas sejam iguais 
e 0 caso sejam diferentes.

   A função deve usar somente os procedimentos/funções do TAD "Pilha.h".

   1. Faça um programa principal para testar a função com as pilhas abaixo:

Pilha 1: 
4
3
2
1

Pilha 2:
4
3
2

Pilha 3:
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
    TipoPilha *P1, *P2;
    TipoInfo dado;
    
    P1=InicializaPilha(P1);
    
    P1 = PushPilha(P1,1);
    P1 = PushPilha(P1,2);
    P1 = PushPilha(P1,3);
    P1 = PushPilha(P1,4);
    ImprimirPilha(P1);
    
    P2=InicializaPilha(P2);
    
    //P2 = PushPilha(P2,1);
    P2 = PushPilha(P2,2);
    P2 = PushPilha(P2,3);
    P2 = PushPilha(P2,4);

    ImprimirPilha(P2);
    
    if (Compara(P1,P2))
      printf("pilhas iguais\n");
    else
      printf("pilhas diferentes\n");
    
   
    
   system("pause");
}
