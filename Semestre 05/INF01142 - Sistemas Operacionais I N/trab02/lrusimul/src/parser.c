#include "../include/parser.h"

/* Definition: initializes the parser
 *
 * Parameters:
 *		@configFileName: string with the name of the file
 *		configuration file.
 *
 * Global Variables: 
 *		@commands: list of strings with the commands names
 *		@configFile: stream for the configuration file
 *		@LRUFIFO: pointer to the LRU second-chance fifo queue
*/
void initParser(char *configFileName) {	
	//printf("initializing parser.\n");
	
	//initialize global variable commands
	memcpy(commands[0], "MEMSIZE", strlen("MEMSIZE") + 1);
	memcpy(commands[1], "PROCSIZE", strlen("PROCSIZE") + 1);
	memcpy(commands[2], "READ", strlen("READ") + 1);
	memcpy(commands[3], "WRITE", strlen("WRITE") + 1);
	memcpy(commands[4], "ENDPROC", strlen("ENDPROC") + 1);
	
	//opens the file and tests if opened successful	
	configFile = openFile(configFileName, "r");

	//sets the name of the output file
	logFileName = (char *) malloc( 20 * sizeof(char) );
	memcpy(logFileName, "../perf/log.txt", 20);
	
	//opens new output file 
	logFile	= openFile(logFileName, "w");
	
	//create LRUFIFO
	LRUFIFO = createFIFO();
}


/* Definition: searches for a substring in a string.
 *
 * Parameters:
 *		@string: original string
 *		@substring: string to be checked inside 'string'
 *
 * Returns: the return is 0 if the substring has not been found 
 * in string. The return is 1 if the substring is found.	
*/
int searchSubstring(char *string, char *substring) {
	int flag = 0;
	
	//printf("searching for '%s' in '%s'.", substring, string);
	
	for(; *string != '\0';) {
		if(*substring == '\0')
			break;
		for(; *substring != '\0';) {
			if(*string == *substring) {			
				flag = 1;
				string++;
				substring++;
			}
			else {
				flag = 0;
				string++;
				break;
			}
		}
	}
	
	if(flag == 0) { 
		//printf(" substring not found.\n");
		return 0;
	}
	else {
		//printf(" substring has been found.\n");
		return 1;
	}
}


/* Definition: opens a file given a filename.
 *
 * Parameters:
 *		@configFileName: string with the name of the file
 *		configuration file.	
 * 		@option: string with the option for fopen	
 *
 * Returns: returns the opened file.
*/
FILE * openFile(char *configFileName, char *option) {
	FILE * file;	

	//searches for word ".txt" in the string
	if( !searchSubstring(configFileName, ".txt") ) {
		//printf("Error: Configuration file must have .txt format.\n");
		exit(1);
	}
		
	file = fopen(configFileName, option);
	if( !file ) {
		//printf("Error: Failure to open file: %s\n", configFileName);
		exit(1);
    }

	//retorna arquivo aberto.
    return file; 
}


/* Definition: opens the configuration file, reads the first line
 * of the file and if the first line is valid returns the memory size. 
 *
 * Returns: memory size if valid, or an error if the first line 
 * isn't the configuration MEMSIZE.
*/
int firstLineCheck() {
	char buffer[GETLINE_SIZE];	
	ParseElm parseElm;	
	
	//gets the characters of the first line, until the '/n' is reached
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);
	//printf("buffer: %s", buffer);

	//parses a line	and tests if the first line is valid	
	parseElm = parseLine(buffer);
	if( !strcmp(parseElm.command, commands[0]) )
		return parseElm.page;
	else {
		//printf("Error: First command of the configuration file must be MEMSIZE.\n");
		exit(1);
	}
}


/* Definition: gets a line from the configuration file
 *
 * Parameters:
 *		@buffer: holder for the line
 *
 * Returns: the buffer with the line
*/
char * getLine(char *buffer) {
	int i;

	for(i = 0; i < GETLINE_SIZE; i++) {
		buffer[i] = getc(configFile);
		if(buffer[i] == '\n') {
			break;
		}
	}
	
	return buffer;
}


