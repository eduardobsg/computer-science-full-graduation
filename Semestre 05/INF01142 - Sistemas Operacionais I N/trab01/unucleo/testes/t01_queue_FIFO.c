/* Title: t01_queue_FIFO.c
 * Description: just creates some PCBs, insert them on a queue and print it.
*/

#include "../include/unucleo.h" 

void *sum(int *val) {
	printf("val: %d.\n", *val);
	return NULL;
}

int main (int argc, char *argv[]) {
	
	pFIFO *p;
	PCB pcb[10];
	int i, n[10];
	
	printf("test 01 starts.\n");
	
	printf("initializing the PCBs.\n");
	for(i = 0; i < 10; i++) {
		n[i] = 10;
		pcb[i] = createPCB(createContext(), sum, &n[i]);
	}		
	
	printf("creating FIFO.\n");
	p = createFIFO();

	for(i = 0; i < 10; i++) {
		printf("inserting element %d.\n", i);
		p = insertElement(p, pcb[i]);
	}

	printQueue(p);

	printf("test 01 ends.\n");

	return 0;
}
