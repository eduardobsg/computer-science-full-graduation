#include "../include/libsisop.h"

int yield(void *arg) {
	printf("\nyield\n");
	mproc_yield();
	return 0;
}

void ok() { printf("ok!!!\n"); }

int main (int argc, char *argv[]) {
	libsisop_init();	
	
	int k=0;
	int p[127];
	
	for(k=0; k<126; k++) {
		p[k] = mproc_create(yield,&k);
	}
	
	int p127 = mproc_create(ok,NULL);

	//todos os 126 yields param no meio da execucao
	mproc_yield();

	//nessa linha somente o processo p127 ja terminou, logo liberou o pid 127 (127 deve ser impresso abaixo)	
	printf("PID after 128 processes: %d\n", mproc_create(ok, NULL));
	
	//termina de executar os 126 yields que estavam pela metade e depois executa o processo criado na linha acima
	mproc_yield();
	
	//Libera o id do primeiro processo que havia terminado (pid 1 deve ser impresso na linha de baixo)
	printf("PID after 129 processes: %d\n", mproc_create(ok, NULL));
	mproc_yield();
	return 0;
}
