CC = gcc
CFLAGS = -g -Wall 
LIBS = -L./lib -lsisop
OBJS = libsisop unucleo.o fifo.o pcb.o

all: t01_queue_FIFO t02_mproc_create t03_mproc_create_and_scheduler t04_mproc_create_and_scheduler t05_mproc_yield t06_mproc_yield_multi_priority t07_mproc_join t08_double_join t09_create_200_processes

t09_create_200_processes: $(OBJS)
	$(CC) -o testes/t09_create_200_processes testes/t09_create_200_processes.c $(LIBS) $(CFLAGS)

t08_double_join: $(OBJS)
	$(CC) -o testes/t08_double_join testes/t08_double_join.c $(LIBS) $(CFLAGS)

t07_mproc_join: $(OBJS)
	$(CC) -o testes/t07_mproc_join testes/t07_mproc_join.c $(LIBS) $(CFLAGS)

t06_mproc_yield_multi_priority: $(OBJS)
	$(CC) -o testes/t06_mproc_yield_multi_priority testes/t06_mproc_yield_multi_priority.c $(LIBS) $(CFLAGS)

t05_mproc_yield: $(OBJS)
	$(CC) -o testes/t05_mproc_yield testes/t05_mproc_yield.c $(LIBS) $(CFLAGS)

t04_mproc_create_and_scheduler: $(OBJS)
	$(CC) -o testes/t04_mproc_create_and_scheduler testes/t04_mproc_create_and_scheduler.c $(LIBS) $(CFLAGS)

t03_mproc_create_and_scheduler: $(OBJS)
	$(CC) -o testes/t03_mproc_create_and_scheduler testes/t03_mproc_create_and_scheduler.c $(LIBS) $(CFLAGS)

t02_mproc_create: $(OBJS)
	$(CC) -o testes/t02_mproc_create testes/t02_mproc_create.c $(LIBS) $(CFLAGS)
	
t01_queue_FIFO: $(OBJS)
	$(CC) -o testes/t01_queue_FIFO testes/t01_queue_FIFO.c $(LIBS) $(CFLAGS)

libsisop: unucleo.o fifo.o pcb.o 
	ar crs lib/libsisop.a unucleo.o fifo.o pcb.o

unucleo.o: src/unucleo.c fifo.o pcb.o
	$(CC) -c src/unucleo.c fifo.o -o unucleo.o
	
fifo.o: src/fifo.c pcb.o
	$(CC) -c src/fifo.c pcb.o -o fifo.o
	
pcb.o: src/pcb.c
	$(CC) -c src/pcb.c -o pcb.o


