/*
  Disciplina de Algoritmos de Programação (INF01202) - Turma H
  Aluno: João Luiz Grave Gross 	
  Matrícula: 180171
  Atividade: Exercício de Avaliação 2.4
  Data: 08/03/09 16:49
  Descrição: Um hotel com 75 apartamentos deseja fazer uma promoção especial de final de semana, concedendo um desconto 
de 25% na diária. Com isto, espera aumentar sua taxa de ocupação de 50 para 80%. Sendo dado o valor normal da diária, 
calcular e imprimir:
         a) o valor da diária promocional;
         b) o valor total arrecadado com 80% de ocupação e diária promocional;
         c) o valor total arrecadado com 50% de ocupação e diária normal;
         d) a diferença entre estes dois valores.
*/

#include<stdlib.h>
#include<stdio.h>

int main ()
{
    float diaria_normal, diaria_prom, valor_80_prom, valor_50_normal, diferenca;
    printf("Digite o valor da diaria: ");
    scanf("%f",&diaria_normal);
    diaria_prom = diaria_normal*0.75;
    valor_80_prom = diaria_prom*75*0.8;
    valor_50_normal = diaria_normal*38;                         // 75*0,5 = 37,5 -> arredondei para mais -> 38
    diferenca = valor_80_prom - valor_50_normal;
    printf("\nDiaria Promocional: %.2f\n", diaria_prom);
    printf("Valor total arrecadado com 80 porcento de ocupacao e diaria promocional: %.2f", valor_80_prom);    
    printf("Valor total arrecadado com 50 porcento de ocupacao e diaria normal: %.2f\n", valor_50_normal);
    printf("Diferenca: %.2f\n", diferenca);    
    system("pause");
    return 0;
}
