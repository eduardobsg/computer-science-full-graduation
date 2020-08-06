#include "../include/pcb.h"

extern PCB running;

void keepReturnValue(void) {
	running.return_value = running.func(running.arg);
	return;
}

PCB NewPCB(ucontext_t context, void* (*start_routine)(void*), void* arg ) {
	PCB newPCB;
	newPCB.PID = 0;
	newPCB.state = NEW;
	newPCB.return_value = 0;
	newPCB.PID_join = PID_EMPTY;
	//inicializa com contexto sem ligação, pois o processo novo ainda nao foi executado
	newPCB.context = context;
	newPCB.func = start_routine;
	newPCB.arg = arg;
	makecontext(&(newPCB.context), keepReturnValue, 0);

	return newPCB;
}
