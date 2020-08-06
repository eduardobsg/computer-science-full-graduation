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

#define TABLE_SIZE 97

/*
 * We begin with our linked lists (for separate chaining):
 */
typedef struct Entry {
    char *text;
    int *type;
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

Entry *add(Hashtable *hashtable, char *str, int type);

void destroy(Hashtable *hashtable);

void print(Hashtable *hashtable);

void fixEntry(char *yytext, int type);

#endif	/* HASHTABLE_H */

