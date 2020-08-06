/*
  Disciplina de Algoritmos de Programação (INF01202) - Turma H
  Aluno: João Luiz Grave Gross 	
  Matrícula: 180171
  Atividade: Exercício de Avaliação 4.6.
  Date: 15/03/09 19:56
  Description: Recebido um código alfabético e valores apropriados a cada caso, calcule e imprima: 

  Código       Cálculo
  c            conversão de um valor expresso em polegadas para centímetros 
  j            duração de um jogo
  m            determinação de qual o menor de três valores inteiros fornecidos
 
 conversão: 1 polegada - 2,54 cm  x=pol*2.54
            2          - x

 duração do jogo: serão fornecidas as horas inicial e final do jogo (horas inteiras). O jogo pode 
 durar de 1 a 24 horas, mas pode iniciar em um dia e terminar em outro.
 
 Entradas: código alfabético
*/


#include<stdlib.h>
#include<stdio.h>

int main ()
{
    char code;
    float pol, cent;
    int time_1, time_2, time;
    printf ("Digite o codigo alfabético: ");
    scanf ("%c",&code);
    switch (code)
    {
           case 'c': printf ("Digite o valor para conversao: ");
                     scanf ("%f",&pol);
                     cent = pol*2.54;
                     printf ("%.2f polegadas = %.2f centimetros\n\n",pol,cent);
                     break;
           case 'j': printf ("Inicio do jogo: ");
                     scanf ("%d",&time_1);
                     printf ("Termino do jogo: ");
                     scanf ("%d",&time_2);
                     if (time_1>time_2)
                     {  
                     time = (24-time_1)+time_2;
                     printf ("Duracao do jogo: %dh\n\n",time);   
                     }
                     if (time_1<time_2)
                     {  
                     time = time_2-time_1;
                     printf ("Duracao do jogo: %dh\n\n",time);   
                     }
                     if (time_1==time_2)
                        printf ("Duracao do jogo: 24h\n\n");
                     break;
           case 'm': printf ("Digite tres valores: ");
                     scanf ("%d%d%d",&time_1,&time_2,&time);
                     if (time_1<time_2 && time_1<time)
                        printf ("Menor valor: %d\n\n",time_1);
                     else
                     {
                         if (time_2<time_1 && time_2<time)
                            printf ("Menor valor: %d\n\n",time_2);
                         else
                         {
                             if (time<time_1 && time<time_2)
                                printf ("Menor valor: %d\n\n",time);
                             else
                                printf ("Valores iguais\n\n");    
                         }
                     }
                     break;
           default: printf ("Codigo nao existente. Tente novamente.\n\n");
    }
    system ("pause");
    return 0;
}
