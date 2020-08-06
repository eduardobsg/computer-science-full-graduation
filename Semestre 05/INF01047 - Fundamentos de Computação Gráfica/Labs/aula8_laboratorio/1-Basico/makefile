# FCG - 2011/01
# Programa: basico.cpp
# Descrição: 
 
# Terminal command line: gcc -L/usr/X11R6/lib -lGL -lglut -lGLU -lm basico.cpp -o basico

# Variáveis
CC = gcc
GLFLAGS = -L/usr/X11R6/lib -lGL -lglut -lGLU
CFLAGS = -Wall -c -lm

# Alvo (tarket) 
all: basico

basico: basico.o
	$(CC) basico.o -o basico $(GLFLAGS) 

basico.o: basico.cpp
	$(CC) $(CFLAGS) basico.cpp 

clean:
	rm -rf *o basico
