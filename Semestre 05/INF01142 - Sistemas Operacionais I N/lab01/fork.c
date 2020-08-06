#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main( ) {
    pid_t pid;
    char *message;
    int n, code;

    printf("Iniciando a execucao do fork\n");
    pid = fork ( );
    printf("Cada processo, faz uma impressao destas!! ######\n");

    switch (pid) {
    case -1:
	perror("Falha na execucao do fork! \n");
	exit(1);
    case 0:
	message = "Este eh o processo filho";
	n = 4;
        code = 37;
	break;
    default:
	message = "Este eh o processo pai";
	n = 3;
	break;
    }

    for(; n > 0; n--) {
       puts(message);
       sleep(1);
    }
/* Apos executar uma vez, descomente as linhas de codigo abaixo,
 * compile e reexecute o programa. */

/* --------inicio de comentario-------
    if (pid != 0) {
       pid_t child_pid;
       int   status;

       child_pid = wait(&status); 
       printf("Pai esperou o filho com PID = %d\n", child_pid);
       printf("O codigo de termino do filho eh %d\n", WEXITSTATUS(status));
       exit(0);
    }
    else 
       exit(code);
-----------Final de comentario --------*/

}

