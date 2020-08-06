# <- Comentários sempre iniciam por "#"
#
############################# Makefile ##########################
all: forkexec
forkexec: forkexec.o make_dummy.o
	gcc -o forkexec forkexec.o make_dummy.o
#-----> Usar TAB e nao espacos

forkexec.o: forkexec.c
	gcc -o forkexec.o -c forkexec.c

make_dummy.o: make_dummy.c
	gcc -o make_dummy.o -c make_dummy.c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf forkexec

