#include <ucontext.h>

//PID "em branco"
#define PID_EMPTY -1

//Estados do Processo
#define NEW 1
#define READY 2
#define RUNNING 3
#define BLOCKED 4
#define END 5

/*-----------------ESTRUTURA PCB-----------------------*/
typedef struct {
	int PID;
	int state;
	int return_value;
	int PID_join;//Quando um processo está em running e é chamado o join, o PID do processo que o interrompeu é chamado
	ucontext_t context;
	void* (*func) (void*); //funcao de qualquer tipo, com 1 parametro de qualquer tipo
	void* arg;
} PCB;

//Inicializa PCB
PCB NovoPCB(ucontext_t context, void* (*start_routine)(void*), void* arg);
