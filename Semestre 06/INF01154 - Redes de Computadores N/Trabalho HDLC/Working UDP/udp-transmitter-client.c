/* UDP client in the internet domain */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define IP 64000
#define MAX_SIZE 256

typedef struct hdcl {
	
	
} HDCL;

//Function prototype
void error(char *);

int main(int argc, char *argv[])
{
	int sock, length, n;
	struct sockaddr_in server, from;
	struct hostent *hp;
	char buffer[MAX_SIZE];
   
	/* Initialize random seed */
	srand(time(NULL));
	
	//printf("%d", rand() % 7 + 1);
   
	if(argc < 2) {
		printf("IP address must be informed.\n");
		exit(1);
	}
   
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
		error("socket");

	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);

	if(hp == 0)
		error("Unknown host");

	bcopy(	(char *)hp->h_addr, 
			(char *)&server.sin_addr,
         	hp->h_length);     
	server.sin_port = htons(IP);
	length = sizeof(struct sockaddr_in);
	
	while(1) {
		printf("Please enter the message: ");
		bzero(buffer, MAX_SIZE);
		fgets(buffer, MAX_SIZE - 1, stdin);
		
		//Newline '\n' correction
		n = strlen(buffer) - 1;
		if(buffer[n] == '\n')
			buffer[n] = '\0';
		
	   	n = sendto(	sock, buffer, strlen(buffer), 
	   				0, (struct sockaddr *)&server, length);

		if(n < 0)
			error("Sendto");
	   
		bzero(buffer, MAX_SIZE);
		n = recvfrom(sock, buffer, MAX_SIZE, 0, (struct sockaddr *)&from, (socklen_t *)&length);
	   	
	   	if(n < 0)
	   		error("recvfrom");

		fprintf(stderr, "Got an ack from server: ");
		fprintf(stderr, "%s \n", buffer);
	}	
		
	return 0;
}

void error(char *msg)
{
	perror(msg);
	exit(0);
}







