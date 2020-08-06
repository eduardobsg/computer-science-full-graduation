# FCG - 2011/01
# Program: Fun Flight

# Variables
#CC = colorgcc
FLAGS = -w

OBJS = lib/model.o lib/camera.o lib/light.o lib/moviment.o lib/EasyBMP.o
OBJLIB = lib/glm.o lib/texture.o 

LIBS = -lGL -lglut -lGLU
BIN = fun-flight

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(FLAGS) $(LIBS) 

all: fun-flight.cpp $(OBJS) $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(FLAGS) $(LIBS) 

clean:
	rm -f fun-flight
	rm -f *.o

