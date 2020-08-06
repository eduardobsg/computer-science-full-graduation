CC = colorgcc

CFLAGS = -Wall -g

OBJS = JpegImage.o

LIBS = -lglui -lglut -lGLU -lGL -ljpeg


all: fpi
 
fpi: FotoShopping.cpp $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


JpegImage.o: JpegImage.cpp JpegImage.h
	$(CC) $(CFLAGS) $< -c $(LIBS)

clean:
	rm -f *.o
	rm -f fpi

