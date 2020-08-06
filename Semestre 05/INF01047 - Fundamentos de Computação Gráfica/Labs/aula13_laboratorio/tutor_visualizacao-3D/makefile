# FCG - 2011/01
# Program: Obj Loader
# Description: Loads an object from an .obj file and put some texture on it

# Variables
CC = g++
FLAGS = -Wno-write-strings

OBJS =  
OBJLIB = glm.o

LIBS = -lGL -lglut -lGLU
BIN = projection

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS) 

all: projection.c $(OBJS) $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(LIBS) 

clean:
	rm -f projection
	rm -f *.o./
