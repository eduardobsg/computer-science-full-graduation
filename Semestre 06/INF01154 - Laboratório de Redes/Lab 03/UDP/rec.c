/* Copyright (C) 2006 PRAV - Pesquisa em Redes de Alta Velocidade
 *                    NTVD - Núcleo de TV Digital
 * http://www.ufrgs.br/ntvd
 *
 *  O objetivo deste programa é apresentar a base da estrutura de programação com sockets
 *  através de UDP
 *
 * Serv.c: Esqueleto de servidor UDP.
 * Argumentos: -p <porta>
 *
 * Desenvolvido para sistemas UNIX Like (Linux, FreeBSD, NetBSD...) e Windows
 *		Maiko de Andrade
 *		Valter Roesler
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <winsock2.h>
#else
	#define SOCKET int
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif

int main(int argc, char **argv){
	 struct  sockaddr_in peer;
	 SOCKET  s;
	 int porta, peerlen, rc, i;
	 char buffer[1250];

#ifdef _WIN32
	 WSADATA wsaData;


	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("Erro no startup do socket\n");
		exit(1);
	}
#endif

	 if(argc < 2) {
		  printf("Utilizar:\n");
		  printf("rec -p <porta>\n");
		  exit(1);
	 }

	 for(i=1; i < argc; i++) {
		  if(argv[i][0]=='-'){
				switch(argv[i][1]){
					 case 'p':
						  i++;
						  porta = atoi(argv[i]);
						  if(porta < 1024) {
								printf("Porta invalida\n");
								exit(1);
						  }
						  break;
					 default:
						  printf("Parametro %d: %s invalido\n",i,argv[i]);
						  exit(1);
				}
		  }else{
				printf("Parametro %d: %s invalido\n",i,argv[i]);
				exit(1);
		  }
	 }

// Cria o socket na familia AF_INET (Internet) e do tipo UDP (SOCK_DGRAM)
	 if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		  printf("Falha na criacao do socket\n");
		  exit(1);
 	 }

// Define domínio, IP e porta a receber dados
	 memset((void *) &peer,0,sizeof(struct sockaddr_in));
	 peer.sin_family = AF_INET;
	 peer.sin_addr.s_addr = htonl(INADDR_ANY); // Recebe de qualquer IP
	 peer.sin_port = htons(porta); // Recebe na porta especificada na linha de comando
	 peerlen = sizeof(peer);

// Associa socket com estrutura peer
	 if(bind(s,(struct sockaddr *) &peer, peerlen)) {
		  printf("Erro no bind\n");
		  exit(1);
	 }

	 printf("Socket inicializado. Aguardando mensagens...\n\n");

// Recebe pacotes do cliente e responde com string "ACK"
	 while (1)
	 {
		 // Quando recebe um pacote, automaticamente atualiza o IP da estrutura peer
#ifdef _WIN32
		 rc = recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&peer, &peerlen);
#else
		 rc = recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&peer, (socklen_t *)&peerlen);
#endif
		 //printf("Recebido %s\n", buffer);

		 strcpy(buffer,"ACK");
		 sendto(s,buffer,sizeof(buffer),0,(struct sockaddr *)&peer, peerlen);
		 //printf("Enviado ACK\n\n");
	 }

}
