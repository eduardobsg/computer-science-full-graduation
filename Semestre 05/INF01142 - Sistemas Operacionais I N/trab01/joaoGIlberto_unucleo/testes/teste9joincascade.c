#include "../include/libsisop.h"

int printok() {
	printf("ok!\n");
	return 0;
}

int func0(int arg) { 
	int p2 = mproc_create(printok, NULL);
	printf("\np1\n");
	mproc_join(p2);
	printf("p1 is back!\n");
    return 99;
} 

int main(int argc, char *argv[]) { 
    int i = 0; 

    libsisop_init(); 

    int p1 = mproc_create(func0, i);
	
    printf("terminou: %d\n", mproc_join(p1));
    return 0;
} 
