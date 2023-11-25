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
#include "SNAP.h"

SNAP_TUPLE*
new_SNAP_TUPLE(int studentId, char* name, char* address, char* phone) {
    SNAP_TUPLE* this = (SNAP_TUPLE*)malloc(sizeof(SNAP_TUPLE));
    if (this != NULL) {
        this->studentId = studentId;
        strcpy(this->name, name);
        strcpy(this->address, address);
        strcpy(this->phone, phone);
        this->next = NULL;
    }
    return this;
}
//const int SNAP_HASHTABLE_SIZE = 11;


/**
 * Print this given SNAP tuple to stdout.
 */
void
SNAP_TUPLE_print(struct SNAP_TUPLE* this) {
     printf("<%d,\"%s\",\"%s\",\"%s\"> ", this->studentId, this->name, this->address, this->phone);
}

/**
 * Hash the given SNAP tuple using the studentId attribute and return
 * the index of its bucket in the SNAP hashtable.
 */
int
h_SNAP_studentId(SNAP_TUPLE* t) {
    return t->studentId % 11;
}

/**
 * FOCS p. 418: ``To insert a tuple t, we examine the bucket to check that
 * t is not already there, and we create a new cell on the bucket’s list
 * for t if it is not. [...] An insert operation always specifies the
 * inserted tuple completely.''
 */
void
SNAP_insert(SNAP_TUPLE* t, SNAP_HASHTABLE R) {
    int i = h_SNAP_studentId(t);
    SNAP_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->studentId == t->studentId) {
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
 * You could also gather them into a list, or into a SNAP_HASHTABLE, or ...
 */
void
SNAP_lookup(SNAP_TUPLE* X, SNAP_HASHTABLE R) {
    bool check = false;
    int i = h_SNAP_studentId(X);
    if (i>=0) {
        // lookup tuples matching X in bucket i of R
        SNAP_TUPLE* p = R[i];
        while (p != NULL) {
            if (p->studentId == X->studentId) {
                SNAP_TUPLE_print(p);
                check = true;
            }
            p = p->next;
        }
    
    } else {
        for (int j = 0; j < 11; j++) {
            // lookup tuples matching X in bucket j of R
            SNAP_TUPLE* p = R[j];
            while (p != NULL) { 
                if ((strcmp(X->name, "") == 0 || strcmp(X->name, p->name) == 0) &&
                    (strcmp(X->address, "") == 0 || strcmp(X->address, p->address) == 0) &&
                    (strcmp(X->phone, "") == 0 || strcmp(X->phone, p->phone) == 0)) {
                    SNAP_TUPLE_print(p);
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
SNAP_delete(SNAP_TUPLE* X, SNAP_HASHTABLE R) {
    if (X->studentId >= 0) {
        int i = h_SNAP_studentId(X);
        // delete tuples matching X from bucket i of R
        SNAP_TUPLE* p = R[i];
        SNAP_TUPLE* prev = NULL;
        while (p != NULL) {
            if ((X->studentId == p->studentId) &&
                (strcmp(X->name, "") == 0 || strcmp(X->name, p->name) == 0) &&
                (strcmp(X->address, "") == 0 || strcmp(X->address, p->address) == 0) &&
                (strcmp(X->phone, "") == 0 || strcmp(X->phone, p->phone) == 0)) {
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
    } else {
        for (int j = 0; j < 11; j++) {
            // delete tuples matching X from bucket j of R
            SNAP_TUPLE* p = R[j];
            SNAP_TUPLE* prev = NULL;
            while (p != NULL) {
                if ((strcmp(X->name, "") == 0 || strcmp(X->name, p->name) == 0) &&
                    (strcmp(X->address, "") == 0 || strcmp(X->address, p->address) == 0) &&
                    (strcmp(X->phone, "") == 0 || strcmp(X->phone, p->phone) == 0)) {
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
 * Initialize the given (empty) SNAP hashtable.
 */
void
SNAP_HASHTABLE_init(SNAP_HASHTABLE R) {
    for (int i=0; i < 11; i++) {
	R[i] = NULL;
    }
}

/**
 * Print the given SNAP hashtable to stdout.
 * Only print buckets that are not empty.
 */
void
SNAP_HASHTABLE_print(SNAP_HASHTABLE table) {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        SNAP_TUPLELIST p = table[i];
        while (p != NULL) {
            count++;
            p = p->next;
        }
    }
    printf("SNAP hashtable with %d relations\n", count);
    for (int i=0; i < 11; i++) {
	    if (table[i] != NULL) {
	        printf("%d: ", i);
	        for (SNAP_TUPLELIST p=table[i]; p != NULL; p=p->next) {
		        SNAP_TUPLE_print(p);
		        if (p->next != NULL) {
		            printf(", ");
		        }
	        }
	        printf("\n");
	    }
    }
}

void SNAP_setup(SNAP_HASHTABLE R){
    SNAP_HASHTABLE_init(R);
    SNAP_TUPLE* snap;
    snap = new_SNAP_TUPLE(66252, "L. Adams", "55 Pear Ave.", "455-9284");
    SNAP_insert(snap, R);
    snap = new_SNAP_TUPLE(01376, "R. Johnson", "88 Apple Dr.", "717-5542");
    SNAP_insert(snap, R);
    snap = new_SNAP_TUPLE(39391, "O. Gonzalez", "62 Durian Blvd.", "687-6203");
    SNAP_insert(snap, R);
    snap = new_SNAP_TUPLE(74533, "C. Johnson", "5 Raisin Ln.", "992-4616");
    SNAP_insert(snap, R);
    snap = new_SNAP_TUPLE(58429, "O. Gonzalez", "78 Rhubarb Ave.", "171-8839");
    SNAP_insert(snap, R);
    snap = new_SNAP_TUPLE(99730, "R. Johnson", "56 Kiwi Blvd.", "903-9855");
    SNAP_insert(snap, R);
}

/*int main(int argc, char** argv) {
    SNAP_HASHTABLE SNAP;
    SNAP_setup(SNAP);
    printf("(b) lookup(⟨*, \"R. Johnson\", *, *⟩, StudentId-Name-Address-Phone)\n");
    SNAP_TUPLE* snap;
    snap = new_SNAP_TUPLE(-1, "R. Johnson", "","");
    SNAP_lookup(snap, SNAP);
}*/
