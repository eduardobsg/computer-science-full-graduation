#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
 

void impar(ucontext_t *impar_context, ucontext_t *main_context2, int *n) {
	int i = 1;
	while(i < *n) {
		printf("impar: %d\n", i);
		i = i + 2;
		swapcontext(impar_context, main_context2);
	}
}

void par(ucontext_t *par_context, ucontext_t *main_context2, int *n) {
	int i = 2;
	while(i < *n) {
		printf("par: %d\n", i);
		i = i + 2;
		swapcontext(par_context, main_context2);
	}
}

 
int main(int argc, char **argv) {

    ucontext_t main_context, main_context2, impar_context, par_context;
    char iterator_stack1[SIGSTKSZ], iterator_stack2[SIGSTKSZ];
    volatile int sequence_finished;
	int n;

	if(argc == 2) {
		n = atoi(argv[argc-1]);
		if(n != 0 && !(n % 2))
			printf("Imprimindo sequencia de 1 a %d.\n", n);
		else
			printf("Insira um número par.");
	}
	else if(argc < 2) {
		printf("Insira um numero par para a sequencia.\n");
	}
	else {
		printf("Argumentos em excesso. Insira apenas um numero para a sequencia.\n");
	}

    getcontext(&impar_context);
    impar_context.uc_link          = &main_context;
    impar_context.uc_stack.ss_sp   = iterator_stack1;
    impar_context.uc_stack.ss_size = sizeof(iterator_stack1);
 
    makecontext(&impar_context, (void (*)(void)) impar,
        3, &impar_context, &main_context2, &n);

    getcontext(&par_context);
    par_context.uc_link          = &main_context;
    par_context.uc_stack.ss_sp   = iterator_stack2;
    par_context.uc_stack.ss_size = sizeof(iterator_stack2);

	makecontext(&par_context, (void (*)(void)) par,
        3, &par_context, &main_context2, &n);
 
    sequence_finished = 0;
    getcontext(&main_context);
    printf("Sequencia terminou! Ultimo elemento: %d\n", n);
 
    if(!sequence_finished) {
        sequence_finished = 1;
		while(1) {
			swapcontext(&main_context2, &impar_context);     
			swapcontext(&main_context2, &par_context);       
		}
    }
 
    return 0;
}

