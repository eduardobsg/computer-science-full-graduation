#include "../include/fifo.h"

/* Definition: Creates a new queue FIFO. 
 * Returns: returns a null pointer of type pFIFO (FIFO pointer).
*/
pFIFO * createFIFO(void) {
	return NULL;
}


/* Definition: Given a pointer to a queue, returns the first element 
 * of this queue.
 * Returns: returns an invalid infoFIFO if the queue is empty, if its not,
 * returns the first element.
*/
PCB getFirstElement(pFIFO * p) {
    PCB pcb;
    pcb.pid = -1;
 
    if(p == NULL) 
        return pcb;
     
    return p->pcb;
}


/* Definition: Given a pointer to a queue, returns the first element 
 * of this queue with equal of higher priority to the given one.
 * Returns: returns an invalid infoFIFO if the queue is empty, if its not,
 * returns the first element.
*/
PCB getFirstPriorityElement(pFIFO * p, int priority) {
	pFIFO * paux;
	PCB pcb;
	pcb.pid = -1;

	//printf("\tIs in getFirstPriorityElement().\n");
	if(p == NULL)  
		return pcb;
	
	paux = p;
	while(paux != NULL) {
		//printf("\tpaux->pcb.priority: %d, priority: %d\n", paux->pcb.priority, priority);
		if(paux->pcb.priority <= priority) {
			/* we need to exclude this pcb element from the queue (p) */
			return paux->pcb;			
		}
		else {
			paux = paux->next;
		}
	}

	return pcb;
}


PCB getFirstPidJoinElement(pFIFO * p, int pid_join) {
	pFIFO *paux;
	PCB pcb;
	pcb.pid_join = ERROR;

	//printf("\tIs in getFirstPidJoinElement().\n");
	if(p == NULL)  
		return pcb;
	
	paux = p;
	while(paux != NULL) {
		//printf("paux->pcb.pid_join: %d, pid_join: %d\n", paux->pcb.pid_join, pid_join);
		if(paux->pcb.pid_join == pid_join) {
			return paux->pcb;			
		}
		else {
			paux = paux->next;
		}
	}

	return pcb;
}

/* Definition: Insert a new node at the end of the queue.
 * Returns: the pointer of the queue of type pFIFO.
*/
pFIFO * insertElement(pFIFO * p, PCB pcb) {
	/* Creates a new node */
	pFIFO *newNodeFIFO, *auxFIFO;
	newNodeFIFO = malloc( sizeof(pFIFO) );

	newNodeFIFO->pcb = pcb;
	newNodeFIFO->next = NULL;
	
	if(p == NULL)
		p = newNodeFIFO;	
	else {
		auxFIFO = p;
		while(auxFIFO->next != NULL)
			auxFIFO = auxFIFO->next;
		auxFIFO->next = newNodeFIFO;
	}

	return p;	
}


/* Definition: Removes the first node from de queue and destroys it. 
 * Returns: pointer of type pFIFO.
*/
pFIFO * removeFirstElement(pFIFO *p) {
	pFIFO *pAux;
 
	pAux = p->next;
	free(p);
	return pAux;	
}


/* Definition: Removes the node with given pid
 * Returns: pointer of type pFIFO.
*/
pFIFO * removePIDElement(pFIFO *p, int pid) {
	pFIFO *aux1, *aux2;

	aux1 = p;
	aux2 = p->next;

	if(aux1->pcb.pid == pid) {
		p = aux2;
		free(aux1);	
	}
	else {
		while(aux2 != NULL && aux2->pcb.pid != pid) {
			aux1 = aux2;
			aux2 = aux2->next;
		}   

		if(aux2 != NULL) {
			aux1->next = aux2->next;
			free(aux2);
		}
	}

	return p;
}


/* Definition: Destroys the queue. The exclusion is from the last
 * Returns: pointer of type pFIFO.
*/
pFIFO * destroyFIFO(pFIFO *p) {
	pFIFO *excludeNode;
	
	while(p->next != NULL) {
		excludeNode = p; /* selects the element to be excluded */		
		p = p->next; /* go to the next element of the queue */
		
		free(excludeNode);
	}
	p->next = NULL;	

	return p;
}


/* Definition: Prints the contentes of elements of the queue. 
 * Returns: none.
*/
void printQueue(pFIFO *p) {
	int i, *x;
	pFIFO *paux;

	if(p == NULL) {
		printf("Empty queue.\n");
		return;
	}

	//printf("Printing elements of queue.\n");
	
	i = 0; paux = p;
	while(paux->next != NULL) {
		printf("Element %d:\n", i);
		printf("\tpid: %d\n", paux->pcb.pid);
		printf("\tstate: %d\n", paux->pcb.state);
		printf("\tpriority: %d\n", paux->pcb.priority);
		printf("\tpid_join: %d\n", paux->pcb.pid_join);
		x = paux->pcb.arg; printf("\targ: %d\n", *x);
		paux = paux->next;
		i++;
	}
	printf("Element %d:\n", i);
	printf("\tpid: %d\n", paux->pcb.pid);
	printf("\tstate: %d\n", paux->pcb.state);
	printf("\tpriority: %d\n", paux->pcb.priority);
	printf("\tpid_join: %d\n", paux->pcb.pid_join);
	x = paux->pcb.arg; printf("\targ: %d\n", *x);
}














