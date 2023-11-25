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
#include "CDH.h"

CDH_TUPLE*
new_CDH_TUPLE(char* course, char* day, int hour) {
    CDH_TUPLE* this = (CDH_TUPLE*)malloc(sizeof(CDH_TUPLE));
    if (this != NULL) {
        this->hour = hour;
        strcpy(this->course, course);
        strcpy(this->day, day);
        this->next = NULL;
    }
    return this;
}
//const int CDH_HASHTABLE_SIZE = 11;
/**
 * Print this given CDH tuple to stdout.
 */
void
CDH_TUPLE_print(struct CDH_TUPLE* this) {
     printf("<%s,\"%s\",\"%d\">", this->course, this->day, this->hour);
}

/**
 * Hash the given CDH tuple using the course attribute and return
 * the index of its bucket in the CDH hashtable.
 */
int
h_CDH_course(CDH_TUPLE* t) {
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
CDH_insert(CDH_TUPLE* t, CDH_HASHTABLE R) {
    int i = h_CDH_course(t);
    CDH_TUPLE* p = R[i];
    while (p != NULL) {
        if (strcmp(t->course, p->course) == 0 && strcmp(t->day, p->day) == 0) { // Assume that no student can get more than one grade
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
 * You could also gather them into a list, or into a CDH_HASHTABLE, or ...
 */
void
CDH_lookup(CDH_TUPLE* X, CDH_HASHTABLE R) {
    bool check = false;
    int i = h_CDH_course(X);
    if (i>=0) {   //Course provided, only search in one bucket
        // lookup tuples matching X in bucket i of R
        CDH_TUPLE* p = R[i];
        if (strcmp(X->day, "") == 0){   // Only Course provided
            while (p != NULL) {
                if (strcmp(p->course, X->course) == 0) {
                    CDH_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        } else {   // Day and Course Provided, and since one student can only earn one grade, no need to compare grade
            while (p != NULL) {
                if (strcmp(p->day, X->day) == 0 && strcmp(p->course, X->course) == 0) {
                    CDH_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        }
    } else { // Course not provided
        for (int j = 0; j < 11; j++) {
            // lookup tuples matching X in bucket j of R
            CDH_TUPLE* p = R[j];
            while (p != NULL) {
                if ((strcmp(X->day, "") == 0 || strcmp(X->day, p->day) == 0) &&
                    (X->hour == -1 || X->hour == p->hour)) {
                    CDH_TUPLE_print(p);
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
CDH_delete(CDH_TUPLE* X, CDH_HASHTABLE R) {
    if (h_CDH_course(X) >= 0) {  // Course provided
        int i = h_CDH_course(X);
        // delete tuples matching X from bucket i of R
        CDH_TUPLE* p = R[i];
        CDH_TUPLE* prev = NULL;
        while (p != NULL) {
            if ((strcmp(X->course, "") == 0 || strcmp(X->course, p->course) == 0) &&
                (strcmp(X->day, "") == 0 || strcmp(X->day, p->day) == 0)) {
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
            CDH_TUPLE* p = R[j];
            CDH_TUPLE* prev = NULL;
            while (p != NULL) {
                if ((strcmp(X->day, "") == 0 || strcmp(X->day, p->day) == 0) &&
                    (X->hour == -1 || X->hour == p->hour)) {
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
 * Initialize the given (empty) CDH hashtable.
 */
void
CDH_HASHTABLE_init(CDH_HASHTABLE R) {
    for (int i=0; i < 11; i++) {
	R[i] = NULL;
    }
}

/**
 * Print the given CDH hashtable to stdout.
 * Only print buckets that are not empty.
 */
void
CDH_HASHTABLE_print(CDH_HASHTABLE table) {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        CDH_TUPLELIST p = table[i];
        while (p != NULL) {
            count++;
            p = p->next;
        }
    }
    printf("CDH hashtable with %d relations\n", count);
    for (int i=0; i < 11; i++) {
	    if (table[i] != NULL) {
	        printf("%d: ", i);
	        for (CDH_TUPLELIST p=table[i]; p != NULL; p=p->next) {
		        CDH_TUPLE_print(p);
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
void CDH_setup(CDH_HASHTABLE R){
    CDH_HASHTABLE_init(R);
    CDH_TUPLE* cdh;
    cdh = new_CDH_TUPLE("CSC171", "M", 1400);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC171", "W", 1400);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC172", "W", 1640);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC172", "M", 1525);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC173", "M", 1400);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC173", "W", 1400);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC252", "M", 1230);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("CSC252", "W", 1230);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("DSCC201", "R", 900);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("DSCC201", "R", 900);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("DSCC202", "T", 1650);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("DSCC202", "R", 1650);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("DSCC265", "T", 1400);
    CDH_insert(cdh, R);
    cdh = new_CDH_TUPLE("DSCC265", "R", 1400);
    CDH_insert(cdh, R);
    

}

