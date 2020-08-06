/* Title: t02_mproc_create.c
 * Description: initializes the libsisop, create some processes with mproc_create
 * and print the queue with the valid processes, the ones who succeeded on the 
 * creation.
*/

#include "../include/unucleo.h"

void *sum(int *val) {
	printf("val: %d.\n", *val);
	return NULL;
}

int main(int argc, char *argv[]) {
	
	int i, pid[7];
	int n = 20;

	printf("test 02 starts.\n");

	libsisop_init();

	for(i = 0; i < 5; i++)  
	pid[i] = mproc_create(PRIO_LOW, sum, &n);
	
	pid[5] = mproc_create(-1, sum, &n);
	pid[6] = mproc_create(6, sum, &n);
	
	if(pid[5] == ERROR)
		printf("\nfail to create process with prio -1.");
	if(pid[6] == ERROR)
		printf("\nfail to create process with prio 6.\n");
	
	printQueue(readyQueue);
	
	printf("\ntest 02 ends.\n");

	return 0;
}
