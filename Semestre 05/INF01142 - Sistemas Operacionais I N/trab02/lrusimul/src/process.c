#include "../include/process.h"


/* Definition: creates a process, given its pid and the number of pages
 * of the process.
 *
 * Parameters:
 *		@pid: the new process pid	
 *		@pages: the number of pages of the new software
*/
void createProcess(int pid, int pages) {
	Process *newProcess;
	int i;

	//creates a new process
	newProcess = (Process *) malloc( sizeof(Process) );
	newProcess->pid = pid;
	newProcess->numPages = pages;
	newProcess->next = NULL;
	newProcess->pages = (ProcessPage *) malloc( pages * sizeof(ProcessPage) );

	//initialize pages
	for(i = 0; i < pages; i++) {
		newProcess->pages[i].page = i + 1;
		newProcess->pages[i].numAccess = 0;
		newProcess->pages[i].numPageFault = 0;
		newProcess->pages[i].numSwap = 0;
	}

	//insert the process 
	processes = insertProcessInQueue(processes, newProcess);
}


/* Definition: Insert a new process at the end of the queue.
 *
 * Parameters:
 *		@p: pointer to the list of active processes
 *		@newProcess: pointer to the new process
 *
 * Returns: the pointer of the queue of type Process.
*/
Process * insertProcessInQueue(Process *p, Process *newProcess) {
	Process *paux;
	
	if(p == NULL)
		p = newProcess;	
	else {
		paux = p;
		while(paux->next != NULL)
			paux = paux->next;
		paux->next = newProcess;
	}

	return p;	
}


/* Definition: Ends a process by its pid. If the pid is invalid (does 
 * not belong to any process) nothing happens. 
 *
 * Parameters:
 *		@pid: the pid of the processthat will end
 *
 * Global Variables:
 *		@memorySize: the number of frames in the memory 
 *		@memory: pointer to the memory
 *
*/
void endProcess(int pid) {
	Process * process;
	int i;

	//removes a process from the process queue
	process = removeProcessByPIDFromQueue(&processes, pid);
	
	if(process != NULL) {
		//deallocate the process pages from the memory
		for(i = 0; i < memorySize; i++) 
			if(memory[i].pid == pid) {
				memory[i].pid = AVAILABLE;
				memory[i].page = AVAILABLE;
				LRUFIFO = removeElementByFrame(LRUFIFO, i);
			}

		//

		//add process info to the 'log.txt' file
		writeProcessInfoOnLog(process);
	}
	else {
		printf("Error: there is no process with pid %d to be ended.\n", pid);
		exit(1);
	}
}



/* Definition: Removes process given a pid. If the pid does not reffer to
 * any process, then nothing happens.
 *
 * Parameters:
 *		@p: pointer to the pointer of the list of active processes
 *		@pid: pid of the process that will be removed from the active 
 *		process list
 *
 * Returns: pointer of type Process.
*/
Process * removeProcessByPIDFromQueue(Process **p, int pid) {
	Process *aux1, *aux2;
	Process *process;
	int i;

	//tests if the process queue is empty
	if(*p != NULL) {
		aux1 = *p;
		aux2 = (*p)->next;
	}
	else
		return NULL;	

	if(aux1->pid == pid) {
		*p = aux2;
		
		process = (Process *) malloc( sizeof(Process) );
		process->pid = aux1->pid;
		process->numPages = aux1->numPages;
		process->pages = (ProcessPage *) malloc( process->numPages * sizeof(ProcessPage) );
		for(i = 0; i < process->numPages; i++) {
			process->pages[i].page = aux1->pages[i].page;
			process->pages[i].numAccess = aux1->pages[i].numAccess;
			process->pages[i].numPageFault = aux1->pages[i].numPageFault;
			process->pages[i].numSwap = aux1->pages[i].numSwap;
		}
		
		free(aux1);	
		return process;
	}
	else {
		while(aux2 != NULL && aux2->pid != pid) {
			aux1 = aux2;
			aux2 = aux2->next;
		}   

		if(aux2 != NULL) { //so aux2->pid == pid
			aux1->next = aux2->next;
			
			process = (Process *) malloc( sizeof(Process) );
			process->pid = aux2->pid;
			process->numPages = aux2->numPages;
			process->pages = (ProcessPage *) malloc( process->numPages * sizeof(ProcessPage) );
			for(i = 0; i < process->numPages; i++) {
				process->pages[i].page = aux2->pages[i].page;
				process->pages[i].numAccess = aux2->pages[i].numAccess;
				process->pages[i].numPageFault = aux2->pages[i].numPageFault;
				process->pages[i].numSwap = aux2->pages[i].numSwap;
			}

			free(aux2);
			return process;
		}
	}

	return NULL;	
}


