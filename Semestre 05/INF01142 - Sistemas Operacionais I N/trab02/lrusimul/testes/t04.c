/* Title: t04.c - memory
 *
 * Description: tests the memory loop
*/

#include "../include/parser.h" 
#include "../include/memory.h"

int main (int argc, char *argv[]) {
	
	printf("test 04 starts.\n");

	//tests if the program received at least one argument	
	if( !argv[1] ) {
		fprintf( stderr, "Must have at least 1 arguments.\n" );
		exit(1);		
	}

	//initializes the parser
	initParser(argv[1]);
	
	//starts reading the configuration file line by line	
	memoryLoop();

	//closes the configuration file and log file
	fclose(configFile);
	fclose(logFile);	
	
	printf("test 04 ends.\n");

	return 0;
}
