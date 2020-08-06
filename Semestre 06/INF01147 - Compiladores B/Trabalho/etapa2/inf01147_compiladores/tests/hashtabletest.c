/*
 * File:   hashtabletest.c
 * Author: fkrahe
 *
 * Created on Mar 17, 2013, 1:34:07 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "hashtable.h"

typedef enum
{
    INT, FLOAT, BOOL, CHAR
} Type;

/*
 * CUnit Test Suite
 */
int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void testCreate()
{
    Hashtable* hashtable = create(3);

    if (hashtable->size == 3) {
        CU_ASSERT(CU_PASS("Table size checks"));
    }
    else {
        CU_ASSERT(CU_FAIL("Wrong table size"));
    }

    destroy(hashtable);
}

void testAdd()
{
    Hashtable* hashtable = create(3);

    char* str1 = "lala";
    int type1 = INT;

    Entry *result = add(hashtable, str1, type1);
    if (result != NULL) {
        CU_ASSERT(CU_PASS("String inserted"));
    }
    else {
        CU_ASSERT(CU_FAIL("Could not insert"));
    }

    destroy(hashtable);
}

void testFind()
{
    Hashtable* hashtable = create(3);

    char* str1 = "lala";
    int type1 = INT;

    // insert and retrieve
    if (add(hashtable, str1, type1) == NULL) {
        CU_ASSERT(CU_FAIL("Could not insert!"));
    }
    else {
        Entry* entry = find(hashtable, str1);

        if (entry != NULL) {
            if (strcmp(entry->text, str1) != 0) {
                CU_ASSERT(CU_FAIL("String was not the same!"));
            }
            else {
                if (*(entry->type) != type1) {
                    CU_ASSERT(CU_FAIL("Type was not the same!"));
                }
                CU_ASSERT(CU_PASS("Info was the same!"));
            }
        }
        else {
            CU_ASSERT(CU_FAIL("Couldn't find the Entry!"));
        }
    }

    destroy(hashtable);
}

void testCollision()
{
    Hashtable* hashtable = create(3);

    char* str1 = "lala";
    int type1 = INT;

    char* str2 = "lala";
    int type2 = FLOAT;

    // insert and retrieve
    Entry *entry1 = add(hashtable, str1, type1);
    Entry *entry2 = add(hashtable, str2, type2);
    if (entry1 == NULL) {
        CU_ASSERT(CU_FAIL("Could not insert 1!"));
    }
    else {
        if (entry2 == NULL) {
            CU_ASSERT(CU_FAIL("Could not insert 2!"));
        }
        else {
            CU_ASSERT_TRUE(entry1 == entry2);
        }
    }

    destroy(hashtable);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("HASHTABLE TEST", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testCreate", testCreate)) ||
        (NULL == CU_add_test(pSuite, "testAdd", testAdd)) ||
        (NULL == CU_add_test(pSuite, "testFind", testFind)) ||
        (NULL == CU_add_test(pSuite, "testCollision", testCollision))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
