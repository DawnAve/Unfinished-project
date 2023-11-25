/**
 * focs_ch08.c
 * George Ferguson
 *
 * @see FOCS Ch. 8: The Relational Data Model
 * @see ``C for Java programmers,'' Chapter 8 ``Memory Management,'' p. 51
 * @see Tutorial Lesson 3 ``Objects''
 * @see https://www.cs.rochester.edu/u/ferguson/csc/c/c-for-java-programmers.pdf
 * @see https://www.cs.rochester.edu/u/ferguson/csc/c/tutorial/employee/
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "CSG.h"

CSG_TUPLE*
new_CSG_TUPLE(char* course, int studentId, char* grade) {
    CSG_TUPLE* this = (CSG_TUPLE*)malloc(sizeof(CSG_TUPLE));
    if (this != NULL) {
        this->studentId = studentId;
        strcpy(this->course, course);
        strcpy(this->grade, grade);
        this->next = NULL;
    }
    return this;
}
//const int CSG_HASHTABLE_SIZE = 11;
/**
 * Print this given CSG tuple to stdout.
 */
void
CSG_TUPLE_print(struct CSG_TUPLE* this) {
     printf("<%s,\"%d\",\"%s\">", this->course, this->studentId, this->grade);
}

/**
 * Hash the given CSG tuple using the studentId attribute and return
 * the index of its bucket in the CSG hashtable.
 */
int
h_CSG_studentId(CSG_TUPLE* t) {
    return t->studentId % 11;
}

/**
 * FOCS p. 418: ``To insert a tuple t, we examine the bucket to check that
 * t is not already there, and we create a new cell on the bucket’s list
 * for t if it is not. [...] An insert operation always specifies the
 * inserted tuple completely.''
 */
void
CSG_insert(CSG_TUPLE* t, CSG_HASHTABLE R) {
    int i = h_CSG_studentId(t);
    CSG_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->studentId == t->studentId && strcmp(t->course, p->course) == 0) { // Assume that no student can get more than one grade
            // Found
            return;
        } else {
            p = p->next;
        }
    }
    // Add t to bucket list i (at the front is easiest)
    t->next = R[i];
    R[i] = t;
}

/**
 * FOCS p. 418: ``To lookup tuples according to a specification X, we again
 * find the domain value from X and hash that value to find the proper bucket.
 * We run down the list for that bucket, producing as an answer each tuple on
 * the list that matches the specification X. [...] If the operation does not
 * specify the domain value, we are not so fortunate. [...] In those cases,
 * we must search all the bucket lists for matching tuples and [...] list
 * them.''
 * You could also gather them into a list, or into a CSG_HASHTABLE, or ...
 */
void
CSG_lookup(CSG_TUPLE* X, CSG_HASHTABLE R) {
    bool check = false;
    int i = h_CSG_studentId(X);
    if (i>=0) {   //ID provided, only search in one bucket
        // lookup tuples matching X in bucket i of R
        CSG_TUPLE* p = R[i];
        if (strcmp(X->course, "") == 0){   // Only ID provided
            while (p != NULL) {
                if (p->studentId == X->studentId) {
                    CSG_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        } else {   // ID and Course Provided, and since one student can only earn one grade, no need to compare grade
            while (p != NULL) {
                if (p->studentId == X->studentId && strcmp(p->course, X->course) == 0) {
                    CSG_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        }
    } else { // ID not provided
        for (int j = 0; j < 11; j++) {
            // lookup tuples matching X in bucket j of R
            CSG_TUPLE* p = R[j];
            while (p != NULL) {
                if ((strcmp(X->course, "") == 0 || strcmp(X->course, p->course) == 0) &&
                    (strcmp(X->grade, "") == 0 || strcmp(X->grade, p->grade) == 0)) {
                    CSG_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        }
    }
    if (check == false){
        printf("NONE");
    }
    printf("\n");
    
}

/**
 * FOCS p. 418: ``To delete tuples that match a specification X, we find
 * the domain value from X, hash to find the proper bucket, and run down
 * the list for this bucket, deleting each tuple that matches the
 * specification X.''
 */
void
CSG_delete(CSG_TUPLE* X, CSG_HASHTABLE R) {
    if (h_CSG_studentId(X) >= 0) {  // Student ID provided
        int i = h_CSG_studentId(X);
        // delete tuples matching X from bucket i of R
        CSG_TUPLE* p = R[i];
        CSG_TUPLE* prev = NULL;
        while (p != NULL) {
            if ((X->studentId == p->studentId) &&
                (strcmp(X->course, "") == 0 || strcmp(X->course, p->course) == 0) &&
                (strcmp(X->grade, "") == 0 || strcmp(X->grade, p->grade) == 0)) {
                if (prev == NULL) {
                    R[i] = p->next;
                    p = R[i];
                } else {
                    prev->next = p->next;
                    p = prev->next;
                }
            } else {
                prev = p;
                p = p->next;
            }
        }
    } else {  // ID not provided
        for (int j = 0; j < 11; j++) {
            // delete tuples matching X from bucket j of R
            CSG_TUPLE* p = R[j];
            CSG_TUPLE* prev = NULL;
            while (p != NULL) {
                if ((strcmp(X->course, "") == 0 || strcmp(X->course, p->course) == 0) &&
                    (strcmp(X->grade, "") == 0 || strcmp(X->grade, p->grade) == 0)) {
                    if (prev == NULL) {
                        R[j] = p->next;
                    } else {
                        prev->next = p->next;
                    }
                   
                    if (prev == NULL) {
                        p = R[j];
                    } else {
                        p = prev->next;
                    }
                } else {
                    prev = p;
                    p = p->next;
                }
            }
        }
    }
}

/**
 * Initialize the given (empty) CSG hashtable.
 */
void
CSG_HASHTABLE_init(CSG_HASHTABLE R) {
    for (int i=0; i < 11; i++) {
	R[i] = NULL;
    }
}

/**
 * Print the given CSG hashtable to stdout.
 * Only print buckets that are not empty.
 */
void
CSG_HASHTABLE_print(CSG_HASHTABLE table) {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        CSG_TUPLELIST p = table[i];
        while (p != NULL) {
            count++;
            p = p->next;
        }
    }
    printf("CSG hashtable with %d relations\n", count);
    for (int i=0; i < 11; i++) {
	    if (table[i] != NULL) {
	        printf("%d: ", i);
	        for (CSG_TUPLELIST p=table[i]; p != NULL; p=p->next) {
		        CSG_TUPLE_print(p);
		        if (p->next != NULL) {
		            printf(", ");
		        }
	        }
	        printf("\n");
	    }
    }
}
void CSG_setup(CSG_HASHTABLE R){
    
    CSG_HASHTABLE_init(R);
    CSG_TUPLE* csg;
    csg = new_CSG_TUPLE("CSC171", 66252, "A");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("CSC171", 58429, "B");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("MATH150", 39391, "A");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("DSCC201", 66252, "C");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("DSCC201", 01376, "B+");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("CSC172", 99730, "A");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("MATH150", 58429, "C+");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("CSC173", 74533, "B+");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("CSC173", 99730, "A");
    CSG_insert(csg, R);
    csg = new_CSG_TUPLE("DSCC201", 99730, "C");
    CSG_insert(csg, R);
    
}
