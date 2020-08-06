/*
  Name: João Luiz Grave Gross
  Copyright: 
  Author: 
  Date: 08/03/09 14:49
  Description: Multiplica dois termos quaisquer
*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main ()
{
    float x1, x2, x3;
    printf("Digite dois valores para multiplica:\n");
    scanf("%f%f", &x1, &x2);
    x3 = x1 * x2;
    printf("%.2f * %.2f = %.2f\n", x1, x2, x3);
    system("pause");
    return 0;
}
