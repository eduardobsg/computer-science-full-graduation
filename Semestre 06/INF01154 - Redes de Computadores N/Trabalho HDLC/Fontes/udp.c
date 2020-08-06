#include "udp.h"

/*
Description: 
	As soon as the application is launched for a client this function is called.
Parameters:
	@ char *argv : vector with inputs from the terminal
Return:
	None.
*/
void runClient(char *argv[]) {
	int sock, length;
	struct sockaddr_in server;
	struct hostent *hp;
	char filename[MAX_FILENAME];
	FILE * pFile;
	HDLC * myHDLC;

	/* Connect to server */
	hp = NULL;
	checkArguments(argv, &hp, filename);	
	if(hp == 0)
		error("Unknown host");
	
	/* Creates a socket stream with the server */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
		error("socket");

	server.sin_family = AF_INET;
	bcopy(	(char *)hp->h_addr, 
			(char *)&server.sin_addr,
	     	hp->h_length);     
	server.sin_port = htons(IP);
	length = sizeof(struct sockaddr_in);
	
	/* Creates a new HDLC element for the connection message.
	NON_I_MSG indicates that there is no data segment. */
	myHDLC = newHDLC(NON_I_MSG);


	while(1) {
		/* Sets the control byte for the HDLC */
		myHDLC->control = setControlByte('U', "SIM", -1);

		/* Sends the control message */
		sendHDLCMessage(myHDLC, sock, server, length);

		/* Receives U - UA message from the client */
		myHDLC = newHDLC(NON_I_MSG);
		myHDLC = receiveHDLCMessage(sock, &server, &length);

		if(myHDLC->control == UA)
			break;
	}

	
	/* Start sending file */	
	pFile = openFile(filename, "r"); /* Opens the file */
	while(1) {
		break;
	}


	/* Close connection */
	while(1) {
		/* Sets the control byte for the HDLC */
		myHDLC->control = setControlByte('U', "DISC", -1);

		/* Sends the control message */
		sendHDLCMessage(myHDLC, sock, server, length);

		/* Receives U - UA message from the client */
		myHDLC = receiveHDLCMessage(sock, &server, &length);

		if(myHDLC->control == UA) {
			break;
		}
	}	

	/* Closes the file */
	fclose(pFile);
}


/*
Description: 
	As soon as the application is launched for a server this function is called.
Parameters:
	None.
Return:
	None.
*/
void runServer() {
	int sock, length;
	struct sockaddr_in server, client;
	FILE * pFile;
	HDLC * myHDLC;

	/* Creates a socket stream with the client */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
		error("Opening socket");
		
	printf("Server has started.\n");
			
	length = sizeof(struct sockaddr_in);
	
	bzero(&server, length);
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(IP);
   
	if(bind(sock, (struct sockaddr *)&server, length) < 0) 
		error("binding");
	
	while(1) {
		/* Receives U - SIM message from the client */
		myHDLC = receiveHDLCMessage(sock, &client, &length);

		if(myHDLC->control == SIM) {
			/* Prepare UA command */			
			myHDLC->control = setControlByte('U', "UA", -1);
			
			/* Send ACK to client */
			sendHDLCMessage(myHDLC, sock, client, length);
			break;
		}
	}


	/* Start receiving data */
	pFile = openFile("output", "w"); /* Opens the file */

	while(1) {				
		
		/* Receives U - DISC message from the client */
		myHDLC = receiveHDLCMessage(sock, &client, &length);

		if(myHDLC->control == DISC) {
			/* Prepare UA command */			
			myHDLC->control = setControlByte('U', "UA", -1);
			
			/* Send ACK to client */
			sendHDLCMessage(myHDLC, sock, client, length);
			break;
		}
	}

	/* Closes the file */
	fclose(pFile);
}


/*
Description:
	Check the arguments sent in the application call. If all the arguments
	are ok, then we can move foward.
Parameters:	
	@ char *argv[] : vector with inputs from the terminal. Will be tested
	@ struct hostent **hp : structure to store informations of the host
	@ char *filename : the input file filename
Return:
	None.
*/
void checkArguments(char *argv[], struct hostent **hp, char *filename) {
	
	if( !strcmp(argv[1], "-l") ) {
		//do log
			
		if( !strcmp(argv[2], "-h") ) {
			if(argv[3] != NULL) {
				*hp = gethostbyname(argv[3]);
					
				if( !strcmp(argv[4], "-f") ) {
					if(argv[5] != NULL) 
						strcpy(filename, argv[5]);
					else
						error("Fifth argument must be the filename");	
				}
			}
			else
				error("Third argument must be the IP.");					
		}
		else
			error("Second argument must be -h.");
	}
	else {
		if( !strcmp(argv[1], "-h") ) {
			if(argv[2] != NULL) {
				*hp = gethostbyname(argv[2]);
						
				if( !strcmp(argv[3], "-f") ) {
					if(argv[4] != NULL) 
						strcpy(filename, argv[4]);
					else
						error("Forth argument must be the filename.");
				}
			}
			else
				error("Second argument must be the IP.\n");					
		}
		else
			error("First argument must be -l or -h.\n");
	}	
}


