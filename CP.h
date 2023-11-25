#ifndef CP_H
#define CP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct CP_TUPLE *CP_TUPLELIST;
typedef struct CP_TUPLE CP_TUPLE;
struct CP_TUPLE {
    char course[10];
    char prerequisite[10];
    CP_TUPLELIST next;
};

extern const int CP_HASHTABLE_SIZE;
typedef CP_TUPLELIST CP_HASHTABLE[11];

CP_TUPLE* new_CP_TUPLE(char* course, char* prerequisite);
void CP_TUPLE_print(struct CP_TUPLE* table);
int h_CP_course(CP_TUPLE* t);
void CP_insert(CP_TUPLE* t, CP_HASHTABLE R);
void CP_lookup(CP_TUPLE* X, CP_HASHTABLE R);
void CP_delete(CP_TUPLE* X, CP_HASHTABLE R);
void CP_HASHTABLE_init(CP_HASHTABLE R);
void CP_HASHTABLE_print(CP_HASHTABLE table);
void CP_setup(CP_HASHTABLE R);

#endif // CP_H
