# Programa: BasicoDesenho1.cpp
# Descrição:

# Variáveis
CC = gcc
CFLAGS = -Wall -c
GLFLAGS = -L/usr/X11R6/lib -lGL -lglut -lGLU

# Alvo e dependências
all: basicoDesenho1

basicoDesenho1: basicoDesenho1.o
	$(CC) basicoDesenho1.o -o basicoDesenho1 $(GLFLAGS)

basicoDesenho1.o: basicoDesenho1.cpp
	$(CC) $(CFLAGS) basicoDesenho1.cpp 

clear: 
	rm -rf *o basicoDesenho1
