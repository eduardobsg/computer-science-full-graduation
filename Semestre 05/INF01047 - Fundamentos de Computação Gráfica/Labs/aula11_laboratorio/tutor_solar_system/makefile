# FCG - 2011/01
# Programa: solar_system.cpp
# Descrição: 
 
# Terminal command line: gcc -L/usr/X11R6/lib -lGL -lglut -lGLU -lm solar_system.cpp -o solar_system

# Variáveis
CC = gcc
GLFLAGS = -L/usr/X11R6/lib -lGL -lglut -lGLU
CFLAGS = -Wall -c -lm

# Alvo (tarket) 
all: solar_system

solar_system: solar_system.o
	$(CC) solar_system.o -o solar_system $(GLFLAGS) 

solar_system.o: solar_system.cpp
	$(CC) $(CFLAGS) solar_system.cpp 

clean:
	rm -rf *o solar_system
