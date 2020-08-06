/* Copyright (C) 2006 PRAV - Pesquisa em Redes de Alta Velocidade
 *                    NTVD - Núcleo de TV Digital
 * http://www.ufrgs.br/ntvd
 *
 *  O objetivo deste programa é apresentar a base da estrutura de programação com sockets
 *  através de UDP
 *
 * Cli.c: Esqueleto de cliente UDP. 
 * Argumentos: -h <IP destino> -p <porta>
 *
 * Desenvolvido para sistemas UNIX Like (Linux, FreeBSD, NetBSD...) e Windows
 *		Maiko de Andrade
 *		Valter Roesler
*/

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
	#include <winsock2.h>
#else
        #include <stdlib.h>
        #include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#define SOCKET	int
#endif

int main(int argc, char **argv){
	 struct sockaddr_in peer;
	 SOCKET s;
	 int porta, peerlen, rc, i;
	 char ip[16], buffer[1250];
	 int kbits, quantSends, bytesSobra;
     float sleepTime;
	 
#ifdef _WIN32
	 WSADATA wsaData;
  
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("Erro no startup do socket\n");
		exit(1);
	}
#endif

	 if(argc < 7) {
		  printf("Utilizar:\n");
		  printf("trans -h <numero_ip> -p <porta> -r <taxa>\n");
		  exit(1);
	 }

	 // Pega parametros
	 for(i=1; i<argc; i++) {
		  if(argv[i][0]=='-') {
				switch(argv[i][1]) {
					 case 'h': // Numero IP
						  i++;
						  strcpy(ip, argv[i]);
						  break;
					 
					 case 'p': // porta
						  i++;
						  porta = atoi(argv[i]);
						  if(porta < 1024) {
								printf("Valor da porta invalido\n");
								exit(1);
						  }
						  break;
						  
					 case 'r': //taxa	
                          i++;			 
                          kbits = atoi(argv[i]);
                          
                          if(kbits % 10 != 0) {
                                   bytesSobra = ((kbits % 10)*1000)/8;   
                                   quantSends = kbits/10 + 1;                                
                                   sleepTime = (float) 1000 / quantSends;       
                          }
                          else {
                            quantSends = -1;                          
                            sleepTime = (float) 10000 / kbits;
                            bytesSobra = 0;
                          }
                               
						  printf("sleepTime: %f\n", sleepTime);	                     
						  printf("quantSends: %d\n", quantSends);	                     
						  printf("bytesSobra: %d\n", bytesSobra);
						  break;
						  
					 default:
						  printf("Parametro invalido %d: %s\n",i,argv[i]);
						  exit(1);
				}		  	 
		  } else {
			  printf("Parametro %d: %s invalido\n",i, argv[i]); 
				exit(1);
		  }
	 }
	 
// Cria o socket na familia AF_INET (Internet) e do tipo UDP (SOCK_DGRAM)
	 if((s = socket(AF_INET, SOCK_DGRAM,0)) < 0) {
		  printf("Falha na criacao do socket\n");
		  exit(1);
 	 }
	 
// Cria a estrutura com quem vai conversar 
	 peer.sin_family = AF_INET;
	 peer.sin_port = htons(porta);
	 peer.sin_addr.s_addr = inet_addr(ip); 
	 peerlen = sizeof(peer);
	
 	 while(1) {
        if(quantSends > -1)                      
           if(quantSends > 1) {
              sendto(s, buffer, 1250, 0, (struct sockaddr *)& peer, peerlen);
              quantSends--;
           }
           else {
              sendto(s, buffer, bytesSobra, 0, (struct sockaddr *)& peer, peerlen);
              quantSends = kbits/10 + 1;
           }
        else
            sendto(s, buffer, 1250, 0, (struct sockaddr *)& peer, peerlen);
        
		#ifdef _WIN32
			Sleep(sleepTime);
		#else
			usleep(sleepTime*1000);
		#endif
     }
}
