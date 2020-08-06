# FCG - 2011/01
# Program: Fun Flight

# Variables
CC = colorgcc
FLAGS = -w

OBJLIB = camera.o 

LIBS = -lGL -lglut -lGLU
BIN = main

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(FLAGS) $(LIBS) 

all: main.cpp $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(FLAGS) $(LIBS) 

clean:
	rm -f main
	rm -f *.o


#
