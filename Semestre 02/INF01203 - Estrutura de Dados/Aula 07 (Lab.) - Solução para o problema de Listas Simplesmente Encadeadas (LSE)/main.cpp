#include <stdio.h>
#include <stdlib.h>
#include "LSE.h"

int main(void)
{
    TipoInfoNo dados;
    char cont;
    
    TipoPtNo* l;
    l = cria_lista();
    do
    {
        printf("\nTitulo: "); scanf("%s",dados.titulo);
        printf("ISBN: "); scanf("%s",dados.isbn);
        printf("Numero de páginas: "); scanf("%d",&dados.numpag);
        l = insere_fim(l, dados);
        printf("Continua? \n"); 
        fflush(stdin);
        cont = getchar(); 
    }while (cont!='n');
    imprime(l);
    l=destroi(l);
    imprime(l);
    system("pause");
}
