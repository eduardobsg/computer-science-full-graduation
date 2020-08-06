/* Title: t02.c - parser
 *
 * Description: tests the substring search, initParser, firstLineCheck
 * and getLine functions
*/

#include "../include/parser.h" 

int main (int argc, char *argv[]) {
	
	//variables
	char string[10] = "lala.txt";
	char substring[5] = ".txt";
	char substring2[5] = "lele";
	char buffer[GETLINE_SIZE];
	int flag, memory_size;

	printf("test 02 starts.\n");

	//tests if the program received at least one argument	
	if( !argv[1] ) {
		fprintf( stderr, "Must have at least 1 arguments.\n" );
		exit(1);		
	}
	
	//searches for a substring in a string
	printf("search a substring in a string.\n");
	flag = searchSubstring(string, substring);
	flag = searchSubstring(string, substring2);
	
	//initializes the parser
	initParser(argv[1]);
	
	//read the first line of the file and return the memory size
	memory_size = firstLineCheck();
	printf("main - memory_size: %d.\n", memory_size);
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);
	printf("buffer: %s", buffer);
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);
	printf("buffer: %s", buffer);
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);
	printf("buffer: %s", buffer);
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);
	printf("buffer: %s", buffer);
	memset(buffer, '\0', GETLINE_SIZE);
	memcpy(buffer, getLine(), GETLINE_SIZE);
	printf("buffer: %s", buffer);

	//closes the configuration file
	fclose(configFile);
	
	printf("test 02 ends.\n");

	return 0;
}
