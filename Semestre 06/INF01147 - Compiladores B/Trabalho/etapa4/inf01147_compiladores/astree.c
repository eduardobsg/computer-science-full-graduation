#include "semantics.h"
#include "hashtable.h"
#include "astree.h"
#include "y.tab.h"

#define FILENAME "output.txt"

/* Creates a node for the syntax tree */
ASTREE *astreeCreate(int nodeType, int contentType, int lineNumber, Entry *n, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3)
{
    ASTREE * node = 0;

    node = (ASTREE *) calloc(1, sizeof (ASTREE));
    node->nodeType = nodeType;
    node->contentType = contentType; //KW_WORD, KW_BOOL or KW_BYTE
   	node->lineNumber = lineNumber;
    node->symbol = n;
    node->son[0] = son0;
    node->son[1] = son1;
    node->son[2] = son2;
    node->son[3] = son3;

    return node;
}

/* Prints the type of a node and the value of the terminal token if applied */
void astreePrintSingle(ASTREE *node)
{
    fprintf(stderr, "ASTREE(");

    switch (node->nodeType) {
    case ASTREE_SYMBOL: fprintf(stderr, "SYMBOL");
        break;
    case ASTREE_ADD: fprintf(stderr, "ADD");
        break;
    case ASTREE_SUB: fprintf(stderr, "SUB");
        break;
    case ASTREE_MUL: fprintf(stderr, "MUL");
        break;
    case ASTREE_DIV: fprintf(stderr, "DIV");
        break;
    case ASTREE_SCALA_ASS: fprintf(stderr, "SCALAR-ASSIGNMENT");
        break;
    case ASTREE_VECT_SCALA_ASS: fprintf(stderr, "VECT-SCALAR-ASSIGNMENT");
        break;
    case ASTREE_CMDL: fprintf(stderr, "CMD-LIST");
        break;
    case ASTREE_CMD_BLOCK: fprintf(stderr, "CMD-BLOCK");
        break;
    case ASTREE_PROGRAM: fprintf(stderr, "PROGRAM");
        break;
    case ASTREE_SIMPLE_DECL: fprintf(stderr, "SIMPLE-DECL");
        break;
    case ASTREE_ARRAY_DECL: fprintf(stderr, "ARRAY-DECL");
        break;
    case ASTREE_ARRAY_DECL_INI: fprintf(stderr, "ARRAY-DECL-INICIALIZATION");
        break;
    case ASTREE_ARRAY_DECL_LITS: fprintf(stderr, "ARRAY-DECL-INI-LITERALS");
        break;
    case ASTREE_POINTER_DECL: fprintf(stderr, "POINTER-DECL");
        break;
    case ASTREE_DECL: fprintf(stderr, "DECL");
        break;
    case ASTREE_FUNC: fprintf(stderr, "FUNC");
        break;
    case ASTREE_FUNC1: fprintf(stderr, "FUNC1");
        break;
    case ASTREE_FUNC2: fprintf(stderr, "FUNC2");
        break;
    case ASTREE_FUNC3: fprintf(stderr, "FUNC3");
        break;
    case ASTREE_FUNC4: fprintf(stderr, "FUNC4");
        break;
    case ASTREE_FUNC_PARAM: fprintf(stderr, "FUNC-PARAMETERS");
        break;
    case ASTREE_FUNC_DECL: fprintf(stderr, "FUNC-DECL");
        break;
    case ASTREE_IF: fprintf(stderr, "IF");
        break;
    case ASTREE_IF_ELSE: fprintf(stderr, "IF-ELSE");
        break;
    case ASTREE_OPERATOR_GE: fprintf(stderr, "OPERATOR-GE");
        break;
    case ASTREE_OPERATOR_LE: fprintf(stderr, "OPERATOR-LE");
        break;
    case ASTREE_OPERATOR_EQ: fprintf(stderr, "OPERATOR-EQ");
        break;
    case ASTREE_OPERATOR_NE: fprintf(stderr, "OPERATOR-NE");
        break;
    case ASTREE_OPERATOR_AND: fprintf(stderr, "OPERATOR-AND");
        break;
    case ASTREE_OPERATOR_OR: fprintf(stderr, "OPERATOR-OR");
        break;
    case ASTREE_OPERATOR_GREATER: fprintf(stderr, "OPERATOR-GREATER");
        break;
    case ASTREE_OPERATOR_LESS: fprintf(stderr, "OPERATOR-LESS");
        break;
    case ASTREE_UNARY_MINUS: fprintf(stderr, "EXP-UNARY-MINUS");
        break;
    case ASTREE_POINTER_REFERENCE: fprintf(stderr, "EXP-POINTER-REFERENCE");
        break;
    case ASTREE_POINTER_DEREFERENCE: fprintf(stderr, "EXP-POINTER-DEREFERENCE");
        break;
    case ASTREE_VECT_ACCESS: fprintf(stderr, "EXP-VECTOR-POSITION-ACCESS");
        break;
    case ASTREE_EXP_PARENTESIS: fprintf(stderr, "EXP-PARENTESIS");
        break;
    case ASTREE_FUNC_CALL: fprintf(stderr, "EXP-FUNC-CALL");
        break;
    case ASTREE_FUNC_CALL_LIST: fprintf(stderr, "EXP-FUNC-CALL-LIST");
        break;
    case ASTREE_LOOP: fprintf(stderr, "LOOP");
        break;
    case ASTREE_INPUT: fprintf(stderr, "INPUT");
        break;
    case ASTREE_RETURN: fprintf(stderr, "RETURN");
        break;
    case ASTREE_OUTPUT: fprintf(stderr, "OUTPUT");
        break;
    case ASTREE_OUTPUT_LIST: fprintf(stderr, "OUTPUT-LIST");
        break;
    default: fprintf(stderr, "UNKNOWN");
    }

    if (node->symbol) {
        if (node->symbol->text) {
            fprintf(stderr, ", %s", node->symbol->text);
        }
    }

    fprintf(stderr, ")\n");
}

