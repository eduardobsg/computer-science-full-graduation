#include "../include/libsisop.h"

int func0(int arg) { 
	printf("\nfunc0(%d)\n", arg);
	mproc_join(arg);
	printf("i'm back!");
    return 0;
} 

int main(int argc, char *argv[]) { 
    int i = 0; 

    libsisop_init(); 

    int id0 = mproc_create(func0, i);

	mproc_yield();

	printf("terminou: %d\n", mproc_join(id0));
    return 0;
} 
