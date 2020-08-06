/* 1) Usando a função Insere a 1ª vez, cria a pilha. Se uma uma 2ª vez Topo=NULL e a pilha se perde. */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "Aula09_Pilhas_TAD.h"

int menu (void);

int main (void)
{
    int i, estado, cont, *pcont;
    pcont = &cont; //pcont aponta para cont
    char c;
    float preco;
    TipoPilha* Topo;
    TipoPilha* *pTopo;
    pTopo = &Topo;
    TipoInfo Dado;
    do
    {     
        switch (i = menu ())
        {
               case 1: /* TipoPilha* */ Topo = InicializaPilha (Topo, pcont); //Topo recebe NULL
                       printf ("\nLista criada com sucesso\n");
                       //Como provar para o usuário que a lista foi criada?
                       //Como imprimir o NULL contido em "Topo", tentei printf ("
                       break;
               case 2: printf ("\nInserir preco: "); 
                       scanf ("%f", &Dado.preco);
                       /* TipoPilha* */ Topo = InsereNodo (Topo, Dado, pcont);
                       break;
               case 3: if (estado = RemoveNodo (Topo, pcont))
                          printf ("Nodo removido");
                       else
                          printf ("Lista ja estava vazia");   
                       //Topo não atualiza na função Remove Nodo, por isso ao imprimir os dados após a remoção a ordem aparece errada 
                       //printf ("Topo = %d, Nodo topo = %f", Topo, Topo->dado.preco);
                       break;
               case 4: /* TipoPilha* */ preco = ConsultaNodo (Topo);
                       printf ("(%d) Preco = %.f", cont, preco);
                       break;
               case 5: /* TipoPilha* */ DestroiPilha (Topo, pcont);
                       break;
               case 6: ImprimePilha (Topo, cont);
                       break;
        }
        printf ("\n");
        system ("pause");
    } while (i);
    
    system ("pause");
    return 0;
}

int menu ()
{
    int i;
    system ("CLS");
    printf ("O que deseja fazer?\n");
    printf ("1 - Criar Pilha\n");
    printf ("2 - Inserir Nodo na Pilha\n");
    printf ("3 - Remove Nodo da Pilha\n");
    printf ("4 - Consultar Nodo do Topo da Pilha\n");
    printf ("5 - Destroi Pilha\n");
    printf ("6 - Imprime Pilha\n");
    printf ("0 - Sair\n");
    printf ("Codigo: ");
    scanf ("%d", &i);
    return i;
}
