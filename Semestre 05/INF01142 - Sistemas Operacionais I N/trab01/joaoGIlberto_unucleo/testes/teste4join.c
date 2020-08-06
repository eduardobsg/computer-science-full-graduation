#include "../include/libsisop.h"

int id(int x) { 
	mproc_yield(); 
	printf("...continua executando p1...x=%d\n", x); 
	printf("\nFim p1\n");
	return x; 
	
}

int join2(int pid) { 
	printf("pid join2: %d\n", pid);
	mproc_join(pid); //Como a main esta bloqueada volta a executar p1
	printf("\nFim p2\n");
	return 0;
}
 
int main (int argc, char *argv[]) {
	int i=5;
	libsisop_init();
	
	int p1 = mproc_create(id,i);
	int p2 = mproc_create(join2,p1);
	
	mproc_join(p1);
	//Main só volta depois que p1 termina de executar
	printf("Volta main!Fim execucao...\n");
	
	return 0;
}


