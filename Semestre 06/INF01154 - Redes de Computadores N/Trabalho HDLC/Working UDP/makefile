CC = gcc
CFLAGS = -g -Wall 

all: client server

client: 
	$(CC) udp-transmitter-client.c -o client $(CFLAGS)

server:
	$(CC) udp-receiver-server.c -o server $(CFLAGS)

