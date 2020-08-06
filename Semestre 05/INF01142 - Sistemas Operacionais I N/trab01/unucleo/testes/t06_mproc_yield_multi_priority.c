/* Title: t06_mproc_yield_multi_priority.c
 * Description: create some process, some of them yield, and they have
 * different priority.
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
	
	pid[0] = mproc_create(PRIO_MEDIUM, sum1, &n[0]); //pid 1
	pid[1] = mproc_create(PRIO_LOW, sub1, &n[1]); //pid 2
	pid[2] = mproc_create(PRIO_LOW, sum2, &n[2]); //pid 3
	pid[3] = mproc_create(PRIO_MEDIUM, sub2, &n[3]); //pid 4

	printf("scheduler started.\n");	
	scheduler();
	printf("scheduler ended.\n");			

	return 0;
}
