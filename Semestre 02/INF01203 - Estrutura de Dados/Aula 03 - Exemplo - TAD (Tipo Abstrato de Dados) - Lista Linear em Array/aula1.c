#include "aula1.h"

/*inicializando o vetor */
void inicializa ( TProduto t[], int *inicio, int *fim) {
     int i;
  
     for (i=0; i<MAX; i++) {
         strcpy(t[i].nome,"");
         t[i].cod=0;
         t[i].preco=0;
     }

     *inicio = -1;
     *fim = -1;
     
}


/*verifica se um elemento existe na lista*/
int consulta ( TProduto t[], int inicio, int fim, int posicao) {
   int i;

 if ( (posicao > fim - inicio + 1 ) || (posicao < 1))
      return -1;
  else 
      return t[inicio+posicao-1].cod;
}



/*inserindo registros na posicao solicitada*/
void insere ( TProduto t[], int *inicio, int *fim, int posicao) {
   int i;

   if ( ((*inicio == 0) && (*fim == MAX-1)) || //não tem espaço
         (posicao > *fim - *inicio + 2 ) || //posição inválida
         (posicao < 1) || //posição inválida
         ((*inicio == -1) && (posicao != 1 )) ) //lista vazia, só pode ser o primeiro
           {
             printf("erro - nao e possivel inserir\n");
             return ;
           }
   else if (*inicio ==-1) {
           *inicio = 0;
           *fim = 0; 
           }
           else if (*fim != MAX-1) {
                for (i=*fim; i >= *inicio + posicao -1; i--) //deslocando elementos para o final
                         t[i+1] = t[i];  
                *fim = *fim + 1;
        }
             else {
             for (i=*inicio; i <= *inicio + posicao-1; i++) //deslocando elementos para o inicio
                         t[i-1] = t[i];  
                *inicio = *inicio -1; 
        }
       /* Lendo os dados*/ 
       printf("Codigo: "); scanf("%d", &t[*inicio+posicao-1].cod); 
       printf("Nome: "); scanf ("%s", t[*inicio+posicao-1].nome);
       printf("Preco: "); scanf ("%f", &t[*inicio+posicao-1].preco);
}

/*remove o elemento da posição solicitada retornando seu código. Caso não exista, retorna -1.*/
int remove ( TProduto t[], int *inicio, int *fim, int posicao) {
   int i, rem=0;
   
   if ( (posicao > *fim - *inicio + 1 ) || (posicao < 1))
        return -1;
   else
   {
      rem =  t[*inicio+posicao-1].cod;
      for (i=*inicio+posicao-1; i <*fim; i++)
          t[i] = t[i+1];      
      strcpy(t[*fim].nome,"");
      t[*fim].cod=0;
      t[*fim].preco=0;
      *fim = *fim -1;
      return rem;
    }
}   
   
/*percorre o vetor, mostrando os elementos*/
void imprime (TProduto t[]) {
     int i;

     puts("Dados dos Produtos");
     for (i=0; i<MAX; i++) {
         printf("\nProduto %d\n", i);
         printf("Codigo = %d\n", t[i].cod);
         printf("Nome = %s\n", t[i].nome);
         printf("Preco = %4.2f\n", t[i].preco);

     } 
}
