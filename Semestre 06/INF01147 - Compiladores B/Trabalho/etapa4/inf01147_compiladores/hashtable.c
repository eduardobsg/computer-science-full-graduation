/*
 * Started with "Very Simple implementation", found in
 * http://www.sparknotes.com/cs/searching/hashtables/section3.rhtml
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

// Why did we declare the table as list_t **table? 
// We don't know up front how big we want the table to be. 
// Therefore, we need to make the table a dynamic array. 
// Remember that an array is just a big block of memory and 
// is basically synonymous with a pointer 
// (see the SparkNotes on arrays and pointers. 
// What we have is a pointer to a pointer to a linked list; 
// thus list_t **table.

/*
 * Creation
 */
Hashtable *create(int size)
{
    Hashtable *new_table;

    if (size < 1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((new_table = malloc(sizeof (Hashtable))) == NULL) {
        return NULL;
    }

    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = malloc(sizeof (Entry *) * size)) == NULL) {
        return NULL;
    }

    /* Initialize the elements of the table */
    int i;
    for (i = 0; i < size; i++) new_table->table[i] = NULL;

    /* Set the table's size */
    new_table->size = size;

    return new_table;
}

/*
 * Our hash function. We'll go with a relatively simple one.
 */
unsigned int hash(Hashtable *hashtable, char *str)
{
    unsigned int hashval;

    /* we start our hash out at 0 */
    hashval = 0;

    /* for each character, we multiply the old hash by 31 and add the current
     * character.  Remember that shifting a number left is equivalent to 
     * multiplying it by 2 raised to the number of places shifted.  So we 
     * are in effect multiplying hashval by 32 and then subtracting hashval.  
     * Why do we do this?  Because shifting and subtraction are much more 
     * efficient operations than multiplication.
     */
    for (; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;

    /* we then return the hash value mod the hashtable size so that it will
     * fit into the necessary range
     */
    return hashval % hashtable->size;
}

/*
 * String (key) lookup. Doing a string lookup is as simple as hashing the string, 
 * going to the correct index in the array, and then doing a linear search 
 * on the linked list that resides there.
 */
Entry* find(Hashtable *hashtable, char *str)
{
    Entry *list;
    unsigned int hashval = hash(hashtable, str);

    /* Go to the correct list based on the hash value and see if str is
     * in the list. If it is, return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL.
     */
    for (list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, list->text) == 0) return list;
    }
    return NULL;
}

/*
 * Inserting a string. Inserting a string is almost the same as looking up 
 * a string. Hash the string. Go to the correct place in the array. 
 * Insert the new string at the beginning.
 * 
 * Return NULL if fails
 * Return pointer if success or item already there
 */
Entry* add(Hashtable *hashtable, char *str, int lexicalType)
{
    Entry *new_list;
    Entry *current_list;
    unsigned int hashval = hash(hashtable, str);

    /* Attempt to allocate memory for list */
    if ((new_list = malloc(sizeof (Entry))) == NULL) return NULL;

    /* Does item already exist? */
    current_list = find(hashtable, str);
    /*
     * item already exists, don't insert it again. 
     * Return the pointer;
     */
    if (current_list != NULL) {
        return current_list;
    }

    /* Removes " or ' if it is a string or char */
    fixEntry(str, lexicalType);

    /* Insert into list */
    new_list->text = strdup(str);

    new_list->varType = malloc(sizeof (int));
    *(new_list->varType) = -1;

    new_list->lexicalType = malloc(sizeof (int));
    *(new_list->lexicalType) = lexicalType;

    new_list->semanticType = malloc(sizeof (int));
    *(new_list->semanticType) = -1;

    new_list->quant = malloc(sizeof (int));
    *(new_list->quant) = -1;

    new_list->parameters = NULL;

    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;

    //fprintf(stderr, "\tadd: inserted %s \n", str);
    return new_list;
}

/*
 * Deleting a table. Freeing up the memory you use is a very good habit, 
 * so we write a function to clear out the hashtable.
 * 
 * Whatever you passed to the void pointer in an "Entry will be freed here.
 * Don't try to use after calling destroy.
 */
void destroy(Hashtable *hashtable)
{
    int i;
    Entry *list, *temp;

    if (hashtable == NULL) return;

    /* Free the memory for every item in the table, including the 
     * strings themselves.
     */
    for (i = 0; i < hashtable->size; i++) {
        list = hashtable->table[i];
        while (list != NULL) {
            temp = list;
            list = list->next;
            free(temp->text);
            free(temp->lexicalType);
            free(temp->semanticType);
            free(temp);
        }
    }

    /* Free the table itself */
    free(hashtable->table);
    free(hashtable);
}

/*
 * Do not test this function with CUnit. 
 * Don't even call it.
 * It apparently messes up with the tests!
 */
void print(Hashtable *hashtable)
{
    //return;//FIXME
    fprintf(stderr, "\n//*** BEGIN HASH TABLE **********\n");
    Entry *entry;
    int i;
    for (i = 0; i < hashtable->size; i++) {
        entry = hashtable->table[i];
        while (entry != NULL) {
            fprintf(stderr, "{%03i} Entry[%s, L%i, S%i]\n",
                    i,
                    entry->text,
                    *(entry->lexicalType),
                    *(entry->semanticType));
            entry = entry->next;
        }
    }
    fprintf(stderr, "//*** END HASH TABLE ************\n");
}

/*
 * Given an char or string entry, it fixes
 * the format of it to later add in the hashtable.
 */
void fixEntry(char *str, int lexicalType)
{

    if (lexicalType == 285) { // LIT_CHAR
        str[0] = str[1];
        str[1] = '\0';
        return;
    }
    else if (lexicalType == 286) { // LIT_STRING
        int size = strlen(str);
        int i;
        for (i = 0; i < size; i++) {
            str[i] = str[i + 1];
        }
        str[i - 2] = '\0';
        return;
    }
}
