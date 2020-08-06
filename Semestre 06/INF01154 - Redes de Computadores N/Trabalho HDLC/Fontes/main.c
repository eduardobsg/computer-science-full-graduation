/*
João Luiz Grave Gross
INF01154 - Redes de Computadores N
2013/02

Trabalho 01 - Implementação HDLC
*/

/* REALIZAR BYTE STUFFING APÓS O CRC */


#include "hdlc.h"
#include "udp.h"

/* Function prototypes */
void error(char *);

int main(int argc, char *argv[])
{   
	//Server	   
	if(argc < 2)
		runServer();	
	
	//Client
	else {
		if(argc >= 5 && argc <= 6)
			runClient(argv);	
		else {
			error("Wrong number of parameters.");
			exit(0);
		}
	}
		
	return 0;
}

void error(char *msg)
{
	fprintf(stderr, "Error: %s \n", msg);
	exit(0);
}







