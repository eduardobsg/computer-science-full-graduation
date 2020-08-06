/* 
1) Crie uma função que receba 2 pilhas (P1 e P2) cujos campos de 
informação são formados por 1 campo inteiro. A função deve comparar 
as 2 pilhas e retornar 1 caso elas sejam iguais e 0 caso sejam diferentes.

COmpara as duas pilhas -> se forem iguais retornar 1

***A função deve usar somente os procedimentos/funções do TAD.

Faça um programa principal para testar a função com as pilhas abaixo:

Exemplo:

Pilha 1: 
         4
	      3
	      2
         1
         
Pilha 2:
         3
         2
         1
         
Pilha 3:
         4
	      3
	      2
         1    

*/

//Destruindo as Pilhas
#include <stdlib.h>
#include <stdio.h>
#include "Pilha.h"

TipoPilha* CriaPilha1 (TipoPilha *);
TipoPilha* CriaPilha2 (TipoPilha *);
TipoPilha* CriaPilha3 (TipoPilha *);

int main ()
{  
       TipoPilha *Pilha1, *Pilha2, *Pilha3;
       int i; 
        
       //Testa se Pilha1 == Pilha2
       printf ("Comparando Pilhas 1 e 2:\n"); 
       Pilha1 = CriaPilha1 (Pilha1);
       Pilha2 = CriaPilha2 (Pilha2);
       if (ComparaPilhas (Pilha1, Pilha2))
         printf ("\n\nPilhas 1 e 2 sao iguais\n\n");
       else
         printf ("\n\nPilhas 1 e 2 sao diferentes\n\n");
       system ("pause");
       
       //Testa se Pilha1 == Pilha3
       printf ("Comparando Pilhas 1 e 3:\n");  
       Pilha1 = CriaPilha1 (Pilha1);
       Pilha3 = CriaPilha3 (Pilha3);
       if (ComparaPilhas (Pilha1, Pilha3))
         printf ("\n\nPilhas 1 e 3 sao iguais\n\n");
       else
         printf ("\n\nPilhas 1 e 3 sao diferentes\n\n");  
         
       system ("pause");
       return 0;
}

TipoPilha* CriaPilha1 (TipoPilha *Pilha1)
{
       //Inicializa Pilha1
       Pilha1 = InicializaPilha (Pilha1);
       Pilha1 = PushPilha (Pilha1, 1);   
       Pilha1 = PushPilha (Pilha1, 2);   
       Pilha1 = PushPilha (Pilha1, 3);   
       Pilha1 = PushPilha (Pilha1, 4);  
       ImprimirPilha (Pilha1);
       return Pilha1;
}

TipoPilha* CriaPilha2 (TipoPilha *Pilha2)
{
       //Inicializa Pilha2
       Pilha2 = InicializaPilha (Pilha2);
       Pilha2 = PushPilha (Pilha2, 2);   
       Pilha2 = PushPilha (Pilha2, 3);   
       Pilha2 = PushPilha (Pilha2, 4);  
       ImprimirPilha (Pilha2);
       return Pilha2;
}

TipoPilha* CriaPilha3 (TipoPilha *Pilha3)
{
       //Inicializa Pilha3
       Pilha3 = InicializaPilha (Pilha3);
       Pilha3 = PushPilha (Pilha3, 1);   
       Pilha3 = PushPilha (Pilha3, 2);   
       Pilha3 = PushPilha (Pilha3, 3);   
       Pilha3 = PushPilha (Pilha3, 4); 
       ImprimirPilha (Pilha3);
       return Pilha3;
}

/*
//Desconstruindo e Reconstruindo as pilhas
#include <stdlib.h>
#include <stdio.h>
#include <Pilha.h>

int main ()
{
      TipoPilha *Pilha1, *Pilha2, *Pilha3;
   
      system ("pause");
      return 0;
}
*/




