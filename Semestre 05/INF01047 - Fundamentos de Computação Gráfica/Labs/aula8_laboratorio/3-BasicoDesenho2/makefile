# Programa: BasicoDesenho2.cpp
# Descrição:

# Variáveis
CC = gcc
CFLAGS = -Wall -c
GLFLAGS = -L/usr/X11R6/lib -lGL -lglut -lGLU

# Alvo e dependências
all: basicoDesenho2

basicoDesenho2: basicoDesenho2.o
	$(CC) basicoDesenho2.o -o basicoDesenho2 $(GLFLAGS)

basicoDesenho2.o: basicoDesenho2.cpp
	$(CC) $(CFLAGS) basicoDesenho2.cpp 

clear: 
	rm -rf *o basicoDesenho2
