# FCG - 2011/01
# Program: tutor_ilumination.c
# Description: 

# Variables
CC = g++
FLAGS = -Wall
  
OBJLIB = glm.o

LIBS = -lGL -lglut -lGLU
BIN = tutor_ilumination

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS) 

all: tutor_ilumination.c $(OBJS) $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(LIBS) 

clean:
	rm -f tutor_ilumination
	rm -f *.o./
