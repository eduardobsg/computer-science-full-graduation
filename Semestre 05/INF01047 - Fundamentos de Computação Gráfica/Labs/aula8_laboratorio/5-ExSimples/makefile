# Programa: exsimples.cpp
# Descrição:

# Variáveis
CC = gcc
CFLAGS = -Wall -c
GLFLAGS = -L/usr/X11R6/lib -lGL -lglut -lGLU

# Alvo e dependências
all: exsimples

exsimples: exsimples.o
	$(CC) exsimples.o -o exsimples $(GLFLAGS)

exsimples.o: exsimples.cpp
	$(CC) $(CFLAGS) exsimples.cpp 

clear: 
	rm -rf *o exsimples
