# FCG - 2011/01
# Program: tutor_transformation.c
# Description: 

# Variables
CC = g++
FLAGS = -Wno-write-strings

OBJS =  
OBJLIB = glm.o

LIBS = -lGL -lglut -lGLU
BIN = tutor_transformation

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS) 

all: tutor_transformation.c $(OBJS) $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(LIBS) 

clean:
	rm -f tutor_transformation
	rm -f *.o./
