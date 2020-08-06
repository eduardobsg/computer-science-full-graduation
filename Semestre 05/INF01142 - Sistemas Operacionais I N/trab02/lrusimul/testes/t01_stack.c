/* Title: t01_stack.c - stack
 *
 * Description: create stack, push nodes, print stack, pop nodes, print stack
 * and finally destroy the stack;
 *
 * Global Variable: LRUStack
*/

#include "../include/stack.h" 

int main (int argc, char *argv[]) {
	
	int info[10], i;
	
	printf("test 01 starts.\n");
	
	printf("initializing the info.\n");
	for(i = 0; i < 10; i++)
		info[i] = i*i;

	LRUStack = createStack();

	//insert nodes in the stack
	for(i = 0; i < 10; i++)
		LRUStack = pushStackNode(LRUStack, info[i]);
	printStack(LRUStack);

	//search and pop nodes
	printf("search for 81. return: %d.\n", searchAndPopNode(&LRUStack, 81));
	printf("search for 4. return: %d.\n", searchAndPopNode(&LRUStack, 4));
	printf("search for 60. return: %d.\n", searchAndPopNode(&LRUStack, 60));
	printf("search for 9. return: %d.\n", searchAndPopNode(&LRUStack, 9));
	printf("search for 1. return: %d.\n", searchAndPopNode(&LRUStack, 1));
	printf("search for 50. return: %d.\n", searchAndPopNode(&LRUStack, 50));
	printf("search for 64. return: %d.\n", searchAndPopNode(&LRUStack, 64));
	printStack(LRUStack);

	//pop nodes from stack
	for(i = 0; i < 5; i++)
		info[i] = (int) popStackNode(&LRUStack);
	printStack(LRUStack);
	
	destroyStack(LRUStack);

	printf("test 01 ends.\n");

	return 0;
}
