#include "../include/memory.h"
#include "../include/process.h"
#include "../include/fifo.h"
#include "../include/parser.h"

int main (int argc, char *argv[])  {

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
	
	return 0;
}

	
