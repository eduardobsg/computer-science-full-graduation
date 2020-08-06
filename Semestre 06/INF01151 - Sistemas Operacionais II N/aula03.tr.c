#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 500

void espera(int n) {
	int i,j;
	for(i = 0; i < n; ++i)
		for(j = 0; j < 100000; ++j)
			j = j;
}


void *filha(void * param) {
	int i;
	int n = (int) param;
	for(i = 0; i < MAX; ++i) {
		fprintf(stderr,"%d: Filha%d \n", i, n);
		espera(20);
	}
}

	
int main () {
	pthread_t t1;
	pthread_t t2;
	pthread_attr_t at;
	
	pthread_attr_init(&at);
	//pthread_attr_setscope(&at,PTHREAD_SCOPE_SYSTEM);
	pthread_create(&t1, &at, filha, (void*)1);
	pthread_create(&t2, &at, filha, (void*)2);
	printf("Pai que tem duas filhas\n");
	getchar();

	return 0;
}


