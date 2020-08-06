#include<stdio.h>

main()
{
	int a[1024][1024];
	int b[1024][1024];
	int c[1024][1024];
	int i, j, k;

	//printf("Comeca Inicialização."); getchar();
	/*Inicializa as matrizes*/
	for(i=0;i<1024;i++)
		for(j=0;j<1024;j++)
		{
			a[i][j] = 1;
			b[i][j] = 2;
			c[i][j] = 0;
		}

	//printf("Inicialização OK."); getchar();
	/*Efetua a multiplicacao*/
	for(i=0;i<1024;i++)
		for(j=0;j<1024;j++)
			for(k=0;k<1024;k++)
				c[i][j] = a[i][k] * b[k][j];

	/*Calculo pronto, vamos entrar em loop*/
	for(;;) 
		sleep(1);

}
