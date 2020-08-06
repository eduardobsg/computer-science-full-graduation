all: etapa4

# yacc -v : prints the yacc output
etapa4:  
	lex --header-file=lex.yy.h --outfile=lex.yy.c scanner.l
	yacc -d -v parser.y
	gcc -o etapa4 main.c hashtable.c y.tab.c lex.yy.c -Wall -Wno-unused-function

# Test files
src31 = tests/source_etapa3_1.ling
src32 = tests/source_etapa3_2.ling
src41 = tests/source_etapa4_1.ling
src42 = tests/source_etapa4_2.ling
src43 = tests/source_etapa4_3.ling
src44 = tests/source_etapa4_4.ling
src45 = tests/source_etapa4_5.ling
src4j = tests/source_etapa4_j.ling

# Testing with source	
tst: etapa4
	./etapa4 $(src4j)	

# Testing with Valgrind, also
val: etapa4
	valgrind --dsymutil=yes ./etapa4 $(src4j)
	
# "-" at the beginning of the line 
# prevents Makefile from stopping at an error
clean: 
	-rm etapa4 lex.yy.c lex.yy.h y.tab.c y.tab.h
	-rm output.txt
	-rm y.output
	-rm -rf etapa4.dSYM
	clear
	ls
