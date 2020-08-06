#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"


/* Stack structures */

/* Stack definitions:
	- the pStack (Stack pointer) points to the top of the stack
	- the base of the stack is the first inserted element
	- new inserted elements goes to the top of the stack
*/
typedef int StackInfo;

typedef struct aStack {
	StackInfo memoryFrame;	//the number of the memory page
	struct aStack *down;
} StackNode;


/* Global variables */
StackNode *LRUStack;


/* Stack operations */

/* Creates a new Stack */
StackNode * createStack(void);

/* Insert a new node at the top of the stack */
StackNode * pushStackNode(StackNode *, StackInfo);

/* Removes the top node of the stack */
StackInfo popStackNode(StackNode **);

/* Search a node and removes if from the stack if found */
StackInfo searchAndPopNode(StackNode **, StackInfo);

/* Destroys the stack */
StackNode * destroyStack(StackNode *);

/* Updates the LRU stack */
StackNode * updateLRUStack(StackNode *, int);

/* Prints the stack elements content */
void printStack(StackNode *);

#endif