/*
Description: 
	Open a file given its filename.
Parameters:
	@ char *filename : the name of the file
Return:
	A pointer to the file stream.
*/
FILE * openFile(char * filename, char * option) {
	FILE * pFile;	

	pFile = fopen(filename, option);
	if(pFile == NULL)
		error("File could not be opened.");

	return pFile;
}


/*
Description: 
	Sends a HDLC message.
Parameters:
	@ HDLC * myHDLC : the message with its headers.
	@ int sock : the socket stream number.
	@ struct sockaddr_in destiny : structure containing the internet address of 
	the destiny (client or server).
Return:
	None.
*/
void sendHDLCMessage(HDLC * myHDLC, int sock, struct sockaddr_in destiny, int length) {		
	int i;

	/* Send flag1 */
	sendto(sock, &myHDLC->flag1, sizeof(char), 0, (struct sockaddr *)&destiny, length);

	/* Send address */
	sendto(sock, &myHDLC->address, sizeof(char), 0, (struct sockaddr *)&destiny, length);

	/* Send control byte */
	sendto(sock, &myHDLC->control, sizeof(char), 0, (struct sockaddr *)&destiny, length);

	/* Send datasize */
	sendto(sock, &myHDLC->datasize, sizeof(int), 0, (struct sockaddr *)&destiny, length);

	/* Send data */
	for(i = 0; i < myHDLC->datasize; i++)
		sendto(sock, &myHDLC->data[i], sizeof(char), 0, (struct sockaddr *)&destiny, length);

	myHDLC->FCS = (char *)calcFCS(myHDLC->address, myHDLC->control, 
		myHDLC->datasize, myHDLC->data);

	/* Send FCS */
	sendto(sock, &myHDLC->FCS[0], sizeof(char), 0, (struct sockaddr *)&destiny, length);
	sendto(sock, &myHDLC->FCS[1], sizeof(char), 0, (struct sockaddr *)&destiny, length);

	/* Send flag2 */
	sendto(sock, &myHDLC->flag2, sizeof(char), 0, (struct sockaddr *)&destiny, length);

	//printHDLC("Sent:", myHDLC);
	simplePrintHDLC("Sent: ", myHDLC);
}


/*
Description: 
	Receives a HDLC message.
Parameters:
	@ HDLC * myHDLC : the message with its headers.
	@ int sock : the socket stream number.
	@ struct sockaddr_in server : structure cotaining the internet address of the server.
Return:
	None.
*/
HDLC * receiveHDLCMessage(int sock, struct sockaddr_in * source, int * length) {
	int i;
	HDLC * myHDLC;

	/* Allocates space for the HDLC element */
	myHDLC = malloc(sizeof(HDLC));
	
	/* Receive flag1 */
	recvfrom(sock, &myHDLC->flag1, sizeof(char), 0, 
		(struct sockaddr *)source, (socklen_t *)length);

	/* Receive address */
	recvfrom(sock, &myHDLC->address, sizeof(char), 0, 
		(struct sockaddr *)source, (socklen_t *)length);

	/* Receive control byte */
	recvfrom(sock, &myHDLC->control, sizeof(char), 0,
		(struct sockaddr *)source, (socklen_t *)length);

	/* Receive datasize */
	recvfrom(sock, &myHDLC->datasize, sizeof(int), 0,
		(struct sockaddr *)source, (socklen_t *)length);

	/* Receive data */
	myHDLC->data = malloc(myHDLC->datasize * sizeof(char));

	for(i = 0; i < myHDLC->datasize; i++) 
		recvfrom(sock, &myHDLC->data[i], sizeof(int), 0,
			(struct sockaddr *)source, (socklen_t *)length);

	/* Receive FCS */
	myHDLC->FCS = malloc(2 * sizeof(char));

	recvfrom(sock, &myHDLC->FCS[0], sizeof(char), 0,
		(struct sockaddr *)source, (socklen_t *)length);
	recvfrom(sock, &myHDLC->FCS[1], sizeof(char), 0,
		(struct sockaddr *)source, (socklen_t *)length);

	i = checkFCS(myHDLC->address, myHDLC->control, myHDLC->datasize, 
		myHDLC->data, myHDLC->FCS);

	/* Receive flag2 */
	recvfrom(sock, &myHDLC->flag2, sizeof(char), 0, 
		(struct sockaddr *)source, (socklen_t *)length);

	//printHDLC("Received:", myHDLC);
	simplePrintHDLC("Received: ", myHDLC);

	return myHDLC;
}



