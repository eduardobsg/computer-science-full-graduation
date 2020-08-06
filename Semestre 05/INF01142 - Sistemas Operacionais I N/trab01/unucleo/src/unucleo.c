#include "../include/unucleo.h" 

/* Description: All the inicialization for the 'micro-nucleo'
 * will be done here, in one call.
 *
 * Returns: returns 0 if the execution was sucessful. Returns 
 * anything else if the execution fails.

 * sudo apt-get install electric-fence
 * sudo apt-get install valgrind
 * valgrind --leak-check=full ./teste
*/
int libsisop_init() {
	int i;	

	printf("libsisop_init starts. ");

	/* Initilizes the availability of the pids for the processes */
	pidList[0] = PID_IN_USE; /* for the schedular */
	for(i = 1; i < MAX_PROCESSES; i++)
		pidList[i] = PID_AVAILABLE;	

	/* Creating queues */
	readyQueue = createFIFO();
	blockedQueue = createFIFO();

	/* Initializes running process state */
	running.state = NOSTATE; /* no state */
	running.priority = -1;

	printf("libsisop_init ends.\n");

	return 0;
}


/* Definition:
 *
 * Returns: 
*/
void scheduler(void) {
	PCB pcbaux;

	while(readyQueue != NULL) {
		
		if(running.state != READY) {		
			if(running.priority >= 0) { 
				pcbaux = getFirstPriorityElement(readyQueue, running.priority);
				if(pcbaux.pid == -1) {
					pcbaux = getFirstElement(readyQueue);
				}
				readyQueue = removePIDElement(readyQueue, pcbaux.pid);
				running = pcbaux;
			}
			else { //prio is below zero, so it is the first time a process is being choose
				/* gets the info of the first element of the ready queue */
				running = getFirstElement(readyQueue);
				/* removes the element from the ready list, because its going 
			   	 * to the running state */
				readyQueue = removeFirstElement(readyQueue);
			}
		}
		running.state = EXECUTING;		
		printf("Process with pid %d is executing.\n", running.pid);		
		
		/* swaps the context between the scheduler and the process -
        * it makes the process start running.
  		* in the swap the variable scheduler_context saves the current 
		* context and runs the context of running process. */
        swapcontext(&scheduler_context, &running.context);
	
		/* the process has ended its execution */		
		if(running.state == EXECUTING) {
			pidList[running.pid] = PID_AVAILABLE;
			printf("Process with pid %d has ended.\n", running.pid);
	
			/* we need to test if the process that has just ended is a
			 * pid_join. So we look at the blockedQueue. If a pcb has the 
			 * running.pid has its pid_join, we pass that pcb to the
			 * end of the readyQueue. */
			 pcbaux.pid_join = 0;
			 while(pcbaux.pid_join != ERROR) {
			 	pcbaux = getFirstPidJoinElement(blockedQueue, running.pid);
				if(pcbaux.pid_join != ERROR) {
					printf("Process with pid %d passed from blocked to ready.\n", pcbaux.pid);
					blockedQueue = removePIDElement(blockedQueue, pcbaux.pid);	
				 	readyQueue = insertElement(readyQueue, pcbaux);
				}
			}
		}
		/* the process has blocked */		
		else if(running.state == BLOCKED) {
			blockedQueue = insertElement(blockedQueue, running);
			printf("Process with pid %d has blocked.\n", running.pid);
		}
		/* the process yielded, so its in the ready state and we have to get 
		 * the first process of priority equal or higher to the priority
 		 * of the current process. */
		else if(running.state == READY) {
			/* gets the info of the first element with priority equal or 
			 * higher to given priority */
		 	printf("Process with pid %d yielded.\n", running.pid);
			pcbaux = getFirstPriorityElement(readyQueue, running.priority);
			printf("Returned pcbaux.\n");
			if(pcbaux.pid != -1) { /* found a pcb */				
				readyQueue = insertElement(readyQueue, running);
				readyQueue = removePIDElement(readyQueue, pcbaux.pid);
				printf("Process with pid %d is ready.\n", running.pid);
				running = pcbaux;
			}				
		}
	}
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
	PCB pcb;
	
	printf("mproc_create starts. ");
	
	/* tests if priority is valid - has to be LOW or MEDIUM */
	if( prio > PRIO_LOW || prio < PRIO_MEDIUM )
		return ERROR; /* prio out of bounds */

	/* creating process_context - links to the scheduler context */
	/* creating new PCB */
	pcb = createPCB(createContext(), start_routine, arg);		
	if(initPCB(&pcb, prio) == ERROR)
		return ERROR;
	
	/* the pcb is created, so we have to insert it in the ready queue*/
	readyQueue = insertElement(readyQueue, pcb);

	return pcb.pid;
}


