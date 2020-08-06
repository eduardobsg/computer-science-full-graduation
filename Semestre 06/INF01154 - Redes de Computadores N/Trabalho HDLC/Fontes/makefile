CC = gcc
CFLAGS = -g -Wall

all: main

main: hdlc udp crc16
	$(CC) -o trab1 main.c hdlc.o udp.o crc16.o $(CFLAGS)

hdlc:
	$(CC) -c hdlc.c -o hdlc.o
	
udp:
	$(CC) -c udp.c -o udp.o	

crc16:
	$(CC) -c crc16.c -o crc16.o	
	
clean: 
	-rm trab1 *.o *~
	clear	
	ls
