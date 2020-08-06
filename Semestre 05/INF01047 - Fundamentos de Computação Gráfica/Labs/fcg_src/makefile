# FCG - 2011/01
# Program: FCG

# Variables
CC = colorgcc
FLAGS = -w

OBJS = EasyBMP.o
OBJLIB = 

LIBS = -lGL -lglut -lGLU
BIN = fcg

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@ $(FLAGS) $(LIBS) 

all: main.cpp $(OBJS) $(OBJLIB)
	$(CC) $(FLAGS) $^ -o $(BIN) $(FLAGS) $(LIBS) 

clean:
	rm -f fcg
	rm -f *.o

