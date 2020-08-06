/* Title: t04_mproc_create_and_scheduler.c
 * Description: initializes the libsisop, create some processes with mproc_create
 * and runs the scheduler.
*/

#include "../include/unucleo.h"

void *sum(int *val) {
	*val = *val + 1;
	printf("sum val: %d.\n", *val);
	return NULL;
}

void *sub(int *val) {
	*val = *val - 1;
	printf("sub val: %d.\n", *val);
	return NULL;
}

void *mult(int *val) {
	*val = (int) *val * 2;
	printf("mult val: %d.\n", *val);
	return NULL;	
}

void *div2(int *val) {
	*val = (int) *val / 2;
	printf("div2 val: %d.\n", *val);
	return NULL;	
}

int main(int argc, char *argv[]) {
	
	int pid[4];
	int n[4] = {10, 10, 10, 10};

	libsisop_init();
	
	pid[0] = mproc_create(PRIO_LOW, sum, &n[0]);
	pid[1] = mproc_create(PRIO_LOW, sub, &n[1]);
	pid[2] = mproc_create(PRIO_LOW, mult, &n[2]);
	pid[3] = mproc_create(PRIO_LOW, div2, &n[3]);

	printf("scheduler started.\n");	
	scheduler();
	printf("scheduler ended.\n");			

	return 0;
}