/* Description: when called the process who called it will stop its execution 
 * in the processor, entering at the final of the 'ready' FIFO list. Processes
 * with priority higher or equal to the process that has just stopped can run
 * in the processor.
 *
 * Returns: returns 0 if no problem happens, or any other value if it fails.
*/
void mproc_yield(void) {
	
	/* if the readyQueue is empty there is no need for yielding */
 	if(readyQueue == NULL)
		return;
 	
	/* the process was executing, and now its going to the ready state */
	running.state = READY;

	/* go back to the scheduler context */
	swapcontext(&running.context, &scheduler_context);
}


/* Description: Suspends the current process execution, until the process with
 * process identifier pid ends. 
 *
 * Returns: 0 if ok, -1 if fails.
*/
int mproc_join(int pid) {
	
	/* tests if the required pid is an active process. If its not, there is 
	 * no reason to block for a process that does not exist anymore */
	if( pidList[pid] == PID_AVAILABLE )
		return ERROR;

	running.pid_join = pid;
	running.state = BLOCKED;

	/* go back to the scheduler context */
	swapcontext(&running.context, &scheduler_context);
}


/* Definition: checks in the pidList the first available pid.
 *
 * Returns: if a pid is found, returns it. If no pid is found, then no other
 * process must be created, because the limit has been reached. In this case,
 * the return is -1.
*/
int getPID(void) {
	
	int i;

	for(i = 0; i < MAX_PROCESSES; i++) {
		if(pidList[i] == PID_AVAILABLE)	{	
			pidList[i] = PID_IN_USE;
			return i;
		}
	}
	
	return ERROR;
}


/* Definition: creates a new context, for a new process. Its important to 
 * notice that in the end of the process execution, the scheduler context 
 * will be set again.
 *
 * Returns: returns the new context, of type ucontext_t.
*/
ucontext_t createContext(void) {
	int pid;

	pid = avaliablePid();
	
	getcontext(&process_context[pid]);
	/* When the process ends its execution, it'll return to the scheduler
	 * context */
    process_context[pid].uc_link          = &scheduler_context;
    process_context[pid].uc_stack.ss_sp   = iterator_stack[pid];
    process_context[pid].uc_stack.ss_size = sizeof(iterator_stack[pid]);

	return process_context[pid];
}


/* Definition: given a pointer to a pcb structure, and a priority,
 * this function initializes the structure giving it a pid and setting its 
 * priority.
 *
 * Returns: the pid if everything is okay or -1 if it fails.
*/
int initPCB(PCB * pcb, int priority) {
	pcb->pid = getPID();
	
	if(pcb->pid == ERROR)
		return ERROR; /* there is no pid available */

	pcb->priority = priority;

	return pcb->pid; /* everything is O.K. */
}


/* Definition: search the first avaliable pid in the pidList
 * and then returns it.
 * Returns: returns the first avaliable pid.
*/
int avaliablePid() {
	int i;

	for(i = 0; i < MAX_PROCESSES; i++) {
		if(pidList[i] == PID_AVAILABLE)	{	
			return i;
		}
	}
}





