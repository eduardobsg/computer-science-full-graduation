all:	teste1 teste2 teste3 teste4 teste5 teste6 teste7 teste8 teste9 teste128 teste256 teste10 testeN testeX testeV

testeV:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/testeV testes/testeJoinVoid.c -L./lib -lsisop -Wall

testeX:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/testeX testes/testeX.c -L./lib -lsisop -Wall

testeN:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/testeN testes/testeN.c -L./lib -lsisop -Wall

teste256:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste256 testes/teste256.c -L./lib -lsisop -Wall

teste128:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste128 testes/teste128.c -L./lib -lsisop -Wall

teste10:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste10 testes/teste10joinduplo.c -L./lib -lsisop -Wall

teste9:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste9 testes/teste9joincascade.c -L./lib -lsisop -Wall

teste8:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste8 testes/teste8.c -L./lib -lsisop -Wall

teste7:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste7 testes/teste7join.c -L./lib -lsisop -Wall

teste6:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste6 testes/teste6threadsyield.c -L./lib -lsisop -Wall

teste5:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste5 testes/teste5.c -L./lib -lsisop -Wall

teste4:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste4 testes/teste4join.c -L./lib -lsisop -Wall

teste3:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste3 testes/teste3yield.c -L./lib -lsisop -Wall
	
teste1:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste1 testes/teste1.c -L./lib -lsisop -Wall

teste2:  libsisop libsisop.o fifo.o pcb.o
	gcc -o testes/teste2 testes/teste2.c -L./lib -lsisop -Wall

libsisop: libsisop.o fifo.o pcb.o
	ar crs lib/libsisop.a libsisop.o fifo.o pcb.o

libsisop.o: src/libsisop.c fifo.o pcb.o
	gcc -c src/libsisop.c fifo.o -o libsisop.o
	
fifo.o: src/fifo.c pcb.o
	gcc -c src/fifo.c pcb.o -o fifo.o
	
pcb.o: src/pcb.c
	gcc -c src/pcb.c -o pcb.o
