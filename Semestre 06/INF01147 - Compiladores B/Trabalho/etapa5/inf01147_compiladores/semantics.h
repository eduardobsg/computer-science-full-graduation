#ifndef SEMANTICS_H
#define	SEMANTICS_H

#include "astree.h"

// Needed for pointer checks
#define KW_WORD_POINTER	9998
#define KW_BOOL_POINTER	9999

extern Hashtable *hashtable;
extern int getLineNumber();

//======================================================================
// Semantic Checks 
//======================================================================

// FK new stuff

int isDeclared(ASTREE * node);

int typeOfExpression(ASTREE * node);

int typeMerge(int typeA, int typeB);

char * tr(int value);

int isSymbolPutToCorrectUse(ASTREE * node);

// FK new stuff (end)

/* 1 - Check double declarations and update hash node info */
void updateAndCheckNode(ASTREE *node, int semanticType, int varType, int lineMumber);

/* 2 - Check initialization types for simple variables, arrays and pointers */
void astreeSemanticCheck(ASTREE *node);

/* 3 - Check the number of arguments in a function call and its types */
ASTREE * checkFunctionParameters(ASTREE *node, ASTREE *funcArgs);

/* 4 - Check if identifier is declared and being correctly used */
void testIfDeclaredAndCorrectUse(ASTREE *node, int varType);

/* 5 - Check type of an array index */
void testIndexType(ASTREE *node);

/* 6 - Check if the type of the functions return is correct */
void verifyFunctionReturnType(ASTREE *node);

//======================================================================
// Auxiliar Functions
//======================================================================

/* Match semanticType type against a lexicalType type */
int checkTypeMatch(int semanticType, int lexicalType);

/* For function declaration updates the parameter types in the hash node
associated with the astree node */
ASTREE * fillParamList(ASTREE *node, ASTREE *paramList);

/* Gets the semanticType of a return command inside a command block */
void getSemanticTypeOfCommandBlock(ASTREE *node, int *receivedType, int *returnCommandLine);

char * tr(int value);

#endif	/* SEMANTICS_H */
