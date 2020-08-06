#include "../include/libsisop.h"

int yield(void *arg) {
	printf("\ny1\n");
	mproc_yield();
	
	printf("\ny2\n");
	mproc_yield(); 
	
	printf("\ny3\n");
	mproc_yield();
	
	printf("\ny4\n");
	return 0;
}



int main (int argc, char *argv[]) {
	int i=5;
	libsisop_init();	
	
	int p1 = mproc_create(yield,&i);
	mproc_join(p1);
	printf("Voltou main! Terminou...\n");
	return 0;
}


