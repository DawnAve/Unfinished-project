
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "CP.h"

CP_TUPLE*
new_CP_TUPLE(char* course, char* prerequisite) {
    CP_TUPLE* this = (CP_TUPLE*)malloc(sizeof(CP_TUPLE));
    if (this != NULL) {
        strcpy(this->course, course);
        strcpy(this->prerequisite, prerequisite);
        this->next = NULL;
    }
    return this;
}
//const int CP_HASHTABLE_SIZE = 11;

void
CP_TUPLE_print(struct CP_TUPLE* this) {
     printf("<%s,\"%s\">", this->course, this->prerequisite);
}


int
h_CP_course(CP_TUPLE* t) {
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


void
CP_insert(CP_TUPLE* t, CP_HASHTABLE R) {
    int i = h_CP_course(t);
    CP_TUPLE* p = R[i];
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


void
CP_lookup(CP_TUPLE* X, CP_HASHTABLE R) {
    bool check = false;
    int i = h_CP_course(X);
    if (i>=0) {   //course provided
        // lookup tuples matching X in bucket i of R
        CP_TUPLE* p = R[i];
        if (strcmp(X->prerequisite, "") == 0){   // Only course provided
            while (p != NULL) {
                
                if (strcmp(p->course, X->course)==0) {
                    CP_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
            }
        } else {   // prerequisite and Course Provided
            while (p != NULL) {
                if (strcmp(p->course, X->course) == 0 && strcmp(p->prerequisite, X->prerequisite) == 0) {
                    CP_TUPLE_print(p);
                    check = true;
                }
                p = p->next;
                
            }
        }
    } else { //nothing is provided or prerequisite is provided
        for (int j = 0; j < 11; j++) {
            // lookup tuples matching X in bucket j of R
            CP_TUPLE* p = R[j];
            while (p != NULL) {
                if (strcmp(X->prerequisite, "") == 0 || strcmp(X->prerequisite, p->prerequisite) == 0) {
                    CP_TUPLE_print(p);
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


void
CP_delete(CP_TUPLE* X, CP_HASHTABLE R) {
    int i = h_CP_course(X);
    if (i >= 0) {
        // delete tuples matching X from bucket i of R
        CP_TUPLE* p = R[i];
        CP_TUPLE* prev = NULL;
        while (p != NULL) {
            if ((strcmp(X->course, "") == 0 || strcmp(X->course, p->course) == 0) &&
                (strcmp(X->prerequisite, "") == 0 || strcmp(X->prerequisite, p->prerequisite) == 0)) {
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
            CP_TUPLE* p = R[j];
            CP_TUPLE* prev = NULL;
            while (p != NULL) {
                if (strcmp(X->prerequisite, "") == 0 || strcmp(X->prerequisite, p->prerequisite) == 0) {
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


void
CP_HASHTABLE_init(CP_HASHTABLE R) {
    for (int i=0; i < 11; i++) {
	R[i] = NULL;
    }
}

void
CP_HASHTABLE_print(CP_HASHTABLE table) {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        CP_TUPLELIST p = table[i];
        while (p != NULL) {
            count++;
            p = p->next;
        }
    }
    printf("CP hashtable with %d relations\n", count);
    for (int i=0; i < 11; i++) {
	    if (table[i] != NULL) {
	        printf("%d: ", i);
	        for (CP_TUPLELIST p=table[i]; p != NULL; p=p->next) {
		        CP_TUPLE_print(p);
		        if (p->next != NULL) {
		            printf(", ");
		        }
	        }
	        printf("\n");
	    }
    }
}


void CP_setup(CP_HASHTABLE R){
    CP_HASHTABLE_init(R);
    CP_TUPLE* cp;
    cp = new_CP_TUPLE("CSC172", "CSC171");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("CSC172", "MATH150");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("CSC173", "CSC172");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("CSC252", "CSC172");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("CSC254", "CSC252");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("DSCC201", "CSC171");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("DSCC202", "DSCC201");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("DSCC265", "CSC262");
    CP_insert(cp, R);
    cp = new_CP_TUPLE("DSCC265", "CSC171");
    CP_insert(cp, R);
}

/*int main(int argc, char** argv) {{
    CP_HASHTABLE CP;
    CP_setup(CP);
    printf("(c) lookup(⟨\"CSC252\", \"CSC173\"⟩, Course-Prerequisite)\n");
    CP_TUPLE* cp;
    cp = new_CP_TUPLE("CSC252", "CSC173");
    CP_lookup(cp, CP);
}}*/

