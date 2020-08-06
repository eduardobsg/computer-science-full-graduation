#include "../include/memory.h"


/* Definition: creates the memory and initializes it
 *
 * Global Variables:
 *		@memorySize: the number of frames in the memory 
 *		@memory: pointer to the memory
 *
 * Returns: a pointer to the memory
*/
Memory * createMemory() {
	int i;

	//read the first line of the file and return the memory size
	memorySize = firstLineCheck();
	
	//allocates memory for 'memory'
	memory = (Memory *) malloc( memorySize * sizeof(Memory) );
	
	//initialize memory
	for(i = 0; i < memorySize; i++) {
		memory[i].pid = AVAILABLE;
		memory[i].page = AVAILABLE;
	}
	
	return memory;
}


/* Definition: reads the configuration file line by line
 *
 * Global Variables: 
 *		@memory: pointer to the memory
 *		@configFile: stream for the configuration file
*/
void memoryLoop() {
	char buffer[GETLINE_SIZE];
	ParseElm parseElm;
	
	//creates the memory
	memory = createMemory();

	//iterates over the configuration file
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);	
	while( !feof(configFile) ) {
		//printf("\nbuffer: %s", buffer);	
		parseElm = parseLine(buffer);		

		//printProcessQueue(processes);
		//printQueue(LRUFIFO);
		//getchar();

		memset(buffer, '\0', GETLINE_SIZE);
		memcpy(buffer, getLine(), GETLINE_SIZE);	
	}
}


/* Definition: reads a page from a process. If the page isn't in the memory
 * it is brought in the memory.
 *
 * Parameters: 
 * 		@pid: process id
 *		@page: process page
 *
 * Global Variables: 
 *		@memory: pointer to the memory
 *		@processes: pointer to the list of active processes
 *		@LRUStack: stack for the LRU algorithm
*/
void readOrWriteMemoryFrame(int pid, int page) {
	int access = 0;
	int pageFault = 0;
	int pageSwap = 0;
	int frame;

	//first check if the pid and page are valid
	validatePidAndPage(processes, pid, page);

	//check if the page is in the memory
	frame = lookForPageInMemory(memory, pid, page);
	
	access++;
	if(frame != NOT_FOUND) {
		//printf("1-page found in memory.\n");
		processes = updateProcessInfo(processes, pid, page, 
									  access, pageFault, pageSwap);		
		return;
	}
	else
		//printf("1-page not found in memory.\n");
	
	//the page isn't in the memory. First we see if there is any 
	//available frame is the memory, so we can bring the page to it.
	pageFault++;
	frame = checkAvailableFrame(memory);
	if(frame != NOT_FOUND) {
		//printf("2-available frame found.\n");
		memory = writePageInMemoryFrame(memory, frame, pid, page);
		processes = updateProcessInfo(processes, pid, page, access, pageFault, pageSwap);
		LRUFIFO = insertElement(LRUFIFO, frame);
		return;
	}
	else
		//printf("2-memory is full.\n");
	
	//the memory is full. Its time to use LRU algorithm
	pageSwap++;
	frame = chooseVictim(&LRUFIFO);
	//printf("3-victim frame: %d.\n", frame);

	//updates the pageSwap variable from the page on the given frame
	processes = updateProcessPageSwap(processes, frame);

	//writes the new page in the frame and updates the information of 
	//the page that has just been written in
	memory = writePageInMemoryFrame(memory, frame, pid, page);
	processes = updateProcessInfo(processes, pid, page, access, pageFault, 0);
	LRUFIFO = frameFirstTime(LRUFIFO, frame);
}


/* Definition:
 *
 * Parameters:
 *
 * Global Variables:
 *
*/
void writeMemoryFrame(int pid, int page) {

}


/* Definition: Searchs the memory for the given page
 *
 * Parameters: 
 *		@memory: pointer to the memory
 * 		@pid: process id
 *		@page: process page 
 *
 * Global Variables:
 *		@memorySize: the size of the memory (in frames)	
 *
 * Returns: an integer with the index of the frame with the page
 * or NOT_FOUND if the page ins't in the memory.
*/
int lookForPageInMemory(Memory *memory, int pid, int page) {
	int i;
	
	for(i = 0; i < memorySize; i++) {
		if(memory[i].pid == pid && memory[i].page == page)
			return i;
	}
	
	return NOT_FOUND;
}


/* Definition: Sees if there is an available frame in the memory
 *
 * Parameters: 
 *		@memory: pointer to the memory
 *
 * Global Variables:
 *		@memorySize: the size of the memory (in frames)	
 *
 * Returns: an integer with the index of the first available frame in
 * the memory or NOT_FOUND if the memory is full.
*/
int checkAvailableFrame(Memory *memory) {
	int i;	

	for(i = 0; i < memorySize; i++) {
		if(memory[i].pid == AVAILABLE)
			return i; //an available frame has been found
	}

	//memory is full
	return NOT_FOUND;
}
 

/* Definition: Bring a process page to the memory in the specified frame
 *
 * Parameters: 
 *		@memory: pointer to the memory
 *		@frame: a frame in the memory (memory index)
 * 		@pid: process id
 *		@page: process page 
 *
 * Returns: a pointer to the memory 
*/
Memory * writePageInMemoryFrame(Memory *memory, int frame, int pid, int page) {

	memory[frame].pid = pid;
	memory[frame].page = page;
	
	return memory;
}



