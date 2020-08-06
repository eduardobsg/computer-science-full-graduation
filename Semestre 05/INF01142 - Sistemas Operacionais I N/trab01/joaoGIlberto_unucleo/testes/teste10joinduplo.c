#include "../include/libsisop.h"

int func0(int arg) { 
	printf("Executando p1...\n");
	mproc_yield();
    return -410;
} 

int join_p1(int arg) {
	printf("\nProcesso1\n");
	return mproc_join(arg);
}

int main(int argc, char *argv[]) { 
    int i=0; 

    libsisop_init();
	
	int id1 = mproc_create(func0, &i);
	int id2 = mproc_create(join_p1, id1);
	int id3 = mproc_create(join_p1, id1);
	
	//Antes de voltar desbloqueia main, id2 e id3
	printf("(join return value: %d) Voltou main! Terminou...\n", mproc_join(id1));	
	
    return 0;
} 
