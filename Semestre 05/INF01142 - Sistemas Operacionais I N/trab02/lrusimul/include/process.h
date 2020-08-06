#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

/* Process structure */
typedef struct aProcessPage {
	int page;		  //number of the page of the process
	int numAccess;	  //number of accesses to that page
	int numPageFault; //number of page faults for the page
	int numSwap;  	  //number of page swaps
} ProcessPage;

typedef struct aProcess {
	int pid;				//holds the process pid
	int numPages;			//holds the number of pages
	ProcessPage *pages;		//array of pages
	struct aProcess *next;	//points to the next process
} Process;


/* Global variables */
Process *processes;


/* Process operations */

/* Creates a new process */
void createProcess(int, int);

/* Insert a new process at the end of the queue. */
Process * insertProcessInQueue(Process *, Process *);

/* Ends a process */
void endProcess(int);

/* Removes process given a pid */
Process * removeProcessByPIDFromQueue(Process **, int);

/* Prints the contents of elements of the queue */
void printProcessQueue(Process *);

/* Makes a short print of the elements of the queue */
void shortPrintProcessQueue(Process *);

/* Prints the information of a process */
void printProcess(Process *);

/* Given a pid and a page, sees if the pid and page are valid */
void validatePidAndPage(Process *, int, int);

/* Updates the information of a process */
Process * updateProcessInfo(Process *, int, int, int, int, int);

/* Updates a process pageSwap info */
Process * updateProcessPageSwap(Process *, int);

#endif