/* Given a node, prints all the information of it and its sons. Make calls to astreePrintSingle */
void astreePrintTree(int level, ASTREE *node)
{
    if (!node) {
        //printf("Node is empty.\n");
        return;
    }

    int t;
    for (t = 0; t < level; t++) {
        fprintf(stderr, "...|");
    }

   	astreePrintSingle(node);

    int i;
    for (i = 0; i < MAX_SONS; ++i) {
        astreePrintTree(level + 1, node->son[i]);
    }
}

/* Creates an output file similar to the input file */
void astreeTranslate(ASTREE *node)
{
    fprintf(stderr, "\nProgram Translate: \n\n");
    n2str(0, node);
    printf("\n");
}

/* Node to string. Given a node prints its information on the file,
translated to a format similar to the input file. */
void n2str(int level, ASTREE *node)
{
    if (node == NULL) {
        return;
    }

    if (node->nodeType == ASTREE_CMD_BLOCK)
        output("\n");

    if (node->nodeType != ASTREE_CMDL) {
        printLevel(level); /* Prints '\t' */
    }

    switch (node->nodeType) {
    case ASTREE_SYMBOL:
        //fprintf(stderr, "SYMBOL");
        output(node->symbol->text);
        break;
    case ASTREE_ADD:
        //fprintf(stderr, "ADD");
        n2str(0, node->son[0]);
        output(" + ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_SUB:
        //fprintf(stderr, "SUB");
        n2str(0, node->son[0]);
        output(" - ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_MUL:
        //fprintf(stderr, "MUL");
        n2str(0, node->son[0]);
        output(" * ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_DIV:
        //fprintf(stderr, "DIV");
        n2str(0, node->son[0]);
        output(" / ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_SCALA_ASS:
        //fprintf(stderr, "SCALAR-ASSIGNMENT");
        output(node->son[0]->symbol->text);
        output(" = ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_VECT_SCALA_ASS:
        //fprintf(stderr, "VECT-SCALAR-ASSIGNMENT");
        //identifier '[' exp ']' '=' exp	
        output(node->son[0]->symbol->text);
        output("[");
        output(node->son[1]->symbol->text);
        output("] = ");
        n2str(0, node->son[2]);
        break;
    case ASTREE_CMDL:
        //fprintf(stderr, "CMD-LIST");
        n2str(level, node->son[0]);
        output(";\n");
        if (node->son[1] != NULL) {
            n2str(level, node->son[1]);
        }
        break;
    case ASTREE_CMD_BLOCK:
        //fprintf(stderr, "CMD-BLOCK");
        output("{\n");
        n2str(level + 1, node->son[0]);
        printLevel(level);
        output("}");
        break;
    case ASTREE_PROGRAM:
        //fprintf(stderr, "PROGRAM");
        n2str(level, node->son[0]);
        break;
    case ASTREE_SIMPLE_DECL:
        //fprintf(stderr, "SIMPLE-DECL");
        //output("type ");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output(" : ");
        output(node->son[1]->symbol->text);
        output(";");
        break;
    case ASTREE_ARRAY_DECL: //array without initialization
        //fprintf(stderr, "ARRAY-DECL");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output("[");
        output(node->son[1]->symbol->text);
        output("];");
        break;
    case ASTREE_ARRAY_DECL_INI: //array with initialization
        //fprintf(stderr, "ARRAY-DECL-INICIALIZATION");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output("[");
        output(node->son[1]->symbol->text);
        output("] : ");
        n2str(0, node->son[2]);
        break;
    case ASTREE_ARRAY_DECL_LITS:
        //fprintf(stderr, "ARRAY-DECL-INI-LITERALS");		
        if (node->son[1] != NULL) {
            output(node->son[0]->symbol->text);
            output(" ");
            n2str(0, node->son[1]);
        }
        else {
            output(node->son[0]->symbol->text);
            output(";");
        }
        break;
    case ASTREE_POINTER_DECL:
        //fprintf(stderr, "POINTER-DECL");
        output(nodeCType(node));
        output(" $");
        output(node->son[0]->symbol->text);
        output(" : ");
        output(node->son[1]->symbol->text);
        output(";");
        break;
    case ASTREE_DECL:
        //fprintf(stderr, "DECL");
        if (node->son[0] != NULL) { //has at least 1 son
            n2str(level, node->son[0]);
            if (node->son[1] != NULL) { //has a second son
                output("\n");
                n2str(level, node->son[1]);
            }
        }
        break;
    case ASTREE_FUNC:
        //fprintf(stderr, "FUNC");
        output("\n");
        if (node->son[0] != NULL) { //has at least 1 son
            n2str(level, node->son[0]);
            if (node->son[1] != NULL) { //has a second son
                n2str(level, node->son[1]);
            }
        }
        break;
    case ASTREE_FUNC1:
        //fprintf(stderr, "FUNC1");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output("(");
        n2str(0, node->son[1]);
        output(")\n");
        n2str(1, node->son[2]);
        n2str(0, node->son[3]);
        output("\n");
        break;
    case ASTREE_FUNC2:
        //fprintf(stderr, "FUNC2");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output("()\n");
        n2str(1, node->son[1]);
        n2str(0, node->son[2]);
        output("\n");
        break;
    case ASTREE_FUNC3:
        //fprintf(stderr, "FUNC3");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output("(");
        n2str(0, node->son[1]);
        output(")");
        n2str(0, node->son[2]);
        output("\n");
        break;
    case ASTREE_FUNC4:
        //fprintf(stderr, "FUNC4");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        output("()");
        n2str(0, node->son[1]);
        output("\n");
        break;
    case ASTREE_FUNC_PARAM:
        //fprintf(stderr, "FUNC-PARAMETERS");
        output(nodeCType(node));
        output(" ");
        output(node->son[0]->symbol->text);
        if (node->son[1] != NULL) {
            output(", ");
            n2str(0, node->son[1]);
        }
        break;
    case ASTREE_FUNC_DECL:
        //fprintf(stderr, "FUNC-DECL");
        n2str(0, node->son[0]);
        if (node->son[1] != NULL) {
            output("\n");
            n2str(level, node->son[1]);
        }
        break;
    case ASTREE_IF:
        //fprintf(stderr, "IF");
        output("if(");
        n2str(0, node->son[0]);
        output(") then ");
        if (node->son[1]->nodeType == ASTREE_CMD_BLOCK)
            n2str(level, node->son[1]);
        else
            n2str(0, node->son[1]);
        break;
    case ASTREE_IF_ELSE:
        //fprintf(stderr, "IF-ELSE");
        output("if(");
        n2str(0, node->son[0]);
        output(") then ");
        if (node->son[1]->nodeType == ASTREE_CMD_BLOCK)
            n2str(level, node->son[1]);
        else
            n2str(0, node->son[1]);
        output(" else ");
        if (node->son[2]->nodeType == ASTREE_CMD_BLOCK)
            n2str(level, node->son[2]);
        else
            n2str(0, node->son[2]);
        break;
    case ASTREE_OPERATOR_GE:
        //fprintf(stderr, "OPERATOR-GE");
        n2str(0, node->son[0]);
        output(" >= ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_LE:
        //fprintf(stderr, "OPERATOR-LE");
        n2str(0, node->son[0]);
        output(" <= ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_EQ:
        //fprintf(stderr, "OPERATOR-EQ");
        n2str(0, node->son[0]);
        output(" == ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_NE:
        //fprintf(stderr, "OPERATOR-NE");
        n2str(0, node->son[0]);
        output(" != ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_AND:
        //fprintf(stderr, "OPERATOR-AND");
        n2str(0, node->son[0]);
        output(" && ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_OR:
        //fprintf(stderr, "OPERATOR-OR");
        n2str(0, node->son[0]);
        output(" || ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_GREATER:
        //fprintf(stderr, "OPERATOR-GREATER");
        n2str(0, node->son[0]);
        output(" > ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_OPERATOR_LESS:
        //fprintf(stderr, "OPERATOR-LESS");
        n2str(0, node->son[0]);
        output(" < ");
        n2str(0, node->son[1]);
        break;
    case ASTREE_UNARY_MINUS:
        //fprintf(stderr, "EXP-UNARY-MINUS");
        output("-");
        n2str(0, node->son[0]);
        break;
    case ASTREE_POINTER_REFERENCE:
        //fprintf(stderr, "EXP-POINTER-REFERENCE");
        output("*");
        n2str(0, node->son[0]);
        break;
    case ASTREE_POINTER_DEREFERENCE:
        //fprintf(stderr, "EXP-DEREFERENCE");
        output("&");
        n2str(0, node->son[0]);
        break;
    case ASTREE_VECT_ACCESS:
        //fprintf(stderr, "EXP-VECTOR-POSITION-ACCESS");
        output(node->son[0]->symbol->text);
        output("[");
        output(node->son[1]->symbol->text);
        output("]");
        break;
    case ASTREE_EXP_PARENTESIS:
        //fprintf(stderr, "EXP-PARENTESIS");
        output("(");
        n2str(0, node->son[0]);
        output(")");
        break;
    case ASTREE_FUNC_CALL:
        //fprintf(stderr, "EXP-FUNC-CALL");
        output(node->son[0]->symbol->text);
        output("(");
        if (node->son[1] != NULL)
            n2str(0, node->son[1]);
        output(")");
        break;
    case ASTREE_FUNC_CALL_LIST:
        //fprintf(stderr, "EXP-FUNC-CALL-LIST");
        n2str(0, node->son[0]);
        if (node->son[1] != NULL) {
            output(", ");
            n2str(0, node->son[1]);
        }
        break;
    case ASTREE_LOOP:
        //fprintf(stderr, "LOOP");
        //KW_LOOP '(' exp ')' command
        output("loop(");
        n2str(0, node->son[0]);
        output(")");
        if (node->son[1]->nodeType == ASTREE_CMD_BLOCK)
            n2str(level, node->son[1]);
        else
            n2str(0, node->son[1]);
        break;
    case ASTREE_INPUT:
        //fprintf(stderr, "INPUT");
        output("input ");
        output(node->son[0]->symbol->text);
        break;
    case ASTREE_RETURN:
        //fprintf(stderr, "RETURN");
        output("return ");
        n2str(0, node->son[0]);
        break;
    case ASTREE_OUTPUT:
        //fprintf(stderr, "OUTPUT");
        output("output ");
        n2str(0, node->son[0]);
        break;
    case ASTREE_OUTPUT_LIST:
        //fprintf(stderr, "OUTPUT-LIST");
        n2str(0, node->son[0]);
        if (node->son[1] != NULL) {
            output(", ");
            n2str(0, node->son[1]);
        }
        break;
    default: output("ERROR - NODE UNKNOWN");
    }

}

/* Prints n '\t' */
void printLevel(int level)
{
    int i;
    for (i = 0; i < level; i++)
        output("\t");
}

void output(char *string)
{
    FILE * fp = fopen(FILENAME, "a+");

    //fprintf(stderr, "%s", string);
    //fprintf(fp, "%s", string);

    fclose(fp);
}

char *nodeCType(ASTREE *node)
{
    switch (node->contentType) {
    case KW_WORD:
        return "word";
    case KW_BOOL:
        return "bool";
    case KW_BYTE:
        return "byte";
    default:
        return "nodeCType[UNKNOWN]";
    }
}
