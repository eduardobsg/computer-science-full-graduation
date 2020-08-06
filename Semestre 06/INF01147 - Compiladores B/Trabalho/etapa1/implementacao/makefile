all: etapa1

etapa1: main2.o lex.yy.o hashtable.o
	gcc main2.o lex.yy.o hashtable.o -o etapa1 -Wall

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c	

hashtable.o: hashtable.c
	gcc -c hashtable.c	

main2.o: main2.c
	lex --header-file=lex.yy.h --outfile=lex.yy.c scanner.l
	gcc -c main2.c

clean: 
	rm etapa1 lex.yy.c lex.yy.h *.o
