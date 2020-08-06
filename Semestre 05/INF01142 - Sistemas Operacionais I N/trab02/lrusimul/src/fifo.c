#include "../include/fifo.h"

/* Definition: Creates a new queue FIFO. 
 *
 * Returns: a null pointer of type FIFONode (FIFO pointer).
*/
FIFONode * createFIFO() {
	return NULL;
}


/* Definition: Insert a new node at the end of the queue.
 * 
 * Parameters: 
 * 		@p: pointer to the second-chance frame queue
 *		@frame: the frame that we want insert in the queue
 *
 * Returns: the pointer of the queue of type FIFONode.
*/
FIFONode * insertElement(FIFONode *p, int frame) {
	FIFONode *newNodeFIFO, *auxFIFO;

	//initialize new node
	newNodeFIFO = malloc( sizeof(FIFONode) );
	newNodeFIFO->memoryFrame = frame;
	newNodeFIFO->refbit = 1;
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


/* Definition: Removes the node with the given 'frame' value
 * 
 * Parameters: 
 * 		@p: pointer to the second-chance frame queue
 *		@frame: the frame that we want to remove
 *
 * Returns: pointer of type FIFONode.
*/
FIFONode * removeElementByFrame(FIFONode *p, int frame) {
	FIFONode *aux1, *aux2;

	aux1 = p;
	aux2 = p->next;

	if(aux1->memoryFrame == frame) {
		p = aux2;
		free(aux1);	
	}
	else {
		while(aux2 != NULL && aux2->memoryFrame != frame) {
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


/* Definition: Destroys the queue. Deallocates all the elements
 * of the queue.
 * 
 * Parameters: 
 * 		@p: pointer to the second-chance frame queue.
 *
 * Returns: pointer of type FIFONode.
*/
FIFONode * destroyFIFO(FIFONode *p) {
	FIFONode *excludeNode;
	
	while(p != NULL) {
		excludeNode = p; //selects the element to be excluded
		p = p->next; //go to the next element of the queue
		
		printf("freeing element with frame %d.\n", excludeNode->memoryFrame);
		free(excludeNode);
	}
	p = NULL;	

	return p;
}


/* Definition: given a frame from the memory, puts the reference bit
 * of this frame in 1.
 *
 * Parameters: 
 * 		@p: pointer to the second-chance frame queue.
 *
 * Returns: pointer of type FIFONode.
*/
FIFONode * frameFirstTime(FIFONode *p, int frame) {
	FIFONode *aux;

	aux = p;
	while(aux != NULL) {
		if(aux->memoryFrame == frame) {
			aux->refbit = 1;
			break;
		}
		aux = aux->next; 
	}

	return p;
}


/* Definition: Updates the LRU fifo using the second chance algorithm
 * on the fifo, and choose a frame to be the victim.
 *
 * Parameters: 
 * 		@p: pointer to the second-chance frame queue.
 *
 * Returns: the frame victim
*/ 
int chooseVictim(FIFONode **fifo) {
	FIFONode *aux1;

	aux1 = *fifo;
	while(aux1->refbit == 1) {
		if(aux1->refbit == 1)
			aux1->refbit = 0;

		aux1 = aux1->next;
		if(aux1 == NULL)
			aux1 = *fifo;
	}	

	return aux1->memoryFrame;
}


/* Definition: prints the contents of the queue elements. 
 * 
 * Parameters: 
 * 		@p: pointer to the second-chance frame queue.
*/
void printQueue(FIFONode *p) {
	int i;
	FIFONode *paux;

	if(p == NULL) {
		printf("Empty queue.\n");
		return;
	}

	printf("\nPrinting elements of the LRU queue.\n");
	
	i = 0;
	paux = p;
	while(paux->next != NULL) {
		printf("Element %d:\n", i);
		printf("\tframe: %d\n", paux->memoryFrame);
		printf("\trefbit: %d\n", paux->refbit);
		paux = paux->next; i++;
	}
	printf("Element %d:\n", i);
	printf("\tframe: %d\n", paux->memoryFrame);
	printf("\trefbit: %d\n", paux->refbit);
}














