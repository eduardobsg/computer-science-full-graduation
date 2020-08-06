#include "../include/libsisop.h"

int soma(void *arg){
	return ((int)arg+(int)arg);
}

int yield(void *arg) {
	mproc_yield(); return 0;
}

int main (int argc, char *argv[]) {

	
	int i=5;

	libsisop_init();

	int p1 = mproc_create(soma,&i);
	int q2 = mproc_create(yield,&i);
	
	mproc_join(q2);
	printf("Voltou main! Terminou...\n");
	
	return 0;
}


