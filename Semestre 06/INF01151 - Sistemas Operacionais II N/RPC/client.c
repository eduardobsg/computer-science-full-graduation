#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
	  
///CLIENT   
  
int main(int argc, char *argv[]) {
	printf("This is the client program\n");
 
	int sockfd;
	int len, rc;
	struct sockaddr_in address;
	int result;
	char ch = 'A';
 
	//Create socket for client.
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) { 
		perror("Socket create failed.\n") ; 
		return -1 ; 
	} 
	 
	//Name the socket as agreed with server.
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(7734);
	len = sizeof(address);
 
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		perror("Error has occurred");
		exit(-1);
	}
 
 	int count = 0;
	while(ch < 'E') {
		//Read and write via sockfd
		rc = write(sockfd, &ch, 1);
		printf("write rc = %d\n", rc); 

		/*
		if(rc == -1) {
			sleep(1); 
			printf("RC is -1.\n"); 
			sleep(1); 
			break; 
		}
		*/
		
		sleep(1); 
		
		read(sockfd, &ch, 1);
		count++;
		printf("%d Char from server = %c\n\n", count, ch);
		
		
		//if (ch == 'A') sleep(5) ;  // pause 5 seconds 
	} 
	
	printf("RC: %d, ch: %c.\n", rc, ch);
	
	close(sockfd);
	return 0;
}
