#
# File: Makefile
# Creator: George Ferguson
# Created: Thu Jun 30 11:00:49 2016
#
# Sample Makefile distributed with CSC173 Project 1 code bundle
#
# This Makefile builds the test programs for the data structures
# distributed with the bundle, and show how you might use it to
# build YOUR program for the project.
#

PROG = proj4

CFLAGS = -std=c99 -pedantic -Wall -Werror

SRCS =  CP.c CDH.c SNAP.c CSG.c CR.c main.c
OBJS = ${SRCS:%.c=%.o}

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

