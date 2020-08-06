#include "../include/libsisop.h"

int mult(void *arg){
	printf("\nmultiplicacao\n");
	return (int)arg*(int)arg;
}

int divis(void *arg){
	printf("\ndivisao\n");
	return 1;
}

int soma(void *arg){
	printf("\nsoma\n");
	return ((int)arg+(int)arg);
}

int sub(void *arg){
	printf("\nsubtracao\n");
	return ((int)arg-(int)arg);
}
 
int main (int argc, char *argv[]){

	int pid1, pid2, pid3, pid4;
	int i=5;
	
	libsisop_init();	

	pid1 = mproc_create(divis,&i);
	pid2 = mproc_create(mult,&i);
	pid3 = mproc_create(soma,&i);
	pid4 = mproc_create(sub,&i);

	mproc_yield();
	printf("Voltou main! Terminou...\n");
 
	return 0;
}
