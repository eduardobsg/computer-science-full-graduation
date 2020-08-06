/*---------------------------BIBLIOTECAS--------------------------------------*/
#include "fifo.h"

/*-----------------------CONSTANTES------------------------------------------*/
//Erros
#define ERROR_CODE -1

//Limite de processos
#define MAX_PROCESSES 128

//Status do escalonador
#define ESCALONADOR_ATIVO 1
#define ESCALONADOR_INATIVO 0

//Status PID
#define PID_utilizado 1
#define PID_nao_utilizado 0

/*-----------------------------LIB FUNC--------------------------------- */
int libsisop_init();

/*-----------------------GERENCIA DE PROCESSOS--------------------------------*/
//Cria novo Processo
int mproc_create(void* (*start_routine)(void*), void * arg);

//Processo libera processador voluntariamente
void mproc_yield(void);

/*----------------SINCRONIZAÇÃO DE TÉRMINO DE PROCESSO------------------------*/
int mproc_join(int pid);

/*--------------------------FUNÇÕES ESCALONADOR------------------------------*/
//Troca processo em execução, troca de contexto
void scheduler();

//Processo que está bloqueado é liberado para voltar ao esta do de ready
void unblock(int pid); 

/*------------------GLOBAL------------------------*/
PCB running; //Processo que está sendo executado
TipoFila ready; //Fila de elementos prontos para serejm executados
TipoFila blocked; //Fila de elementos bloqueados (join)
TipoFila terminated; //Fila dos processos com PIDs livres (processos que ja terminaram de executar)
ucontext_t scheduler_context; //Contexto do ESCALONADOR

int V_PID[MAX_PROCESSES]; //Vetor para controlar quais PID estão sendo utilizados
							//0-PID não utilizado
							//1-PID utilizado


/*------------------LOCAL FUNC------------------------*/
ucontext_t NovoContexto();
