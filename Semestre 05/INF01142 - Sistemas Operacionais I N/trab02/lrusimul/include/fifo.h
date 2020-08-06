#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdio.h>

/* LRU Second-chance fifo queue definitions:
	- the frames in the fifo queue are the frames allocated in 
	the memory.
	- the frames in the fifo can be chosen as victims by the lru 
	second-chance algorithm.
	- the maximum elements of the fifo is the quantity of frames
	the memory have.
	- when a frame is chosen as victim, the new frame comes in the 
	fifo queue position of the victim one.
*/

/* FIFO structures */
typedef struct aFIFO {
	int memoryFrame;	//index of a memory frame
	int refbit;
	struct aFIFO *next;
} FIFONode;


/* Global variables */
FIFONode *LRUFIFO;


/* FIFO operations */

/* Creates a new queue FIFO */
FIFONode * createFIFO(void);

/* Insert a new node at the end of the queue */
FIFONode * insertElement(FIFONode *, int);

/* Removes the node with the given 'frame' value */
FIFONode * removeElementByFrame(FIFONode *, int);

/* Destroys the queue */
FIFONode * destroyFIFO(FIFONode *);

/* Sets a frame as first time  */
FIFONode * frameFirstTime(FIFONode *, int);

/* Chooses a frame to be the victim */
int chooseVictim(FIFONode **);

/* Prints the queue elements content */
void printQueue(FIFONode *);

#endif

