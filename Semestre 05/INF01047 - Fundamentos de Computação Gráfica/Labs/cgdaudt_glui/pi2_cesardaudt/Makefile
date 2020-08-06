CC = colorgcc

CFLAGS = -Wall -g

OBJS = pi.o

LIBS = -lglui -lglut -lGLU -lGL -lcxcore -lcv -lhighgui -lcvaux -lml



all: fpi

 
fpi: main.cpp $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


pi.o: pi.cpp pi.h
	$(CC) $(CFLAGS) $< -c $(LIBS)

clean:
	rm -f *.o
	rm -f fpi

