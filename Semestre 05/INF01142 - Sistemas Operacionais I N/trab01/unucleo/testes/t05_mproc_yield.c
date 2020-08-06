/* Title: t05_mproc_yield.c
 * Description: initializes the libsisop, create some processes with mproc_create
 * and runs the scheduler. Some of this processes yield. They all have the same 
 * priority.
*/

#include "../include/unucleo.h"

void *sum1(int *val) {
	
	int count = 0;
	int yield = 5;

	while(count != *val) {
		if(count == yield) {
			mproc_yield();
			printf("sum1: Returned.\n");
		}
		count++;
	}

	*val = *val + 1;
	printf("sum1 val: %d.\n", *val);
	return NULL;
}

void *sum2(int *val) {
	
	int count = 0;
	int yield = 5;

	while(count != *val) {
		if(count == yield) {
			mproc_yield();
			printf("sum2: Returned.\n");
		}
		count++;
	}

	*val = *val + 1;
	printf("sum2 val: %d.\n", *val);
	return NULL;
}

void *sub1(int *val) {
	*val = *val - 1;
	printf("sub1 val: %d.\n", *val);
	return NULL;	
}

void *sub2(int *val) {
	*val = *val - 1;
	printf("sub2 val: %d.\n", *val);
	return NULL;
}

int main(int argc, char *argv[]) {
	
	int pid[4];
	int n[4] = {10, 10, 10, 10};

	libsisop_init();
	
	pid[0] = mproc_create(PRIO_LOW, sum1, &n[0]); //pid 1
	pid[1] = mproc_create(PRIO_LOW, sub1, &n[1]); //pid 2
	pid[2] = mproc_create(PRIO_LOW, sum2, &n[2]); //pid 3
	pid[3] = mproc_create(PRIO_LOW, sub2, &n[3]); //pid 4

	printf("scheduler started.\n");	
	scheduler();
	printf("scheduler ended.\n");			

	return 0;
}
