#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "process.h"
#include "fifo.h"

/* Definition */
#define GETLINE_SIZE 30
#define COMMAND_SIZE 9
#define ERROR -999

/* Parse structure */
typedef struct {
	char *command;
	int pid;
	int page;
} ParseElm;


/* Global variables */
char *logFileName;
FILE *logFile;
FILE *configFile;
char commands[5][COMMAND_SIZE];			   


/* Parser operations */

/* Initializes the parser */
void initParser(char *);

/* Searches for a substring in a string */
int searchSubstring(char *,char *); 

/* Opens a .txt file */
FILE * openFile(char *, char *);

/* Loads the config file and gets the memorysize */
int firstLineCheck();

/* Gets a line from the file */
char * getLine();

/* Given a line from the config file, parses it */
ParseElm parseLine(char *);

/* Given a process, writes its info in the log.txt */
//void writeProcessInfoOnLog(Process *);

#endif


















