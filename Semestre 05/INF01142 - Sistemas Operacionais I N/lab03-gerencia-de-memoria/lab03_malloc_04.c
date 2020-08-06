#include<stdlib.h>

#define BUFF_SIZE 314159265

main()
{
	int *ptr;

	while(1)
	{
		ptr = malloc(BUFF_SIZE);
		*ptr = 42;
		sleep(1);
	}
}

