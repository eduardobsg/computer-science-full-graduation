#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "lex.yy.h"
#include "y.tab.h"

int yyparse(void);
void initMe();

int main(int argc, char** argv)
{
	initMe();

    //verify if source file was provided
    if (argc < 2) {
        fprintf(stderr, "First parameter should be source file\n");
        exit(1);
    }

    //try to open source file
    if (!(yyin = fopen(argv[1], "r"))) {
        fprintf(stderr, "Cannot open source file\n");
        exit(1);
    }
    
    if (yyparse()) {
        exit(0);
    }
    
    fprintf(stderr, "End of program.\n");
    exit(3);
}
