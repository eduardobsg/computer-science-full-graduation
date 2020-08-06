#include <stdio.h>

int yylex();
extern char *yytext;
extern int running;
extern FILE *yyin;

extern int running;
void initMe(void);

int main(int argc, char** argv) {
	initMe();
}
