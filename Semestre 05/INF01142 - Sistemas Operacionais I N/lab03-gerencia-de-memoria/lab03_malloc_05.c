#include<stdlib.h>
#include<stdio.h>
#include <errno.h>

#define BUFF_SIZE 314159265

main()
{
	int *ptr;

	while(1)
	{
		ptr = malloc(BUFF_SIZE);
		
		if(NULL == ptr)
		{
			fprintf(stderr, "Houve um erro fatal!\n");
			fprintf(stderr, "Codigo de Erro: %d\n", errno);
			exit(errno);
		}
		else
		{
			*ptr = 42;
			sleep(1);
		}
	}
}

