#include "../include/stack.h"

/* Definition: Creates a new Stack. 
 *
 * Returns: returns a null pointer of type StackNode.
*/
StackNode * createStack(void) {
	printf("stack created.\n");
	return NULL;
}


/* Definition: Insert a new node at the top of the Stack.
 *
 * Parameters: 
 *		@p: pointer to the stack of pages of LRU
 *		@page: page that is going to the top of the LRU stack		
 *
 * Returns: the pointer of the Stack of type StackNode.
*/
StackNode * pushStackNode(StackNode *p, StackInfo page) {

	/* Creates a new node */
	StackNode *newStackNode;
	
	newStackNode = (StackNode*) malloc( sizeof(StackNode) );
	newStackNode->memoryFrame = page;
	newStackNode->down = NULL;

	/* Put new node */	
	newStackNode->down = p;
	
	/* Update the top */
	p = newStackNode;

	printf("node inserted in stack. StackInfo: %d.\n", page);

	return p;	
}


/* Definition: Remove the node from the top of the stack. 
 *
 * Parameters: 
 *		@p: pointer to the pointer to the stack of pages of LRU
 *
 * Returns: the information removed is returned. If the stack is empty 
 * returns an error.
*/
StackInfo popStackNode(StackNode **p) {
	StackNode *paux;
	StackInfo info;
 
 	if(*p == NULL)	
 		return ERROR;
 	else {
 		info = (*p)->memoryFrame;
 		paux = *p;
 		*p = (*p)->down;
 		
		free(paux);
		//printf("node removed from stack. StackInfo: %d.\n", info);
		
		return info;
 	}
}


/* Definition: search for a memory page in the stack. If the page
 * is found, removes it from the stack.
 *
 * Parameters: 
 *		@p: pointer to the pointer to the stack of pages of LRU
 *		@page: page that is going to the top of the LRU stack		
 *
 * Returns: return the memory_page poped up. If the stack is empty 
 * returns an error. If the page is not in the stack returns an error.
*/
StackInfo searchAndPopNode(StackNode **p, StackInfo page) {
	StackNode *paux, *paux2;
	StackInfo info;

	if(*p == NULL)	
 		return ERROR;
 	else {
	 	if((*p)->memoryFrame == page) {
 			info = (*p)->memoryFrame;
	 		paux = *p;
 			*p = (*p)->down;

 			free(paux);
			//printf("node removed from stack. StackInfo: %d.\n", info);
			return info;
 		}
		 	
 		paux = *p;
 		while(paux->down != NULL) {
 			//printf("paux->memoryFrame: %d, page: %d.\n", paux->memoryFrame, page);
 			paux2 = paux;
 			paux = paux->down;
 			
 			if(paux->memoryFrame == page) {
 				info = paux->memoryFrame;
		 		paux2->down = paux->down;
 				
 				free(paux);
				//printf("node removed from stack. StackInfo: %d.\n", info);
 				return info;
 			}
 		}
 		return ERROR;	
 	}	
}


/* Definition: Destroys the Stack.
 *
 * Parameters: 
 *		@p: pointer to the stack of pages of LRU
 *
 * Returns: return NULL for the Stack pointer.
*/ 
StackNode * destroyStack(StackNode *p) {
	StackNode *paux;
	while(p != NULL) {
		paux = p; 
		p = p->down;
		free(paux); 
	}  
    
    printf("stack has been destroyed.\n");
    return NULL;
}


/* Definition: Updates the LRU stack. If the frame is already in the stack 
 * it is removed from it and then pushed on the top of the stack. If the 
 * frame isn't in the stack it is just pushed in the top of the stack.
 *
 * Parameters: 
 *		@stack: pointer to the stack of pages of LRU
 *		@frame: frame to be pushed in the stack
 *
 * Returns: the pointer of the Stack of type StackNode.
*/ 
StackNode * updateLRUStack(StackNode *stack, int frame) {
	StackInfo info;
	
	info = searchAndPopNode(&stack, (StackInfo)frame);
	if(info == ERROR) //frame was not in the stack
		stack = pushStackNode(stack, (StackInfo)frame); 
	else //frame was in the stack
		stack = pushStackNode(stack, info);

	return stack;
}



/* Definition: Prints the contents of the nodes in the stack. 
 *
 * Parameters: 
 *		@p: pointer to the stack of pages of LRU
*/
void printStack(StackNode *p) {
	StackNode *paux;
	
	if(p == NULL) 
		printf("empty stack.\n");
	else {
		printf("\nPrinting the stack.\n");
		for(paux = p; paux != NULL; paux = paux->down) 
			printf("%d\n", paux->memoryFrame);
	}
		
}














