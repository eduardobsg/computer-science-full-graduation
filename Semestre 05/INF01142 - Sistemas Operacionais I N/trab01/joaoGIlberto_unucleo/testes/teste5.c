#include "../include/libsisop.h"

int func0(void *arg) { 
    int i; 
    for ( i = 0; i< 10; i++) { 
        printf("func0!\n"); 
        mproc_yield();
    } 
    return 0;
} 

int main(int argc, char *argv[]) { 
    int i, id0; 

    libsisop_init(); 

    id0 = mproc_create(func0, &i); 
    mproc_yield(); 
    printf("Main terminando...\n");
    exit(1);
} 
