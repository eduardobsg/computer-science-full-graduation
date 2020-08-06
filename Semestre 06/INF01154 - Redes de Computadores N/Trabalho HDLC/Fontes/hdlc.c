#include "hdlc.h"


/*
Description: 
	Creates a HDLC element.
Parameters:
	@ int datasize : the size of the data segment. For 'S' and 'U'
	messages the datasize must be 0. For 'I' messages it must be
	above zero. 
Return:
	A HDLC element. Its not fully initialized, still needs data
	segment and FCS.
*/
HDLC * newHDLC(int datasize) {
	HDLC * myHDLC;
	
	myHDLC = malloc(sizeof(HDLC));
	myHDLC->flag1 = FLAG;
	myHDLC->address = BROADCAST;
	myHDLC->datasize = datasize;	
	
	if(datasize == 0)
		myHDLC->data = NULL;
	else if(datasize > 0)
		myHDLC->data = (char *) malloc(datasize * sizeof(char));
	

	myHDLC->FCS = malloc(2 * sizeof(char));
	myHDLC->flag2 = FLAG;	
		
	return myHDLC;
}


/*
Description: 
	Sets the control byte to a HDLC transmission
Parameters:
	@ char type : the type of the message, must be 'U', 'S' or 'I'.
	@ char * controlCode : 
		For type equal 'U', the controlCode	must be "DISC", "UA" or "SIM".
		For type equal 'S', the controlCode can be anything, will not be used.
		For type equal 'I', the controlCode can be anything, will not be used.
	@ int frameNumber : 
		Ranging from 0 to 6 for 'S' and 'I' messages.
		Not used for 'U' messages. Can be anything.		
Return:
	Returns the control for the HDLC structure.
*/
char setControlByte(char type, char * controlCode, int frameNumber) {
	char control;
	int randRet;
	
	/* Initialize random seed */
	srand(time(NULL));	
		
	if(type == 'U')
		if(!strcmp(controlCode, "DISC"))
			control = DISC;
		else if(!strcmp(controlCode, "UA"))
			control = UA;
		else if(!strcmp(controlCode, "SIM"))
			control = SIM;
		else
			error("Wrong control code.");

	else {	
		/* The frames will range from 0 to 6 at maximum */	
		if(frameNumber > 6 || frameNumber < 0)
			error("Frame Number is out of bounds.");
	
		if(type == 'S') {
			randRet = rand() % 100;
			if(randRet < 10)
				control = RNR + frameNumber;
			else
				control = RR + frameNumber;
		}
		
		else if(type == 'I') {
			//implementar
			//bitwise << 4
		}
		
		else 
			error("Wrong message type. Must be 'U', 'S' or 'I'.");
	}
	
	return control;
}


/*
Description: 
	Prints the HDLC element.
Parameters:
	@ char * msg : a message ti be printed.
	@ HDLC * myHDLC : the HDLC pointer to the element.
Return:
	None.
*/
void printHDLC(char * msg, HDLC * myHDLC) {
	int i;	

	printf("%s\n", msg);

	printf("1. FLAG1:\t%d\n", (int)myHDLC->flag1);
	printf("2. Address:\t%d\n", (int)myHDLC->address);	
	printf("3. Control:\t%d\n", (int)myHDLC->control);		
	printf("4. Datasize:\t%d\n", myHDLC->datasize);			
	printf("5. Data:\n");			
	for(i = 0; i < myHDLC->datasize; i++)
		printf("\t%d\t%d\n", i, (int)myHDLC->data);
	printf("6.1. FCS[0]:\t%d\n", (int)myHDLC->FCS[0]);	
	printf("6.2. FCS[1]:\t%d\n", (int)myHDLC->FCS[1]);	
	printf("7. FLAG2:\t%d\n\n", (int)myHDLC->flag2);
}


/*
Description: 
	Prints the HDLC element. Simple print
Parameters:
	@ HDLC * myHDLC : the HDLC pointer to the element.
Return:
	None.
*/
void simplePrintHDLC(char * msg, HDLC * myHDLC) {
	int i;	

	printf("%s", msg);

	printf("%d | ", (int)myHDLC->flag1);
	printf("%d | ", (int)myHDLC->address);	
	printf("%d | ", (int)myHDLC->control);		
	printf("%d | ", myHDLC->datasize);			
	printf("%d | ", (int)myHDLC->FCS[0]);	
	printf("%d | ", (int)myHDLC->FCS[1]);	
	printf("%d\n\n", (int)myHDLC->flag2);
}













