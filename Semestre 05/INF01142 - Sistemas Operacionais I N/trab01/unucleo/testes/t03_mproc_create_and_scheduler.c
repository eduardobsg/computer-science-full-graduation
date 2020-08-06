/* Title: t03_mproc_create_and_scheduler.c
 * Description: initializes the libsisop, create some processes with mproc_create
 * and runs the scheduler.
*/

#include "../include/unucleo.h"

void *sum(int *val) {
	*val = *val + 1;
	printf("val: %d.\n", *val);
	return NULL;
}

int main(int argc, char *argv[]) {
	
	int i, pid[5];
	int n[5] = {10, 20, 30, 40, 50};

	libsisop_init();

	for(i = 0; i < 5; i++)	
		pid[i] = mproc_create(PRIO_LOW, sum, &n[i]);

	printf("scheduler started.\n");	
	scheduler();
	printf("scheduler ended.\n");			

	return 0;
}
