/* Title: t09_create_200_processes.c
 * Description: tries to create more processes than it allowed.
*/

#include "../include/unucleo.h"

void *sub(int *val) {
	*val = *val - 1;
	printf("sub2 val: %d.\n", *val);
	return NULL;
}

int main(int argc, char *argv[]) {
	
	int pid[200], val[200];
	int i, n = 20;

	libsisop_init();
	
	for(i = 0; i < 200; i++) {
		val[i] = n;
		
		if(i%2 == 0)
			pid[i] = mproc_create(PRIO_MEDIUM, sub, &val[i]);
		else
			pid[i] = mproc_create(PRIO_LOW, sub, &val[i]);
			
		if(pid[i] != ERROR)
			printf("Process %d has been created with pid %d\n", i, pid[i]);
		else
			printf("Process %d couldn't be created.\n", i);
	}

	printf("scheduler started.\n");	
	scheduler();
	printf("scheduler ended.\n");			

	return 0;
}
