CC = gcc
FLAGS = -Wall 

all: rec trans

recv: rec.c
	$(CC) recv.c -lc -o rec $(FLAGS) 

sender: trans.c 
	$(CC) trans.c -lc -o trans $(FLAGS) 

clean:
	rm rec trans 
