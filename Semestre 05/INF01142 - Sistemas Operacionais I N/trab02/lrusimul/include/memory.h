#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

#define AVAILABLE 9999
#define NOT_FOUND -9999

/* Memory structure */
struct MemoryNode {
	int pid;	//process owner of the page		
	int page;	//number of the page of a process
};

typedef struct MemoryNode Memory;


/* Global variables */
int memorySize;
Memory *memory;


/* Memory operations */

/* Creates the memory */
Memory * createMemory();

/* Reads the configuration file line by line */
void memoryLoop();

/* Reads/write a page from a process */
void readOrWriteMemoryFrame(int, int);

/* Searchs the memory for the given page */
int lookForPageInMemory(Memory *, int, int);

/* Sees if there is an available frame in the memory */
int checkAvailableFrame(Memory *);

/* Given a frame and a page, write the page in the frame */
Memory * writePageInMemoryFrame(Memory *, int, int, int);

#endif

