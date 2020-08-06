/*
  Name: x180171.cpp
  Author: João Luiz Grave Gross
  Date: 18/05/09 13:38
  Description:
               
        Funções:
        1) preenche vetor com valores randômicos e apresenta o vetor gerado
        2) solicita ao usuário um valor para pesquisar usando o método descrito
        no enunciado
       
        Valores randômicos: rand() % 500 -> gera intervalo de 0 a 499
                                                rand() % 506 -> 0 a 505
                                                rand() % 506 - 5 -> -5 a 500
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 160

int preenchevetor ();
void mostravetor (int [MAX]);
void pesquisa (int [MAX]);

int main ()
{
        int v[MAX], i;
        for (i = 0; i < MAX; i++)
                v[i] = preenchevetor();
        mostravetor(v);       
        pesquisa(v);
       
        printf ("\n");
        system ("pause");
        return 0;
}

int preenchevetor (void)
{
        int x;
        x = rand () % 506 - 5;
        return x;
}

void mostravetor (int vetor[MAX])
{
        int i;
        printf ("Vetor gerado: \n");
        for (i = 0; i < MAX; i++)
                printf ("%d  ", vetor[i]);
}

void pesquisa (int vetor[MAX])
{
        int i, valor;
        printf ("\n\nDigite um valor inteiro: ");
        scanf ("%d", &valor);
       
        for (i = 0; i < MAX/2; i++)
        {
                if (valor == vetor[i])
                {
                        printf ("O valor %d foi encontrado na posicao %d", valor, i + 1);
                        i = MAX;
                }
                if (valor == vetor[MAX - 1 - i])
                {
                        printf ("O valor %d foi encontrado na posicao %d", valor, MAX - i);
                        i = MAX;
                }
        }
        if (i == MAX/2)
                printf ("O valor %d nao foi encontrado!", valor);
}
  	3  	y180171.cpp  	[text/plain]  	3,25 KB  	Baixar 

/*
  Name: y180171.cpp
  Author: João Luiz Grave Gross
  Date: 18/05/09 14:09
  Description:
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
#define MATRIZ 20
#define PRIMO 1229
#define FIBO 18

void geraprimos (int [PRIMO]);
void gerafibo (int [FIBO]);
void preenchematriz (int [MATRIZ][MATRIZ]);
int verdiagonalsecund (int [MATRIZ][MATRIZ], int [PRIMO], int [FIBO], int [MATRIZ]);
void mediaharmonica (int[MATRIZ], int);

int main ()
{
        int primos[PRIMO], fibo[FIBO], mat[MATRIZ][MATRIZ], media[MATRIZ], z, codigo;
        geraprimos(primos);
        gerafibo(fibo);
        preenchematriz(mat);       

//  Valores de teste:
//        mat[0][19] = 2;
//        mat[1][18] = 5;
//        mat[2][17] = 233;
//  mat[3][16] = 13;
       
        printf ("Menu: ");
        do
        {
            printf ("\n1 - apresetar valores primos e pertencentes a serie de fibonacci na diagonal secundaria.");
            printf ("\n2 - calcular a media harmonica desses numeros.");
            printf ("\nCodigo: ");
            scanf ("%d", &codigo);
            if (codigo < 1 || codigo > 2)
                    printf ("Codigo invalido");
        } while (codigo < 1 || codigo > 2);
        switch (codigo)
        {
                case 1: verdiagonalsecund(mat, primos, fibo, media);
                                break;
                case 2: z = verdiagonalsecund(mat, primos, fibo, media);
                                mediaharmonica(media, z);
        }
           
        printf ("\n");
        system ("pause");
        return 0;
}

void geraprimos (int vprimos[PRIMO])
{
        int i, div, num, result, j;
       
        for (i = 0, num = 2; num <= 10000; num++)
        {
                for (div = 1, j = 0; div <= num; div++)
                {
                        result = num / div;
                        if (num == result * div)
                                j++;
                }
                if (j == 2)
                {
                        vprimos[i] = num;
                        i++;
                }
        }
//        printf ("Vetor primos: \n");
//        for (i = 0; i < PRIMO; i++)
//                printf ("%d  ", vprimos[i]);
}

void gerafibo (int vfibo[FIBO])
{
        int i, num1 = 1, num2 = 1, valor;
       
        for (i = 0, valor = 0; valor <= 10000; i++)
        {
                valor = num1 + num2;
                num1 = num2;
                num2 = valor;
                if (valor <= 10000)
                        vfibo[i] = valor;               
        }
//        printf ("Vetor fibo: \n");
//        for (i = 0; i < FIBO; i++)
//                printf ("%d  ", vfibo[i]);
}

void preenchematriz (int mat[MATRIZ][MATRIZ])
{
         int i, j;
         for (i = 0; i < MATRIZ; i++)       
                  for (j = 0; j < MATRIZ; j++)
                          mat[i][j] = rand () % 10001;       
}

int verdiagonalsecund (int mat[MATRIZ][MATRIZ], int vprimos[PRIMO], int vfibo[FIBO], int media[MATRIZ])
{
         int valor, i, j, k, z, primofibo = 0;
        
         printf ("\nValores primos e pertencentes a serie de fibonacci na diagonal secundaria:\n");
         for (i = 0, z = 0, j = MATRIZ - 1; i < MATRIZ; i++, j--)       
         {
                valor = mat[i][j];
                for (k = 0; k < PRIMO; k++)
                        if (valor == vprimos[k])
                        {
                                primofibo = 1;
                                k = PRIMO;
                        }
                for (k = 0; k < FIBO; k++)
                        if (valor == vfibo[k])
                                if (primofibo)
                                {
                                        k = FIBO;
                                        media[z] = valor;
                                        printf ("mat[%d][%d]= %d\n", i, j, valor);
                                        z++;
                                }
                //printf ("\nmat[%d][%d] = %d\tprimofibo: %d", i, j, valor, primofibo);
                primofibo = 0;
         }               
        if (z == 0)
                printf ("nenhum valor\n\n");
        return z;                        
}

void mediaharmonica (int media[MATRIZ], int z)
{
        float divisao, soma, result;
        int i;
       
        printf ("Media hamonica: \n");
        if (z == 0)
                printf ("Nao ha valores primos e pertencentes a serie de fibonacci na diagonal secundaria");
        else
        {               
                for (i = 0, soma = 0; i < z; i++)
                {
                        divisao = (float)1 / media[i];
                        soma += divisao;
                }
                result = z / soma;
                printf ("%f", result);
        }
}
  	4  	z180171.cpp  	[text/plain]  	1,81 KB  	Baixar 
/*
  Name: z180171.cpp
  Author: João Luiz Grave Gross
  Date: 18/05/09 15:37
  Description:
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 13

void preenchegabarito (int *);
void escrevegabarito (int [], int);
int determinaacertos (int [MAX], int [MAX]);

int main ()
{   
    int gabarito[MAX], apostas[MAX], res, seguir, cartao; 
    system("color 70");
    printf("Forneca o gabarito:\n");
    preenchegabarito(gabarito);
        escrevegabarito (gabarito, 13);
       
        do
    {
            printf("\nCartao do apostador: ");
            scanf("%d", &cartao);
            res = determinaacertos(apostas, gabarito);
            printf ("Numero de acertos: %d", res);
                if (res == MAX)
                    printf ("\nGANHADOR, PARABENS");
            else
                    printf ("\nPERDEU!");
             printf("\n\nOutro apostador, digite 1, para parar digite 0: ");
             scanf("%d", &seguir);   
    } while (seguir); 
          
    system("pause");
    return 0;
}

void preenchegabarito (int *gabarito)
{
        int i, valor;
        for (i = 0; i < MAX; i++, gabarito++)
        {
                do
                {
                        printf ("Valor %d: ", i + 1);
                        scanf ("%d", &valor);
                        if (valor < 1 || valor > 3)
                                printf ("Valor invalido\n");
                } while (valor < 1 || valor > 3);
                *gabarito = valor;
        }
}

void escrevegabarito (int vetg[], int num)
 {
   int i;
   printf("\nGabarito lido:\n");
   for (i = 0; i < num; i++)
       printf("%d ", vetg[i]);
   printf("\n\n");   
 }       
 
int determinaacertos (int acertos[MAX], int gabarito[MAX])
{
        int i, j, valor, pontos;
       
        printf ("Faca sua aposta: \n");       
        for (i = 0; i < MAX; i++)
        {
                do
                {
                        printf ("Valor %d: ", i + 1);
                        scanf ("%d", &acertos[i]);
                        if (acertos[i] < 1 || acertos[i] > 3)
                                printf ("Valor invalido\n");
                } while (acertos[i] < 1 || acertos[i] > 3);
        }
       
        for (i = 0, pontos = 0; i < MAX; i++)
                if (gabarito[i] == acertos[i])
                        pontos++;
       
        return pontos;
} 
