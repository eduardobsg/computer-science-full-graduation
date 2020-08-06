/* Title: t03.c - process
 * Description: tests process criation, process remove and process
 * printing function
*/

#include "../include/process.h"

int main (int argc, char *argv[]) {
	
	printf("test 03 starts.\n");

	printf("%s.\n", argv[1]);
	initParser(argv[1]);

	//inserting processes in the queue
	printProcessQueue(processes);
	createProcess(1, 2);
	createProcess(7, 500);
	createProcess(4, 3);
	printProcessQueue(processes);	

	//removing processes from the queue
	endProcess(4);
	//printProcessQueue(processes);
	endProcess(8);
	endProcess(2);
	//printProcessQueue(processes);
	endProcess(7);
	endProcess(1);
	endProcess(1);
	printProcessQueue(processes);

	createProcess(8, 2);
	createProcess(2, 5);
	endProcess(3);
	endProcess(2);
	printProcessQueue(processes);

	fclose(configFile);
	fclose(logFile);

	printf("test 03 ends.\n");

	return 0;
}
