#include "../include/libsisop.h"
#include "../include/debug.h"

//Algoritmo de escalonamento
void scheduler() {
	while (ready != NULL) {
		
		//Remove processo que está rodando atualmente
		//Remove processo que estava no início de ready 
		//Insere como processo que está rodando
		running = *RetiraFila(&ready);
		debug("Running PID: %d\n", running.PID);
		running.state = RUNNING;
		running.context.uc_link = &scheduler_context;
		
		swapcontext(&scheduler_context, &running.context);

		if(running.state == RUNNING) { 
			//Processo terminou
			running.state = END;
			V_PID[running.PID] = PID_nao_utilizado;
			unblock(running.PID);
			InsereFila(&terminated, running);
			debug("finished(pid=%d)\n", running.PID);
		}
	}
}


/**
* 	Libera todos os processos que foram bloqueados (foram retirados do running por um 
* join).Função é chamada quando o processo "pid" termina de executar.
* Ou seja, é chamada sempre que um processo termina de executar.
*
**/
void unblock(int pid) {
	int find = 0;
	TipoFila filaAux = NovaFila();
	
	while(blocked != NULL) {
		find = (blocked->info.PID_join == pid);
		/** Se nao encontrar passa o proximo pcb pra fila auxiliar */
		if(find) {
			debug("Processo desbloqueado: %d\n", blocked->info.PID );
			blocked->info.state = READY;
			blocked->info.PID_join = PID_EMPTY;
			blocked->info.return_value = running.return_value;
			InsereFila(&ready, *RetiraFila(&blocked));
		} else {
			InsereFila(&filaAux, *RetiraFila(&blocked));
		}
	}
	blocked = filaAux;

}

int mproc_create(void* (*start_routine)(void*), void * arg) {
	debug("Create Process\n");

	PCB newProcess = NovoPCB( NovoContexto(), (void*)start_routine, (void*)arg );
	newProcess.PID = nextPID();
	
	if(newProcess.PID != ERROR_CODE) {
		InsereFila(&ready, newProcess);
	}
	return newProcess.PID;
}

int mproc_join(int pid) {
	debug("Join\n");
	int chamou_escalonador = ESCALONADOR_INATIVO;

	//Nao faz sentido usar join se nao ha processo na fila de espera
	//Ou se o PID indicado não é um processo
	if ((ready == NULL) || (V_PID[pid]==0)) return ERROR_CODE;
	
	running.PID_join = pid;
	running.state = BLOCKED;
	getcontext(&running.context);
	if(!chamou_escalonador) {
		chamou_escalonador = ESCALONADOR_ATIVO;
		//Insere processo em execucao no fim da fila de bloqueados
		InsereFila(&blocked, running);
		swapcontext(&running.context, &scheduler_context);
	}
	
	return running.return_value;
}

//Insere processo que está rodando atualmente no fim da fila de prontos
void mproc_yield(void) {
	debug("yield\n");
	int chamou_escalonador = ESCALONADOR_INATIVO;
	
	//Nao faz sentido usar yield se nao ha processo na fila de espera
 	if (ready == NULL) return;
 	
	running.state = READY;
	getcontext(&running.context);
	if(!chamou_escalonador) {
		chamou_escalonador = ESCALONADOR_ATIVO;
 		InsereFila(&ready, running);
		swapcontext(&running.context, &scheduler_context);
 	}

}

ucontext_t NovoContexto() {
	ucontext_t new_context;
	getcontext(&new_context);
	int stack_size = SIGSTKSZ * sizeof(char);
	//Apenas cria uma pilha para o novo contexto (alocando espaco em memoria)
	char* context_stack_pointer = (char*) malloc( stack_size );
	//sempre retorna para o contexto do escalonador (scheduler_context) depois de terminar de executar
	new_context.uc_link = &scheduler_context;
	new_context.uc_stack.ss_sp = context_stack_pointer;
	new_context.uc_stack.ss_size = stack_size;
	return new_context;
}

int libsisop_init() {
	SET_DEBUG_MODE_ON();
	SET_DEBUG_MODE_OFF();
	//Estabelece que nenhum processo está rodando
	running = NovoPCB( NovoContexto(), NULL, NULL );
	ready = NovaFila();
	blocked = NovaFila();
	terminated = NovaFila();
	/** Inicializa contexto do escalonador */
	scheduler_context = NovoContexto();
	V_PID[0] = PID_utilizado; 
	makecontext(&scheduler_context, (void(*)(void))scheduler, 0, 0); 
	return 0;
}

/**
* Retorna o proximo ID de processo
* Retorna um ERROR_CODE(-1) caso tenha atingido o limite de processos
*/
int nextPID() {
	static int pid = 1;
	int aux_pid = 0;
	if(pid < MAX_PROCESSES){
		V_PID[pid]=PID_utilizado;
		return pid++;
	}
	else 
		if(terminated != NULL) {
			aux_pid = RetiraFila(&terminated)->PID;
			if(V_PID[aux_pid]==PID_nao_utilizado) V_PID[aux_pid]=PID_utilizado;
			else return ERROR_CODE;
			return aux_pid;
		}
		else return ERROR_CODE;
}
