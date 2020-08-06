all: etapa3

# yacc -v : prints the yacc output
etapa3:  
	lex --header-file=lex.yy.h --outfile=lex.yy.c scanner.l
	yacc -d -v parser.y
	gcc -o etapa3 main.c hashtable.c y.tab.c lex.yy.c -Wall -Wno-unused-function

# Test files
src1 = tests/source_etapa3_1.ling
src2 = tests/source_etapa3_2.ling

# Testing with source	
tst: etapa3
	./etapa3 $(src1)
tst2: etapa3
	./etapa3 $(src2)	

# Testing with Valgrind, also
val: etapa3
	valgrind --dsymutil=yes ./etapa3 $(src1)
	
# "-" at the beginning of the line 
# prevents Makefile from stopping at an error
clean: 
	clear
	-rm etapa3 lex.yy.c lex.yy.h y.tab.c y.tab.h
	-rm output.txt
	-rm y.output
	-rm -rf etapa3.dSYM
