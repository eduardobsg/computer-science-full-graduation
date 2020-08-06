#include <stdlib.h>
#include <stdio.h>

#include "pcb.h" /* defines the PCB struture */

/* Error messages */
#define ERROR -999

/* FIFO definitions:
 * Last element: the last but one element points to it. The last element
 * has a pointer pointing nowhere (null).
 * First element: has a pointer to the second element.
*/

/**** Structures *****/

/* Node strutcture of the FIFO queue - simple linked list */
typedef struct aFIFO {
	PCB pcb;
	struct aFIFO *next;
} nodeFIFO;

/* Structure to a node of type nFIFO */
typedef nodeFIFO pFIFO;


/***** Operations over the FIFO queue *****/

/* Creates a new queue FIFO */
pFIFO * createFIFO(void);

/* Returns the first element of the list */
PCB getFirstElement(pFIFO *);

/* Returns the first element of the list with equal of higher priority
 * to the given priority. */
PCB getFirstPriorityElement(pFIFO *, int);

/* Returns the first element of the list with equal pid_join
 * to the given pid. */
PCB getFirstPidJoinElement(pFIFO *, int);

/* Insert a new node at the end of the queue */
pFIFO * insertElement(pFIFO *, PCB);

/* Removes the first node from de list and destroys it */
pFIFO * removeFirstElement(pFIFO *);

/* Removes the node with given pid */
pFIFO * removePIDElement(pFIFO *, int);

/* Destroys the queue */
pFIFO * destroyFIFO(pFIFO *);

/* Printfs the queue elements content */
void printQueue(pFIFO *);



