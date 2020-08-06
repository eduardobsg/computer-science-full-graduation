#include <ucontext.h>

/***** Definitions *****/
#define NOSTATE		-1 	/* the process isn't in any state */
#define READY		1
#define EXECUTING	2
#define BLOCKED		3

/***** PCB structure *****/
typedef struct {
	int pid;
	int state;
	int priority;
	int pid_join;
	void * (* func) (void *);
	void * arg;
	ucontext_t context;
} PCB;

/***** Functions *****/

/* Creates a new PCB struture and returns it. */
PCB createPCB(ucontext_t, void * (*start_routine)(void*), void *);

 
