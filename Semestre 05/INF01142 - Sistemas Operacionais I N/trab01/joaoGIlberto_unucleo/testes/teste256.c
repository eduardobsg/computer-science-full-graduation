#include "../include/libsisop.h"

int pid(int arg) {
	printf("Processo: %d", arg);
	return 0;
}



int main (int argc, char *argv[]) {
	int i=5;
	libsisop_init();	
	
	int k=0;
	
	int p[127];
	
	//Cria 127 processos
	for(k=1; k<128; k++) {
		p[k] = mproc_create(pid,k);
	}
	
	//Executa os 127 processos
	mproc_yield();
	
	//Cria novamente 127 processos
	for(k=1; k<128; k++) {
		p[k] = mproc_create(pid,k);
	}
	
	//Executa novamente os 127 processos
	mproc_yield();
	
	return 0;
}
