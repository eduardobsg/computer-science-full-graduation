#include "../include/libsisop.h"

int func0(int* arg) { 
	printf("\nfunc0(%d)\n", *arg);
    return 0;
} 

int yield(void *arg) {
	printf("\nyield\n");
	mproc_yield();
	return 0;
}

int main(int argc, char *argv[]) { 
    int i=0; 

    libsisop_init(); 

    	int id0 = mproc_create(func0, &i);
	int id1 = mproc_create(func0, &i);
	int id2 = mproc_create(func0, &i);
	int id3 = mproc_create(func0, &i);
	int id4 = mproc_create(yield, &i);
	int id5 = mproc_create(func0, &i);	
    
	mproc_join(id3);
	//Volta após terminar id0,id1,id2,id3,id5
	//id4 é o próximo processo a ser executado, portanto executa id4 e encerra programa
	mproc_join(id4);
	//Testa um join dependendo de um processo que já terminou (deve retornar erro)
	printf("Join return: %d\n", mproc_join(id0));

    return 0;
} 
