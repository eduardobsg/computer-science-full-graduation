#include "../include/pcb.h"

/* Definition: create a new PCB structure. 
 * Returns: as the new PCB has been created and initialized, it is returned.
*/
PCB createPCB(ucontext_t context, 
			  void * (*start_routine)(void*), 
			  void * arg) {

	PCB newPCB;
	
	newPCB.pid 		= -1;
	newPCB.state 	= READY;
	newPCB.priority = -1;
	newPCB.pid_join = -1;
	newPCB.func 	= start_routine;
	newPCB.arg		= arg;
	newPCB.context	= context;
	
	makecontext(&newPCB.context, (void (*)(void)) start_routine, 1, arg);
	
	return newPCB;
}
