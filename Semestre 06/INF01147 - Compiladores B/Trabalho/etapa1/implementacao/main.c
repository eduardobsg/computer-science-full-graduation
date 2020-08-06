#include <stdio.h>

int main(int argc, char* argv[]) {

    // scanner's init
    initMe(); //declaration in scanner.l

    // verify if source file was provided
    if (argc < 2) {
        fprintf(stderr, "First parameter should be source file\n");
        exit(1);
    }

    // try to open source file
    if (!(yyin = fopen(argv[1], "r"))) {
        fprintf(stderr, "Cannot open source file\n");
    }

	// counter is used to count the number of entries
	int counter = 0;
    // start scanning tokens, one by one
    int token;
    while (isRunning()) {
        // use scanner to read one token
        token = yylex();
		counter++;
        // check if scanner reached end
        if (!isRunning()) return 0;

        /* 
         * Anotações 21/03
         * 1- case sensitive
         * 2- Hexadecimal - tanto faz 
         * 3- Booleanos TRUE FALSE 
         */
		
		printf("Entry %d: ", counter);

        switch (token) {
            //***************
            // KEY WORDS
            //***************
        case KW_WORD:
            printf("KW_WORD ");
            break;
        case KW_BOOL:
            printf("KW_BOOL ");
            break;
        case KW_BYTE:
            printf("KW_BYTE ");
            break;
        case KW_IF:
            printf("KW_IF ");
            break;
        case KW_THEN:
            printf("KW_THEN ");
            break;
        case KW_ELSE:
            printf("KW_ELSE ");
            break;
        case KW_LOOP:
            printf("KW_LOOP ");
            break;
        case KW_RETURN:
            printf("KW_RETURN ");
            break;
        case KW_INPUT:
            printf("KW_INPUT ");
            break;
        case KW_OUTPUT:
            printf("KW_OUTPUT ");
            break;
            //***************
            // OPERATORS
            //***************
        case OPERATOR_LE:
            printf("OPERATOR_LE ");
            break;
        case OPERATOR_GE:
            printf("OPERATOR_GE ");
            break;
        case OPERATOR_EQ:
            printf("OPERATOR_EQ ");
            break;
        case OPERATOR_NE:
            printf("OPERATOR_NE ");
            break;
        case OPERATOR_AND:
            printf("OPERATOR_AND ");
            break;
        case OPERATOR_OR:
            printf("OPERATOR_OR ");
            break;
            //***************
            // CHARS
            //***************
        case ',':
            printf(", ");
            break;
        case ';':
            printf("; ");
            break;
        case ':':
            printf(": ");
            break;
        case '(':
            printf("( ");
            break;
        case ')':
            printf(") ");
            break;
        case '[':
            printf("[ ");
            break;
        case ']':
            printf("] ");
            break;
        case '{':
            printf("{ ");
            break;
        case '}':
            printf("} ");
            break;
        case '+':
            printf("+ ");
            break;
        case '-':
            printf("- ");
            break;
        case '*':
            printf("* ");
            break;
        case '/':
            printf("/ ");
            break;
        case '<':
            printf("< ");
            break;
        case '>':
            printf("> ");
            break;
        case '=':
            printf("= ");
            break;
        case '!':
            printf("! ");
            break;
        case '&':
            printf("& ");
            break;
        case '$':
            printf("$ ");
            break;
            //***************
            // TOKENS
            //***************
        case TK_IDENTIFIER:
            printf("TK_IDENTIFIER ");
            break;
            //***************
            // LITERALS
            //***************
        case LIT_INTEGER:
            printf("LIT_INTEGER ");
            break;
        case LIT_FALSE:
            printf("LIT_FALSE ");
            break;
        case LIT_TRUE:
            printf("LIT_TRUE ");
            break;
        case LIT_CHAR:
            printf("LIT_CHAR ");
            break;
        case LIT_STRING:
            printf("LIT_STRING ");
            break;
            //***************
            // ERROR
            //***************
        case TOKEN_ERROR:
            printf("TOKEN_ERROR ");
            break;
        default:
            printf("OOPS: %i ", token);
        }
        printf("at line %i\n", getLineNumber());
    }

    // scanner's destruction
    destroyMe();
    return (EXIT_SUCCESS);
}
