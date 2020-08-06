#include <stdio.h>
#include "../include/libsisop.h"

int thread1(int arg) {
	printf("1: Thread started with argument %d.\n", arg);
	int i;
	for (i=0; i<5; i++) {
		printf("1\n");
		mproc_yield();
	}
	printf("1: Finished with mproc_exit(23).\n");
	return 23;
}

int thread2(int arg) {
	printf("2: Thread started with argument %d.\n", arg);
	int i, status;
	for (i=0; i<10; i++) {
		if (i==3) {
			printf("2: Waiting for %d to finish.\n", arg);
			status = mproc_join(arg);
			printf("2: Gotten status %d.\n", status);
		}
		else {	
			printf("2\n");
		}
		mproc_yield();
	}
	printf("2: Finished by returning.\n");
	return 42;
}

int thread3(int arg) {
	printf("3: Thread started with argument %d.\n", arg);
	int i, status;
	for (i=0; i<15; i++) {
		if (i==2) {
			printf("3: Waiting for %d to finish.\n", arg);
			status = mproc_join(arg);
			printf("3: Gotten status %d.\n", status);
		}
		else {
			printf("3\n");
		}
		mproc_yield();
	}
	printf("3: Finished with mproc_exit(69).\n");
	return -588;
}

int main() {
	int t1, t2, t3, s1, s2, s3;

	libsisop_init();
	t1 = mproc_create(thread1, 42);
	t2 = mproc_create(thread2, t1);
	t3 = mproc_create(thread3, t2);
	
	printf("main\n");
	s1 = mproc_join(t1);
	printf("main______2\n");
	s2 = mproc_join(t2);
	printf("main!!!!\n");
	s3 = mproc_join(t3);

	printf("Final values: %d %d %d\n", s1, s2, s3);

	return 0;
}

