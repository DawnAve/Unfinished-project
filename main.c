#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "CSG.h"
#include "CR.h"
#include "SNAP.h"
#include "CP.h"
#include "CDH.h"

void part1(void){
    printf("initialize\n");
    SNAP_HASHTABLE SNAP;
    CSG_HASHTABLE CSG;
    CR_HASHTABLE CR;
    CP_HASHTABLE CP;
    CDH_HASHTABLE CDH;

    printf("setup\n");
    SNAP_setup(SNAP);
    printf("1\n");
    CSG_setup(CSG);
    printf("1\n");
    CP_setup(CP);
    printf("1\n");
    CR_setup(CR);
    printf("1\n");
    CDH_setup(CDH);
    printf("1\n");

    printf("print\n");
    SNAP_HASHTABLE_print(SNAP);
    CSG_HASHTABLE_print(CSG);
    CP_HASHTABLE_print(CP);
    CR_HASHTABLE_print(CR);
    CDH_HASHTABLE_print(CDH);

    printf("(a) lookup(⟨\"DSCC201\", 01376, \"B+\"⟩, Course-StudentId-Grade)\n");
    printf("A\n");
    CSG_TUPLE* csg;
    csg = new_CSG_TUPLE("DSCC201", 01376, "B+");
    CSG_lookup(csg, CSG);
    

    printf("(b) lookup(⟨*, \"R. Johnson\", *, *⟩, StudentId-Name-Address-Phone)\n");
    printf("B\n");
    SNAP_TUPLE* snap;
    snap = new_SNAP_TUPLE(-1, "R. Johnson", "","");
    SNAP_lookup(snap, SNAP);

    printf("(c) lookup(⟨\"CSC252\", \"CSC173\"⟩, Course-Prerequisite)\n");
    CP_TUPLE* cp;
    cp = new_CP_TUPLE("CSC252", "CSC173");
    CP_lookup(cp, CP);

    printf("(d) delete(⟨\"DSCC201\", \"T\", \"900\"⟩, Course-Day-Hour)\n");
    CDH_TUPLE* cdh;
    cdh = new_CDH_TUPLE("DSCC201", "T", 900);
    CDH_delete(cdh, CDH);
    CDH_HASHTABLE_print(CDH);

    printf("(e) delete(⟨\"CSC171\", \"T\", *⟩, Course-Day-Hour)\n");
    cdh = new_CDH_TUPLE("CSC171", "T", -1);
    CDH_delete(cdh, CDH);
    CDH_HASHTABLE_print(CDH);


    printf("(f) delete(⟨\"CSC173\", *, *⟩, Course-Day-Hour)\n");
    cdh = new_CDH_TUPLE("CSC173", "", -1);
    CDH_delete(cdh, CDH);
    CDH_HASHTABLE_print(CDH);

    printf("(g) insert(⟨\"CSC252\", 74533, \"A-\"⟩, Course-StudentId-Grade)\n");

    csg = new_CSG_TUPLE("CSC252", 74533, "A-");
    CSG_insert(csg, CSG);
    CSG_HASHTABLE_print(CSG);

    printf("(h) insert(⟨\"DSCC201\", 66252, \"C\"⟩, Course-StudentId-Grade)\n");

    csg = new_CSG_TUPLE("DSCC201", 66252, "C");
    CSG_insert(csg, CSG);
    CSG_HASHTABLE_print(CSG);
}
int main(int argc, char** argv) {
    part1();
}
