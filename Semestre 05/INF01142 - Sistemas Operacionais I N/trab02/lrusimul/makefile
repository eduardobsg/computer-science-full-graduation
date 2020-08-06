CC = gcc
CFLAGS = -g -Wall 
OBJS = stack.o fifo.o parser.o memory.o process.o

all: lrusimul t01_stack t01 t02 t03 t04 clean

#executable
lrusimul: lrusimul.o $(OBJS)
	$(CC) lrusimul.o $(OBJS) -o bin/lrusimul $(CFLAGS) 
lrusimul.o: src/lrusimul.c
	$(CC) -c src/lrusimul.c $(CFLAGS)

#tests
t04: t04.o $(OBJS)
	$(CC) t04.o $(OBJS) -o testes/t04 $(CFLAGS) 
t04.o: testes/t04.c
	$(CC) -c testes/t04.c $(CFLAGS)

t03: t03.o $(OBJS)
	$(CC) t03.o $(OBJS) -o testes/t03 $(CFLAGS) 
t03.o: testes/t03.c
	$(CC) -c testes/t03.c $(CFLAGS)

t02: t02.o $(OBJS)
	$(CC) t02.o $(OBJS) -o testes/t02 $(CFLAGS) 
t02.o: testes/t02.c
	$(CC) -c testes/t02.c $(CFLAGS)

t01: t01.o $(OBJS)
	$(CC) t01.o $(OBJS) -o testes/t01 $(CFLAGS) 
t01.o: testes/t01.c
	$(CC) -c testes/t01.c $(CFLAGS)
	
t01_stack: t01_stack.o $(OBJS)
	$(CC) t01_stack.o $(OBJS) -o testes/t01_stack $(CFLAGS) 
t01_stack.o: testes/t01_stack.c
	$(CC) -c testes/t01_stack.c $(CFLAGS)	

# libraries
parser.o: src/parser.c include/parser.h
	$(CC) -c src/parser.c $(CFLAGS)

process.o: src/process.c include/process.h
	$(CC) -c src/process.c $(CFLAGS)
	
memory.o: src/memory.c include/memory.h
	$(CC) -c src/memory.c $(CFLAGS)

fifo.o: src/fifo.c include/fifo.h
	$(CC) -c src/fifo.c $(CFLAGS)
	
stack.o: src/stack.c include/stack.h
	$(CC) -c src/stack.c $(CFLAGS)
	
clean:
	\rm -f *.o
	
