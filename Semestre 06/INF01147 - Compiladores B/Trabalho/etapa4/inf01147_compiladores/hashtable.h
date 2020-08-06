/* 
 * File:   hashtable.h
 * Author: fkrahe
 * 
 * Started with "Very Simple implementation", found in
 * http://www.sparknotes.com/cs/searching/hashtables/section3.rhtml
 *
 * Created on March 16, 2013, 1:10 PM
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "string.h"

//****************************************
// STRUCTURES
//****************************************

#define TABLE_SIZE 997

#define FUNCTION 	1
#define	VAR_ARRAY 	2
#define VAR_POINTER	3
#define VAR_SIMPLE	4

/*
 * We begin with our linked lists (for separate chaining):
 
 * varType: function, array, pointer, simple variable
 * lexicanType: type of the token, i. e., char, integer, false, true, string ou identifier
 * semanticType: type associated with the type, i. e., KW_WORD, KW_BOOL or KW_BYTE 
 */
typedef struct Entry {
	char *text;
	int *varType;
	int *lexicalType;
	int *semanticType;

	/* for function */	
	int *quant;
	int *parameters; //KW_WORD, KW_BOOL or KW_BYTE
	
	struct Entry *next;
} Entry;

/*
 * Hash table structure.
 */
typedef struct _hashtable {
	int size; /* the size of the table */
	Entry** table; /* the table elements */
} Hashtable;

//****************************************
// FUNCTIONS
//****************************************

Hashtable *create(int size);

unsigned int hash(Hashtable *hashtable, char *str);

Entry *find(Hashtable *hashtable, char *str);

Entry *add(Hashtable *hashtable, char *str, int lexicalType);

void destroy(Hashtable *hashtable);

void print(Hashtable *hashtable);

void fixEntry(char *yytext, int lexicalType);

#endif	/* HASHTABLE_H */
