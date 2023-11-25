#ifndef CDH_H
#define CDH_H

typedef struct CDH_TUPLE *CDH_TUPLELIST;
struct CDH_TUPLE {
    int hour;
    char course[10];
    char day[2];
    CDH_TUPLELIST next;
};

extern const int CDH_HASHTABLE_SIZE;
typedef CDH_TUPLELIST CDH_HASHTABLE[11];
typedef struct CDH_TUPLE CDH_TUPLE; 
CDH_TUPLE* new_CDH_TUPLE(char* course, char* day, int hour);
void CDH_TUPLE_print(struct CDH_TUPLE* table);
int h_CDH_course(CDH_TUPLE* t);
void CDH_insert(CDH_TUPLE* t, CDH_HASHTABLE R);
void CDH_lookup(CDH_TUPLE* X, CDH_HASHTABLE R);
void CDH_delete(CDH_TUPLE* X, CDH_HASHTABLE R);
void CDH_HASHTABLE_init(CDH_HASHTABLE R);
void CDH_HASHTABLE_print(CDH_HASHTABLE table);
void CDH_setup(CDH_HASHTABLE R);

#endif
