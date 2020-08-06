#include <stdlib.h>
#include <conio.h>
#include "aula1.h"

int main ()
{
    int aluno;
    int cod;
   
    int op;
    TProduto Lista[MAX];
    int inicio, fim, posicao, resultadoConsulta, resultadoRemocao;
    
    inicializa(Lista, &inicio, &fim);  

    do
    {              
      system("cls");                   
      printf("1-Insere\n");
      printf("2-Consulta\n");   
      printf("3-Remove\n");   
      printf("4-Imprime\n");
      printf("0-Fim\n");      
      printf("Digite sua opcao: "); scanf("%d",&op);
      
      switch (op)
      {
          case 1:          
                 printf("\nInsere posicao: "); scanf("%d", &posicao);
                 insere (Lista, &inicio, &fim, posicao);
                 system("pause");break;
                 
          case 2:
                 printf("Consulta posicao: "); scanf("%d", &posicao); 
                 resultadoConsulta = consulta(Lista, inicio, fim, posicao);
                 printf("Codigo = %d\n\n", resultadoConsulta);
                 system("pause");break;
                 
          case 3:
                 printf("Remove posicao: "); scanf("%d", &posicao); 
                 resultadoRemocao = remove(Lista, &inicio, &fim, posicao);
                 if (resultadoRemocao == -1) 
                       printf("não foi possivel remover\n");
                   else
                       printf("Codigo = %d removido\n", resultadoRemocao);
                  system("pause");break;
                  
         case 4:
                 imprime (Lista); 
                 system("pause");
                 break;
      }
    } while (op != 0);
    
}