/* Definition: parses a string.
 *
 * Parameters:
 *		@line: string with a line from the configuration file.
 *
 * Global variables: 
 *		@commands: list of string with the command names
 *		@processes: list of the active processes
 * 
 * Returns: a structure of type ParseElm, wihich has the command,
 * pid, and the page of the process if applied to the command.
*/
ParseElm parseLine(char *line) {
	ParseElm parseElm;
	char *token;
	int i = 0;
	int value1 = ERROR;
	int value2 = ERROR;

	//gets the command
	token = strtok(line, " 	'\n'");
	parseElm.command = (char *) malloc( (strlen(token) + 1) * sizeof(char) );
	memcpy(parseElm.command, token, strlen(token) + 1);
	//printf("command: %s. ", parseElm.command);
	
	while(token != NULL) {
		token = strtok(NULL, " 	'\n'");
		
		//gets first value
		if(i == 0 && token != NULL) {
			value1 = atoi(token);
			//printf("value1: %d. ", value1);
		}
		
		//gets second value (if applicable)
		if(i == 1 && token != NULL) {
			value2 = atoi(token);
			//printf("value2: %d.", value2);
		}
		
		i++;
	}
	//printf("\n");
	
	//organizing parseElm information
	if( !strcmp(parseElm.command, commands[0]) ) { //MEMSIZE
		if(value1 != ERROR && value2 == ERROR) {
			parseElm.pid = ERROR;
			parseElm.page = value1; //number of pages in the memory
		}
		else {
			//printf("Error: MEMSIZE with wrong arguments.\n");
			exit(1);
		}
	}
	else if( !strcmp(parseElm.command, commands[1]) ) { //PROCSIZE
		if(value1 != ERROR && value2 != ERROR) {
			parseElm.pid = value1;	//first argument is pid	
			parseElm.page = value2; //second argument is the number of pages
			createProcess(parseElm.pid, parseElm.page);
		}
		else {
			//printf("Error: PROCSIZE with wrong arguments.\n");
			exit(1);
		}
	}
	else if( !strcmp(parseElm.command, commands[2]) ||
			 !strcmp(parseElm.command, commands[3])) { //READ or WRITE
		if(value1 != ERROR && value2 != ERROR) {
			parseElm.pid = value2;	//second argument is pid	
			parseElm.page = value1; //first argument is the page number
			readOrWriteMemoryFrame(parseElm.pid, parseElm.page);
		}
		else {
			//printf("Error: READ/WRITE with wrong arguments.\n");
			exit(1);
		}
	}
	else if( !strcmp(parseElm.command, commands[4]) ) { //ENDPROC
		if(value1 != ERROR && value2 == ERROR) {
			parseElm.pid = value1;	//first argument is pid	
			parseElm.page = ERROR; 
			endProcess(parseElm.pid);
		}
		else {
			//printf("Error: ENDPROC with wrong arguments.\n");
			exit(1);
		}
	}
	else {
		//printf("Error: Invalid command.\n");
		exit(1);
	}
		
	return parseElm;
}


/* Definition: Given a process of type 'Process', writes its pages info in
 * the log.txt file
 *
 * Parameters: 
 *		@process: structure with informations about a process that has ended
 *
 * Global Variables: 
 *		@logFile: stream for the log.txt file 
*/
void writeProcessInfoOnLog(Process *process) {
	char buffer[100];
	char auxString[20];
	int i;
	
	//initialize the string
	memset(auxString, '\0', sizeof(auxString));
	memset(buffer, '\0', sizeof(buffer));
	
	//gets the pid
	sprintf(auxString, "%d", process->pid);

	//first line to be printed
	memcpy(buffer, "PROCESSO ", 10);
	strcat(buffer, auxString);	
	strcat(buffer, "\n");	
	fwrite(buffer, 1, strlen(buffer), logFile);
	
	//second line to be printed
	memset(buffer, '\0', sizeof(buffer));
	memcpy(buffer, "Página	Acessos(R/W)	NroPageFault	NroSubst", sizeof(buffer));
	strcat(buffer, "\n");		
	fwrite(buffer, 1, strlen(buffer), logFile);
	
	//next lines to be printed
	for(i = 0; i < process->numPages; i++) {
		memset(buffer, '\0', sizeof(buffer));
		
		memset(auxString, '\0', sizeof(auxString));
		sprintf(auxString, "%d", process->pages[i].page);
		strcat(buffer, auxString);
		strcat(buffer, "		");
		
		memset(auxString, '\0', sizeof(auxString));
		sprintf(auxString, "%d", process->pages[i].numAccess);
		strcat(buffer, auxString);
		strcat(buffer, "				");
		
		memset(auxString, '\0', sizeof(auxString));
		sprintf(auxString, "%d", process->pages[i].numPageFault);
		strcat(buffer, auxString);
		strcat(buffer, "				");
		
		memset(auxString, '\0', sizeof(auxString));
		sprintf(auxString, "%d", process->pages[i].numSwap);
		strcat(buffer, auxString);
		strcat(buffer, "\n");
		
		fwrite(buffer, 1, strlen(buffer), logFile);
	}
	fputs("\n", logFile);
	
}






















