#include <stdio.h>
#include <conio.h>
#include <string.h>



typedef struct T_Produto {
        int cod;
        char nome[40];
        float preco;       
}TProduto;


void inicializa (TProduto t[], int *inicio, int *fim);
int consulta (TProduto t[], int inicio , int fim, int posicao);
void insere (TProduto t[], int *inicio, int *fim, int posicao);
void imprime (TProduto t[]);
int remove ( TProduto t[], int *inicio, int *fim, int posicao);
