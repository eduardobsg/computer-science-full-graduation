/*
  Exercício para a prova 3
  
  Estrutura:
            typedef struct item
            {
                    char modelo[10];
                    float preco;
            }
            
  Dados dois arquivo com estruturas do tipo item, gerar um terceiro arquivo com
  os dados dois dois arquivos recebidos, ordenando em ordem alfabética o campo modelo,
  neste terceiro arquivo

  Funções necessárias:
  - AbreArquivo -> lê nome do arquivo e abre
  - Ordena palavras -> recebe uma matriz de strings e cria outra matriz de strings
  com as palavras ordenadas por linha

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXNOME 80
#define NMODELOS 20

typedef struct item
{
        char modelo[10];
        float preco;
};

void menu (void);
FILE *CriaArquivo (int);
void InsereDados (FILE *);
void ListaDados (FILE *);
FILE *AbreArquivo (int); //número máximo de caracteres do nome do arquivo
int LeModelos (FILE *, char [][10], int, int); //função que lê os nomes dos modelos
int OrdemAlfabetica (char [][10], char [][10]);

int main ()
{
    FILE *arq1;
    FILE *arq2;
    FILE *arq3;
    char matmodelos[NMODELOS][10]; //número de palavras = valor de NMODELOS
                                   //número de caracteres = 11 (10 + '\0')
    char matmodelos2[NMODELOS][10] = {'\0'};
    int modeloslidos;                                                                      
    char codigo;
    
    do
    {
        menu ();
        fflush (stdin);
        scanf ("%c", &codigo);
        codigo = toupper (codigo); //deixa letra em maiúsculo
        if (codigo == 'C')
        {
           if (!(arq1 = CriaArquivo (MAXNOME)))
              printf ("\nErro ao criar o arquivo");
           else
           {
               InsereDados (arq1);
               fclose (arq1);
           }   
        }
        if (codigo == 'L')
        {
           if (!(arq1 = AbreArquivo (MAXNOME)))        
              printf ("\nErro ao abrir o arquivo");
           else
           {
               ListaDados (arq1);
               fclose (arq1);
           }
        }
        if (codigo == 'A')
        {
           if (!(arq1 = AbreArquivo (MAXNOME)))        
              printf ("\nErro ao abrir o arquivo");
           else
           {
              if (!(arq2 = AbreArquivo (MAXNOME)))        
                 printf ("\nErro ao abrir o arquivo");
              else
              {
                  printf ("\nOs dois arquivos foram abertos com sucesso.");
                  if (!(arq3 = CriaArquivo (MAXNOME)))        
                     printf ("\nErro ao abrir o arquivo");
                  else
                  {
                      modeloslidos = 0;
                      modeloslidos = LeModelos (arq1, matmodelos, modeloslidos, NMODELOS);
                      modeloslidos = LeModelos (arq2, matmodelos, modeloslidos, NMODELOS);
                      
                      OrdemAlfabetica (matmodelos, matmodelos2);
                                            
                      fclose (arq1);
                      fclose (arq2);
                      fclose (arq3);
                  }
              }
           }
        }
    } while (codigo != 'F');
    
    printf ("\n\n");
    system ("pause");
    return 0;
}

void menu ()
{
     printf ("\nO que deseja fazer?");
     printf ("\n(C)riar arquivo");
     printf ("\n(A)brir e concatenar dois arquivos");
     printf ("\n(L)istar dados do arquivo");
     printf ("\n(F)echar programa");
     printf ("\nCodigo: ");
}

FILE *CriaArquivo (int maxnome)
{
     char nomearq[maxnome];
     printf ("\n\nDigite o nome do arquivo para salvar: ");
     fflush (stdin);
     fgets (nomearq, sizeof (nomearq), stdin);
     if (nomearq[strlen(nomearq) - 1] == '\n')
        nomearq[strlen(nomearq) - 1] = '\0';
     return fopen (nomearq, "wb");
}

void InsereDados (FILE *arq)
{
    item buffer;
    int codigo;
    printf ("\nCadastro de produtos:");
    do
    {
        printf ("\n\nModelo do produto (ate 9 caracteres): ");
        fflush (stdin);
        fgets (buffer.modelo, sizeof (buffer.modelo), stdin);
        if (buffer.modelo[strlen(buffer.modelo) - 1] == '\n')
           buffer.modelo[strlen(buffer.modelo) - 1] = '\0';
        printf ("\nPreco: ");
        scanf ("%f", &buffer.preco);   
        fwrite (&buffer, sizeof (buffer), 1, arq);             
        do
        {
            printf ("\nDeseja inserir mais dados? 1 - sim | 0 - nao");
            printf ("\nCodigo: ");
            scanf ("%d", &codigo);
            if (codigo < 0 || codigo > 1)
               printf ("\n\tCodigo invalido.");
        } while (codigo < 0 || codigo > 1); 
    } while (codigo);
}

FILE *AbreArquivo (int maxnome)
{
     char nomearq[maxnome];
     printf ("\n\nDigite o nome do arquivo que deseja abrir: ");
     fflush (stdin);
     fgets (nomearq, sizeof (nomearq), stdin);
     if (nomearq[strlen(nomearq) - 1] == '\n')
        nomearq[strlen(nomearq) - 1] = '\0';
     return fopen (nomearq, "rb");
}

void ListaDados (FILE *arq)
{
    item buffer;
    printf ("\nLeitura de dados:");
    while (!(feof(arq)))
    {
          if (fread (&buffer, sizeof buffer, 1, arq)) //se for 1, quer dizer que leu
          {
             printf ("\n\nModelo do produto: %s", buffer.modelo);        
             printf ("\nPreco: %.3f", buffer.preco);
          }
    }
    printf ("\n\n");
}

int LeModelos (FILE *arq, char matmodelos[NMODELOS][10], int modeloslidos, int nmodelos)
{
    int i, j;
    item buffer; //buffer do tipo struct item
    for (i = modeloslidos; i < nmodelos; i++)
    {
        if (fread (&buffer, sizeof buffer, 1, arq)) //se for 1, quer dizer que leu
        {
            for (j = 0; j < 10; j++)
                matmodelos[i][j] = buffer.modelo[j];
            modeloslidos++;
        }
        else
            i = nmodelos; //fim do arquivo
    }   
    return modeloslidos;        
}

int OrdemAlfabetica (char matmodelos[][10], char matmodelos2[][10])
{
    int i, j, z, k, flag = 1;
    char modelo1[10], modelo2[10], modelo3[10];
 
    for (i = 0; i < NMODELOS; i++)
    {
        if (matmodelos[i][0] == '\0')
           i = NMODELOS;
        else
            printf ("\n(%d): %s", i, matmodelos[i]);
    }
 
    for (i = 0, z = 0; i < NMODELOS; i++)
    {
        strcpy (modelo1, matmodelos[i]);
        printf ("\nmodelo1: %s", modelo1);
        for (k = 0; k < 10; k++) 
            modelo1[k] = toupper (modelo1[k]);
        if (modelo1[0] == '\0')
        {
           j = NMODELOS;
           i = NMODELOS;
        }
        else
        {
            for (j = 0; j < NMODELOS; j++)
            {
                strcpy (modelo2, matmodelos[j]); 
                for (k = 0; k < 10; k++) 
                    modelo2[k] = toupper (modelo2[k]);
                printf ("\nmodelo1 = %s, modelo2 = %s\n", modelo1, modelo2);
                system ("pause");
                if (modelo2[0] == '\0')
                {
                   for (k = 0; k < 10; k++)
                       matmodelos2[z][k] = modelo1[k];
                   z++;
                   j = NMODELOS;
                }
                if ((strcmp (modelo1, modelo2)) == -1)
                    for (k = 0; k < 10; k++)
                       modelo1[k] = modelo2[k];
                   //modelo1 > modelo2 -> modelo2 vem antes na ordenação
            }
        }       
    }
 
    printf ("\n\nOrdenado:");
    for (i = 0; i < NMODELOS; i++)
    {
        if (matmodelos2[i][0] == '\0')
           i = NMODELOS;
        else
            printf ("\n(%d): %s", i, matmodelos[i]);
    }
 
    printf ("\n\n");
}

 













