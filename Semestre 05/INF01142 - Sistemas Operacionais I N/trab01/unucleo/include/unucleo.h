#include "fifo.h"

/***** Definitions *****/

/* Priority */
#define PRIO_HIGH		0
#define PRIO_MEDIUM 	1
#define PRIO_LOW		2

/* Processes */
#define MAX_PROCESSES	128
#define PID_AVAILABLE	0
#define PID_IN_USE		1


/***** Global Variables *****/
int pidList[MAX_PROCESSES];

/* Queues */
pFIFO * readyQueue;	/* queue of processes ready to run */
pFIFO * blockedQueue; /* queue of processes blocked by the primitive join */

/* Contexts */ 
ucontext_t scheduler_context;
ucontext_t process_context[MAX_PROCESSES];

/* Stacks */
char iterator_stack[MAX_PROCESSES][SIGSTKSZ];

/* Running process */
PCB running;


/***** Function Prototypes *****/

/* Initializes the micro core */
int libsisop_init(void);

/* Controls the execution of the processes */
void scheduler(void);

/* Creates a new process */
int mproc_create(int, void * (*start_routine)(void *), void *);

/* The process who calls this function will go from the executing state
 * to the ready state. Freeing the virtual processor. */
void mproc_yield(void);

/* Suspends the current process execution, until the process with
 * process identifier pid ends. */
int mproc_join(int); 

/* Check the first available pid in order: 0 to 127. */
int availablePID(void);

/* Creates the context of a process */
ucontext_t createContext(void);

/* Initializes the PCB structure */
int initPCB(PCB *, int);

/* Return the first avaliable PID */
int avaliablePid(void);


