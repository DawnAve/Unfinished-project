#ifndef CR_H
#define CR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct CR_TUPLE *CR_TUPLELIST;
struct CR_TUPLE {
    char course[10];
    char room[25];
    CR_TUPLELIST next;
};

extern const int CR_HASHTABLE_SIZE;
typedef CR_TUPLELIST CR_HASHTABLE[11];
typedef struct CR_TUPLE CR_TUPLE;
CR_TUPLE* new_CR_TUPLE(char* course, char* room);
void CR_TUPLE_print(struct CR_TUPLE* table);
int h_CR_course(CR_TUPLE* t);
void CR_insert(CR_TUPLE* t, CR_HASHTABLE R);
void CR_lookup(CR_TUPLE* X, CR_HASHTABLE R);
void CR_delete(CR_TUPLE* X, CR_HASHTABLE R);
void CR_HASHTABLE_init(CR_HASHTABLE R);
void CR_HASHTABLE_print(CR_HASHTABLE table);
void CR_setup(CR_HASHTABLE R);

#endif /* CR_H */
