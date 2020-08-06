#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main( ) {
    pid_t pid;
    int status; 

    make_dummy();

    if ((pid = fork()) != 0) {
       printf("Processo pai esperando filho PID=%d\n", pid);
       wait(&status);
       printf("Filho terminou com o status: %d\n",WEXITSTATUS(status));
       exit(0);
    }
    else {
       printf("Filho: troca de codigo executavel...\n");
       execl("/bin/ls","ls", "-la", NULL);
       printf("Erro!!\n");
    }
}

