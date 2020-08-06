CC = colorgcc
CFLAGS = -Wall -g
OBJS = photonchopp.o
LIBS = -lglui -lglut -lGLU -lGL -lcxcore -lcv -lhighgui -lcvaux -lml

all: photonchopp

photonchopp: main.cpp $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

photonchopp.o: photonchopp.cpp photonchopp.h
	$(CC) $(CFLAGS) $< -c $(LIBS)

clean:
	rm -f *.o
	rm -f photonchopp

