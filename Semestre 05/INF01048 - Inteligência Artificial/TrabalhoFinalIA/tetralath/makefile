CC = gcc
CFLAGS = -Wall -g
LIBS = -lglui -lglut -lGLU -lhighgui
OBJS = board.o interface.o minimax.o round.o

all: tetralath t01 clean

#executable
tetralath: src/tetralath.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

#tests
t01: tests/t01.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

#inc
minimax.o: src/minimax.c inc/minimax.h 
	$(CC) $(CFLAGS) $< -c $(LIBS)
interface.o: src/interface.c inc/interface.h
	$(CC) $(CFLAGS) $< -c $(LIBS)
board.o: src/board.c inc/board.h
	$(CC) $(CFLAGS) $< -c $(LIBS)	
round.o: src/round.c inc/round.h
	$(CC) $(CFLAGS) $< -c $(LIBS)	

#clean
clean: 
	rm -f *.o