/* Definition: Prints the contents of elements of the queue.
 *
 * Parameters:
 *		@p: pointer to the list of active processes  
*/
void printProcessQueue(Process *p) {
	Process *paux;
	int i;

	if(p == NULL) {
		printf("Process queue is empty.\n");
		return;
	}

	printf("\nPrinting elements of process queue.\n");
	
	paux = p;
	while(paux->next != NULL) {
		printf("pid: %d\n", paux->pid);
		printf("numPages: %d\n", paux->numPages);
		for(i = 0; i < paux->numPages; i++) {
			printf("\tpage: %d\n", paux->pages[i].page);
			printf("\t\tnumAccess: %d\n", paux->pages[i].numAccess);
			printf("\t\tnumPageFault: %d\n", paux->pages[i].numPageFault);
			printf("\t\tnumSwap: %d\n", paux->pages[i].numSwap);
		}
		paux = paux->next;
	}

	printf("pid: %d\n", paux->pid);
	printf("numPages: %d\n", paux->numPages);
	for(i = 0; i < paux->numPages; i++) {
		printf("\tpage: %d\n", paux->pages[i].page);
		printf("\t\tnumAccess: %d\n", paux->pages[i].numAccess);
		printf("\t\tnumPageFault: %d\n", paux->pages[i].numPageFault);
		printf("\t\tnumSwap: %d\n", paux->pages[i].numSwap);
	}
}


/* Definition: Makes a short print of the elements of the queue
 *
 * Parameters:
 *		@p: pointer to the list of active processes  
*/
void shortPrintProcessQueue(Process *p) {
	Process *paux;

	if(p == NULL) {
		printf("Process queue is empty.\n");
		return;
	}

	printf("\nPrinting elements of process queue.\n");
	
	paux = p;
	while(paux->next != NULL) {
		printf("pid: %d. numPages: %d\n", paux->pid, paux->numPages);
		paux = paux->next;
	}
	printf("pid: %d. numPages: %d\n", paux->pid, paux->numPages);
}


/* Definition: prints the information of a process
 *
 * Parameters:
 *		@process: pointer to a processes  
*/
void printProcess(Process *process) {
	int i;

	printf("pid: %d\n", process->pid);
	printf("numPages: %d\n", process->numPages);
	for(i = 0; i < process->numPages; i++) {
		printf("\tpage: %d\n", process->pages[i].page);
		printf("\t\nnumAccess: %d\n", process->pages[i].numAccess);
		printf("\t\tnumPageFault: %d\n", process->pages[i].numPageFault);
		printf("\t\tnumSwap: %d\n", process->pages[i].numSwap);
	}
}


/* Definition: given a pid and a page, sees if the pid and page are valid.
 *
 * Parameters: 
 *		@processes: pointer to the list of active processes
 *		@pid: id of a process
 *		@page: page from the pid process
*/
void validatePidAndPage(Process *processes, int pid, int page) {
	Process *paux;
	
	paux = processes;
	while(paux != NULL) {
		if(paux->pid == pid) {
			if(page > paux->numPages) {
				printf("Error: page %d not allowed to pid %d.\n", page, pid);
				exit(1);
			}
			return;
		}
		
		paux = paux->next;
	}
	
	printf("Error: pid %d does not belong to a process.\n", pid );
	exit(1);
}


/* Definition: prints the information of a process
 *
 * Parameters:
 *		@processes: pointer to the list of active processes
 *		@pid: id of a process
 *		@page: page from the pid process
 *		@access: info about the access on the page
 *		@pageFault: info about the page fault of the page
 *		@pageSwap: info about the swap of the page   
 *
 * Returns: pointer of type Process
*/
Process * updateProcessInfo(Process *processes, int pid, int page, int access, int pageFault, int pageSwap) {
	Process *paux;

	paux = processes;
	while(paux != NULL) {
		
		if(paux->pid == pid) {	
			paux->pages[page - 1].numAccess = paux->pages[page - 1].numAccess + access;
			paux->pages[page - 1].numPageFault = paux->pages[page - 1].numPageFault + pageFault;
			paux->pages[page - 1].numSwap = paux->pages[page - 1].numSwap + pageSwap;					
			break;
		}
		
		paux = paux->next;
	}
	
	return processes;
}


/* Definition: Updates a process pageSwap info. Searches for the 
 * frame in the memory, takes the pid and page information of it, 
 * and then updates the pageSwap variable of this page.
 *
 * Parameters:
 *		@p: pointer to the list of active processes
 * 		@frame: index of a frame in the memory
 *
 * Returns: pointer of type Process
*/
Process * updateProcessPageSwap(Process *p, int frame) {
	int pid, page;		
	
	pid = memory[frame].pid;
	page = memory[frame].page;

	p = updateProcessInfo(p, pid, page, 0, 0, 1);

	return p;
}


















