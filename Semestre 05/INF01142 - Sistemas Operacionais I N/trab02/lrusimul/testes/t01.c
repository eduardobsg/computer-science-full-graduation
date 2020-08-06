/* Title: t01.c - fifo
 *
 * Description: create fifo, insert nodes, print fifo, remove nodes, print fifo
 * and finally destroy the fifo;
 *
 * Global Variable: LRUFIFO
*/

#include "../include/fifo.h" 

int main (int argc, char *argv[]) {
	
	int info[10], i;
	
	printf("test 01 starts.\n");
	
	printf("initializing the info.\n");
	for(i = 0; i < 10; i++)
		info[i] = i*i;

	LRUFIFO = createFIFO();
	printQueue(LRUFIFO);

	//insert nodes in the fifo
	for(i = 0; i < 10; i++)
		LRUFIFO = insertElement(LRUFIFO, info[i]);
	printQueue(LRUFIFO);

	
	//search and pop nodes
	LRUFIFO = removeElementByFrame(LRUFIFO, 81);
	LRUFIFO = removeElementByFrame(LRUFIFO, 60);
	LRUFIFO = removeElementByFrame(LRUFIFO, 4);
	LRUFIFO = removeElementByFrame(LRUFIFO, 60);
	LRUFIFO = removeElementByFrame(LRUFIFO, 9);
	LRUFIFO = removeElementByFrame(LRUFIFO, 1);
	LRUFIFO = removeElementByFrame(LRUFIFO, 50);
	LRUFIFO = removeElementByFrame(LRUFIFO, 64);
	printQueue(LRUFIFO);

	//destroy fifo	
	LRUFIFO = destroyFIFO(LRUFIFO);
	printQueue(LRUFIFO);
	LRUFIFO = destroyFIFO(LRUFIFO);
	printQueue(LRUFIFO);

	printf("test 01 ends.\n");

	return 0;
}
