#ifndef SNAP_H
#define SNAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct SNAP_TUPLE *SNAP_TUPLELIST;
struct SNAP_TUPLE {
    int studentId;
    char name[30];
    char address[50];
    char phone[9];
    SNAP_TUPLELIST next;
};
extern const int SNAP_HASHTABLE_SIZE;
typedef SNAP_TUPLELIST SNAP_HASHTABLE[11];
typedef struct SNAP_TUPLE SNAP_TUPLE;
SNAP_TUPLE* new_SNAP_TUPLE(int studentId, char* name, char* address, char* phone);
void SNAP_TUPLE_print(struct SNAP_TUPLE* table);
int h_SNAP_studentId(SNAP_TUPLE* t);
void SNAP_insert(SNAP_TUPLE* t, SNAP_HASHTABLE R);
void SNAP_lookup(SNAP_TUPLE* X, SNAP_HASHTABLE R);
void SNAP_delete(SNAP_TUPLE* X, SNAP_HASHTABLE R);
void SNAP_HASHTABLE_init(SNAP_HASHTABLE R);
void SNAP_HASHTABLE_print(SNAP_HASHTABLE table);
void SNAP_setup(SNAP_HASHTABLE R);

#endif /* SNAP_H */
