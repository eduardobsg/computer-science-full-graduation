#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
 
/* Error messages */
#define PRIO_OUT_OF_BOUNDS	100;
#define PRIO_MEDIUM 		1;
#define PRIO_LOW			2;
 
 /* Function Prototypes */
int libsisop_init();
int mproc_create(int, void * (*start_routine)(void*), void *);
void mproc_yield();
int mproc_join(int); 
 
 
int main(int argc, char **argv) {
 
    return 0;
}


/* Description: All the inicialization for the 'micro-nucleo'
 * will be done here, in one call.
 *
 * Returns: returns 0 if the execution was sucessful. Returns 
 * anything else if the execution fails.
*/
int libsisop_init() {
	
	return 0;
}


/* Description: creates a new process that will execute alongside with
 * the process that created it. The new process starts the function 
 * 'start_routine' passing the argument 'arg'. The process ends its 
 * execution when it reaches the 'normal' final of the function.  
 *
 * Arguments: 'prio' is the priority of the process created. It can be 1
 * for medium priority or 2 to low priority. Other values must return an
 * error.
 *
 * Returns: returns the process identifier (pid) from the process just
 * created. If mproc_create fails, the return is -1. 
*/
int mproc_create(int prio, void * (*start_routine)(void*), void * arg) {
	
	if( prio < PRIO_LOW || prio > PRIO_MEDIUM )
		return PRIO_OUT_OF_BOUNDS; /* prio out of bounds */

}


/* Description: when called the process who called it will stop its execution 
 * in the processor, entering at the final of the 'ready' FIFO list. Processes
 * with priority higher or equal to the process that has just stopped can run
 * in the processor.
 *
 * Returns: returns 0 if no problem happens, or any other value if it fails.
*/
void mproc_yield(void) {
	
}


/* Description: Suspends the current process execution, until the process with
 * process identifier pid ends. 
 *
 * Returns: 0 if ok, 1 if fails.
*/
int mproc_join(int pid) {
	
}




