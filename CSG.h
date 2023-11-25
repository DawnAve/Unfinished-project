#ifndef CSG_H
#define CSG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct CSG_TUPLE *CSG_TUPLELIST;
struct CSG_TUPLE {
    int studentId;
    char course[10];
    char grade[3];
    CSG_TUPLELIST next;
};

extern const int CSG_HASHTABLE_SIZE;
typedef CSG_TUPLELIST CSG_HASHTABLE[11];
typedef struct CSG_TUPLE CSG_TUPLE;
CSG_TUPLE* new_CSG_TUPLE(char* course, int studentId, char* grade);
void CSG_TUPLE_print(struct CSG_TUPLE* table);
int h_CSG_studentId(CSG_TUPLE* t);
void CSG_insert(CSG_TUPLE* t, CSG_HASHTABLE R);
void CSG_lookup(CSG_TUPLE* X, CSG_HASHTABLE R);
void CSG_delete(CSG_TUPLE* X, CSG_HASHTABLE R);
void CSG_HASHTABLE_init(CSG_HASHTABLE R);
void CSG_HASHTABLE_print(CSG_HASHTABLE table);
void CSG_setup(CSG_HASHTABLE R);

#endif /* CSG_H */
