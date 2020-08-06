#include "llcircular.h"

#define MAX 5

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
int consulta ( TProduto t[], int inicio, int fim, int posicao) 
{
   int i;
   if ((posicao > fim - inicio + 1 ) || (posicao < 1))
      return -1;
   else 
      return t[inicio+posicao-1].cod;
}


/*inserindo registros na posicao solicitada*/
void insere ( TProduto t[], int *inicio, int *fim, int posicao) 
{
     int i, nelem, pos;
          
     // calculando o numero de elementos da lista para facilitar os testes      
     if (*inicio == -1 ) 
        nelem = 0;
     else 
          if (*inicio <= *fim) 
             nelem = *fim - *inicio + 1; 
          else 
             nelem = ((MAX-1) - *inicio + 1) + (*fim + 1);             
     if ((nelem == MAX) || (posicao > nelem +1) || (posicao < 1 ) || ((nelem == 0) && (posicao != 1)))
     {
        printf ("erro - nao e possivel inserir\n");
        return;
     }
     //insere primeiro elemento da lista         
     else  
           if (*inicio == -1) 
           {
              *inicio = 0;
              *fim = 0; 
           }      
           else 
                if ((*inicio + posicao -1) <= MAX-1) 
                   pos = *inicio + posicao -1;
                else 
                   pos = (-1 + posicao - ( (MAX-1) - *inicio + 1 )); // (inicio do arranjo -1)  + (posicao - inicio lista + 1)
     //insere no inicio da lista
     if (posicao == 1) 
     {
        if (*inicio > 0) 
        {
           pos = *inicio - 1;
           *inicio = *inicio - 1; 
        }
        else 
        {
             *inicio = MAX-1; 
             pos = MAX -1;
        }
        // inserção no final da lista
     }
     else 
     { 
          if (posicao == nelem + 1 ) 
             if (pos == *fim +1) 
                *fim = *fim + 1;
             else *fim = 0;
// inserção no meio da lista                              
          else 
          { 
               if (((*inicio <= *fim) && (*fim < MAX-1)) || ((*inicio > *fim) && (pos < *inicio)))
               {
                  for (i=*fim; i == pos; i--) 
                      t[i+1] = t[i];  
                  *fim = *fim +1;                                  
               }
               else 
               {
                    if (*fim != MAX-1) 
                    {
                       for (i=*fim; i == 0; i--) 
                           t[i+1] = t[i];  
                       t[0]=t[MAX-1];
                       for (i=MAX-2; i == pos; i--) 
                           t[i+1] = t[i];  
                       if (*fim == MAX-1) 
                          *fim = MAX-1;
                       else 
                            *fim = *fim +1;                                          
                    }                          
                    /* Lendo os dados*/ 
                    printf("Codigo: "); scanf("%d", &t[*inicio+posicao-1].cod); 
                    printf("Nome: "); scanf ("%s", t[*inicio+posicao-1].nome);
                    printf("Preco: "); scanf ("%f", &t[*inicio+posicao-1].preco);
               }
          }
     }
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
