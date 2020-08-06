#ifndef ASTREE_H
#define	ASTREE_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_SONS 				4	//maximum number of sons of a node in the syntax tree

/* Begin */
#define ASTREE_PROGRAM			11	//begin of program - almighty father node
#define ASTREE_DECL				12	//for variable declaration	
#define ASTREE_SIMPLE_DECL		13	
#define ASTREE_ARRAY_DECL		14
#define ASTREE_ARRAY_DECL_INI	15	//for array declaration with initialization
#define ASTREE_ARRAY_DECL_LITS	16	//list of initialization literals for an array declaration
#define ASTREE_POINTER_DECL		17	
#define ASTREE_FUNC				18
#define ASTREE_FUNC1			19	
#define ASTREE_FUNC2			20	
#define ASTREE_FUNC3			21	
#define ASTREE_FUNC4			22		
#define ASTREE_FUNC_PARAM		23	//list of parameters of a function prototype
#define ASTREE_FUNC_DECL		24	//list of variable declarations of a function 
#define ASTREE_SYMBOL			25	//terminals: identifier and literals

/* Expressions */
#define ASTREE_ADD				30
#define ASTREE_SUB				31
#define ASTREE_MUL				32
#define ASTREE_DIV				33
#define ASTREE_OPERATOR_LE		34
#define ASTREE_OPERATOR_GE		35
#define ASTREE_OPERATOR_EQ		36
#define ASTREE_OPERATOR_NE		37
#define ASTREE_OPERATOR_OR		38
#define ASTREE_OPERATOR_AND		39
#define ASTREE_OPERATOR_GREATER	40    
#define ASTREE_OPERATOR_LESS	41
#define ASTREE_VECT_ACCESS		42	//for an expression that accesses a vector position
#define ASTREE_EXP_PARENTESIS	43	//for expressions between parentesis
#define ASTREE_FUNC_CALL		44	//for funciton calls 
#define ASTREE_FUNC_CALL_LIST	45	//list of parameters of a function call
#define ASTREE_UNARY_MINUS		46		
#define ASTREE_POINTER			47	
#define ASTREE_DEREFERENCE		48	

/* Commands */
#define ASTREE_CMDL				60	//list of commands
#define ASTREE_SCALA_ASS		61	//scalar assigment
#define ASTREE_VECT_SCALA_ASS	62	//scalar assigment to a vector position
#define ASTREE_IF				63	
#define ASTREE_IF_ELSE			64	
#define ASTREE_LOOP				65	
#define ASTREE_INPUT			66	
#define ASTREE_OUTPUT			67	
#define ASTREE_OUTPUT_LIST		68	//list of values of a output command
#define ASTREE_RETURN			69	
#define ASTREE_CMD_BLOCK		70


typedef struct astree_node {
	int type;
	Entry * symbol;
	struct astree_node * son[MAX_SONS];
} ASTREE;


/* Prototypes */

/* Creates a node for the syntax tree */
ASTREE * astreeCreate(int type, Entry *n, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3);

/* Prints the type of a node and the value of the terminal token if applied */
void astreePrintSingle(ASTREE *node);

/* Given a node, prints all the information of it and its sons. Make calls to astreePrintSingle */
void astreePrintTree(int level, ASTREE *node);

/* Creates an output file similar to the input file */
void astreeTranslate(ASTREE *node);

/* Node to string. Given a node prints its information on the file,
translated to a format similar to the input file. */
void n2str(int level, ASTREE *node);

/* Prints n '\t' */
void printLevel(int level);

#endif	/* ASTREE_H */

