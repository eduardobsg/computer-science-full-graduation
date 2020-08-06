/*
  Name: converte_contatos.c
  Author: João Luiz Grave Gross
  Date: 02/07/09 15:35
  Description: Trasforma com dados de contatos em outro arquivo.
  
  " -> ignorar
  espaço -> ignorar
  < -> substituir por vírgula
  > -> substituir por \n
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLIN 80
#define MAXCHAR 31

void opcao_menu (void);
void edita_texto (int, int);
FILE *AbreArquivo (int, int);

int main()
{   
    char cod;
    do
    {    
         opcao_menu();
         fflush (stdin);
         scanf ("%c", &cod);     
         cod = toupper (cod);    
         if (cod =='E')
            edita_texto (MAXLIN, MAXCHAR); 
         if (cod =='I')
            insere_texto (MAXLIN, MAXCHAR);
         fflush (stdin);
         printf ("\n\n");
         system ("pause");
    } while (cod != 'F');
    return 0;
}

void opcao_menu()      //menu com as operaçoes
{    
     system ("CLS");
     printf ("O que deseja fazer?");
     printf ("\n- (E)ditar Texto");
     printf ("\n- (I)nserir Texto");
     printf ("\n- (F)im");
     printf ("\nCodigo: ");
}

FILE *AbreArquivo (int maxchar, int codigo)
{
	char nomearq[maxchar];
	if (!codigo)
	   printf("\nSalvar arquivo com o nome (Ex.: xxx.txt) (max de %d caracteres): ", maxchar - 1);
    else
       printf("\nAbrir arquivo com o nome (Ex.: xxx.txt) (max de %d caracteres): ", maxchar - 1); 
  	fflush(stdin);
	fgets(nomearq, sizeof(nomearq), stdin);
    if (nomearq[strlen(nomearq) - 1] == '\n')
 	   nomearq[strlen(nomearq) - 1] = '\0';
	if (!codigo)
	   return fopen (nomearq, "w+");
    else
	   return fopen (nomearq, "r");
}

void edita_texto (int maxlin, int maxchar)
{
    FILE *arq_origem, *arq_destino;
    char linha[maxlin];
    int i;
    if (!(arq_origem = AbreArquivo (maxchar, 1)))
       printf ("\nErro ao abrir o arquivo");
    else
    {    
        if (!(arq_destino = AbreArquivo (maxchar, 0)))
           printf ("\nErro ao abrir o arquivo"); 
        else
        {
            fgets (linha, sizeof linha, arq_origem);
            while ((strcmp(linha, "FIM")))
            {
                  for (i = 0; i < strlen(linha); i++)
                  {
                      if (linha[i] == '<')
                      {
                         putc (',', arq_destino);
                         //printf ("\n,");
                      }
                      else
                          if (linha[i] == '>')
                          {
                             putc ('\n', arq_destino);
                             i = strlen (linha);
                          }   
                          else
                              if (linha[i] == ' ')
                              {
                                 if (!(linha[i+1] == '<'))
                                    putc (linha[i], arq_destino);
                              }   
                              else                          
                                 if (!(linha[i] == '"'))
                                    putc (linha[i], arq_destino);
                  }     
                  fgets (linha, sizeof linha, arq_origem);
            }
        }
    }
    fclose (arq_origem);
    fclose (arq_destino);
}

