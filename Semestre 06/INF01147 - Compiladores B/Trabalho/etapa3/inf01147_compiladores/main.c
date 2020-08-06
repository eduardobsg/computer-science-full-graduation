#include <stdio.h>
#include <stdlib.h>

#include "lex.yy.h"

extern void initMe();
int yyparse(void);

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
        fprintf(stderr, "Cannot open source file [%s]\n", argv[1]);
        return(2);
    }

	// yyparse() returns 0 if ok, but 0 fails the IF statement
	// we were exiting with error 3 (bellow) when correct!
    if (yyparse() == 0) {
        return (0);
    }

    fprintf(stderr, "End of program.\n");
    return 3;
}
