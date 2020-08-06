# Program: objLoader

# Variables
CC = colorgcc
FLAGS = -w

OBJS = lib/model.o lib/camera.o 
OBJLIB = lib/glm.o lib/texture.o 

LIBS = -lGL -lglut -lGLU
BIN = objLoader

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(FLAGS) $(LIBS) 

all: objLoader.cpp $(OBJS) $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(FLAGS) $(LIBS) 

clean:
	rm -f objLoader
	rm -f *.o

