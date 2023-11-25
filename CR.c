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
#include "CR.h"

CR_TUPLE*
new_CR_TUPLE(char* course, char* room) {
    CR_TUPLE* this = (CR_TUPLE*)malloc(sizeof(CR_TUPLE));
    if (this != NULL) {
        
        strcpy(this->course, course);
        strcpy(this->room, room);
        this->next = NULL;
    }
    return this;
}
//const int CR_HASHTABLE_SIZE = 11;
/**
 * Print this given CR tuple to stdout.
 */
void
CR_TUPLE_print(struct CR_TUPLE* this) {
     printf("<%s,\"%s\">", this->course, this->room);
}

/**
 * Hash the given CR tuple using the course attribute and return
 * the index of its bucket in the CR hashtable.
 */
int
h_CR_course(CR_TUPLE* t) {
    if (strcmp("", t->course) ==0){
        return -1;
    }
    char* course = t->course;
	int k = 0;
	for (int i = 0; i < strlen(course); i++) {
		k += (int) course [i];
	}
	int key = k % 11;
	return key;
}

/**
 * FOCS p. 418: ``To insert a tuple t, we examine the bucket to check that
 * t is not already there, and we create a new cell on the bucket’s list
 * for t if it is not. [...] An insert operation always specifies the
 * inserted tuple completely.''
 */
void
CR_insert(CR_TUPLE* t, CR_HASHTABLE R) {
    int i = h_CR_course(t);
    CR_TUPLE* p = R[i];
    while (p != NULL) {
        if (strcmp(p->course, t->course) == 0) {
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
 * You could also gather them into a list, or into a CR_HASHTABLE, or ...
 */
void
CR_lookup(CR_TUPLE* X, CR_HASHTABLE R) {
    bool check = false;
    int i = h_CR_course(X);
    if (i>=0) {   //course provided
        // lookup tuples matching X in bucket i of R
        CR_TUPLE* p = R[i];
        if (strcmp(X->room, "") == 0){   // Only course provided
            while (p != NULL) {
                
                if (strcmp(p->course, X->course)==0) {
                    CR_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        } else {   // room and Course Provided
            while (p != NULL) {
                if (strcmp(p->course, X->course) == 0 && strcmp(p->room, X->room) == 0) {
                    CR_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
                
            }
        }
    } else { //nothing is provided or room is provided
        for (int j = 0; j < 11; j++) {
            // lookup tuples matching X in bucket j of R
            CR_TUPLE* p = R[j];
            while (p != NULL) {
                if (strcmp(X->room, "") == 0 || strcmp(X->room, p->room) == 0) {
                    CR_TUPLE_print(p);
                }
                p = p->next;
                check = true;
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
CR_delete(CR_TUPLE* X, CR_HASHTABLE R) {
    int i = h_CR_course(X);
    if (i >= 0) {
        // delete tuples matching X from bucket i of R
        CR_TUPLE* p = R[i];
        CR_TUPLE* prev = NULL;
        while (p != NULL) {
            if ((strcmp(X->course, "") == 0 || strcmp(X->course, p->course) == 0) &&
                (strcmp(X->room, "") == 0 || strcmp(X->room, p->room) == 0)) {
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
            CR_TUPLE* p = R[j];
            CR_TUPLE* prev = NULL;
            while (p != NULL) {
                if (strcmp(X->room, "") == 0 || strcmp(X->room, p->room) == 0) {
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
 * Initialize the given (empty) CR hashtable.
 */
void
CR_HASHTABLE_init(CR_HASHTABLE R) {
    for (int i=0; i < 11; i++) {
	R[i] = NULL;
    }
}

/**
 * Print the given CR hashtable to stdout.
 * Only print buckets that are not empty.
 */
void
CR_HASHTABLE_print(CR_HASHTABLE table) {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        CR_TUPLELIST p = table[i];
        while (p != NULL) {
            count++;
            p = p->next;
        }
    }
    printf("CR hashtable with %d relations\n", count);
    for (int i=0; i < 11; i++) {
	    if (table[i] != NULL) {
	        printf("%d: ", i);
	        for (CR_TUPLELIST p=table[i]; p != NULL; p=p->next) {
		        CR_TUPLE_print(p);
		        if (p->next != NULL) {
		            printf(", ");
		        }
	        }
	        printf("\n");
	    }
    }
}

/*
 * Main function
 */
void CR_setup(CR_HASHTABLE R){
    CR_HASHTABLE_init(R);
    CR_TUPLE* cr;
    cr = new_CR_TUPLE("CSC171", "Hutchison Hall 141");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("CSC172", "Hutchison Hall 141");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("CSC173", "Wegmans 1400");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("CSC252", "Wegmans 1400");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("CSC254", "Wegmans 1400");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("DSCC201", "Bausch & Lomb 109");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("DSCC202", "Dewey 2162");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("DSCC265", "Wegmans 1400");
    CR_insert(cr, R);
    cr = new_CR_TUPLE("MATH150", "Harkness 115");
    CR_insert(cr, R);
    
}
