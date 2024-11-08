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

/**
 * @see FOCS Fig. 8.3, p. 415
 * ``Types for a hash table as primary index structure''
 * I have replaced ``TUPLE'' with ``SNAP_TUPLE'' and ``HASHTABLE''
 * with ``SNAP_HASHTABLE'' since the tuples and the hashtable are
 * specific to the relation being stored.
 */
typedef struct SNAP_TUPLE *SNAP_TUPLELIST;
struct SNAP_TUPLE {
    int studentId;	// See note [1]
    char name[30];
    char address[50];
    char phone[9];	// See note [2]
    SNAP_TUPLELIST next;
};
#define SNAP_HASHTABLE_SIZE 11
typedef SNAP_TUPLELIST SNAP_HASHTABLE[SNAP_HASHTABLE_SIZE]; // See note [3]

typedef struct SNAP_TUPLE SNAP_TUPLE; // See note [4]

/*
 * Notes:
 * [1] FOCS uses capitalized names for the attributes. That's fine, but
 *     I think it's clearer to name them like instance variables (fields)
 *     in Java.
 * [2] The ``Phone'' attribute has size 8 in FOCS. That is enough to store
 *     a phone number like ``555-1212''. But if you want to be able to print
 *     that attribute easily, or use functions like strcpy with it, you need
 *     room for the NUL at the end.
 * [3] The HASHTABLE in FOCS Fig. 8.3 has 1009 buckets. That is overkill
 *     for our tiny databases. You do probably want to use a prime number,
 *     although FOCS does not explain why.
 * [4] Allows us to refer to SNAP tuples as ``SNAP_TUPLE'' rather than
 *     having to write ``struct SNAP_TUPLE'' all the time. See the C
 *     for Java Programmers Tutorial, Lesson 3.
 */

/**
 * Allocate a new SNAP tuple, initialize it with the given values,
 * and return the reference (pointer) to it.
 */
SNAP_TUPLE*
new_SNAP_TUPLE(int studentId, char* name, char* address, char* phone) {
    SNAP_TUPLE* this = ...;
    ...;
    return this;
}

/**
 * Print this given SNAP tuple to stdout.
 */
void
SNAP_TUPLE_print(struct SNAP_TUPLE* this) {
    printf(...);
}

/**
 * Hash the given SNAP tuple using the studentId attribute and return
 * the index of its bucket in the SNAP hashtable.
 */
int
h_SNAP_studentId(SNAP_TUPLE* t) {
    return t->studentId ...;
}

/**
 * FOCS p. 418: ``To insert a tuple t, we examine the bucket to check that
 * t is not already there, and we create a new cell on the bucket’s list
 * for t if it is not. [...] An insert operation always specifies the
 * inserted tuple completely.''
 */
void
SNAP_insert(SNAP_TUPLE* t, SNAP_HASHTABLE R) {
    int i = ...(t);
    SNAP_TUPLE* p = ...[i];
    while (p != NULL) {
	if (...tuple p matches tuple t...) {
	    // Found
	    return;
	} else {
	    p = p->next;
	}
    }
    // Add t to bucket list i (at the front is easiest)
    ...;
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
    if (...X is hashable...) {
	int i = ...(X);
	...lookup tuples matching X in bucket i of R...;
    } else {
	for (int i=0; i < SNAP_HASHTABLE_SIZE; i++) {
	    ...lookup tuples matching X in bucket i of R...;
	}
    }
}

/**
 * FOCS p. 418: ``To delete tuples that match a specification X, we find
 * the domain value from X, hash to find the proper bucket, and run down
 * the list for this bucket, deleting each tuple that matches the
 * specification X.''
 */
void
SNAP_delete(SNAP_TUPLE* X, SNAP_HASHTABLE R) {
    if (...X is hashable...) {
	int i = ...(X);
	...delete tuples matching X from bucket i of R...;
    } else {
	for (int i=0; i < SNAP_HASHTABLE_SIZE; i++) {
	    ...delete tuples matching X from bucket i of R...;
	}
    }
}

/**
 * Initialize the given (empty) SNAP hashtable.
 */
void
SNAP_HASHTABLE_init(SNAP_HASHTABLE R) {
    for (int i=0; i < SNAP_HASHTABLE_SIZE; i++) {
	R[i] = NULL;
    }
}

/**
 * Print the given SNAP hashtable to stdout.
 * Only print buckets that are not empty.
 */
void
SNAP_HASHTABLE_print(SNAP_HASHTABLE table) {
    printf("SNAP hashtable with %d buckets\n", SNAP_HASHTABLE_SIZE);
    for (int i=0; i < SNAP_HASHTABLE_SIZE; i++) {
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

/*
 * Main function
 */
int
main(int argc, char** argv) {
    SNAP_HASHTABLE R;
    SNAP_HASHTABLE_init(R);
    SNAP_HASHTABLE_print(R);

    SNAP_TUPLE* t;
    t = new_SNAP_TUPLE(12345, "C. Brown", "12 Apple St.", "555-1234");
    SNAP_insert(t, R);
    t = new_SNAP_TUPLE(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
    SNAP_insert(t, R);
    t = new_SNAP_TUPLE(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
    SNAP_insert(t, R);
    SNAP_HASHTABLE_print(R);

    t = new_SNAP_TUPLE(12345, "", "", "");
    SNAP_lookup(t, R);
    t = new_SNAP_TUPLE(-1, "L. Van Pelt", "", "");
    SNAP_lookup(t, R);
    t = new_SNAP_TUPLE(-1, "", "", "555-9999");
    SNAP_lookup(t, R);

    t = new_SNAP_TUPLE(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
    SNAP_delete(t, R);
    SNAP_HASHTABLE_print(R);
    // For ``*'' in queries, I use -1 for int attributes, and "" for string attributes; that's ok for this project or you can do something else
    t = new_SNAP_TUPLE(-1, "L. Van Pelt", "", "");
    SNAP_delete(t, R);
    SNAP_HASHTABLE_print(R);
    t = new_SNAP_TUPLE(12345, "", "", "");
    SNAP_delete(t, R);
    SNAP_HASHTABLE_print(R);
}
