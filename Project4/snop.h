#ifndef PROJ4_SNOP_H
#define PROJ4_SNOP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef struct SNOP_TUPLE *SNOP_TUPLELIST;
struct SNOP_TUPLE {
	char ssn[MAX];
	char name[MAX];
	char office[MAX];
	char phone[MAX];
	SNOP_TUPLELIST next;
};
#define SNOP_HASHTABLE_SIZE 11
typedef SNOP_TUPLELIST SNOP_HASHTABLE[SNOP_HASHTABLE_SIZE];

typedef struct SNOP_TUPLE SNOP_TUPLE;

typedef struct Name_TUPLE *Name_TUPLELIST;
struct Name_TUPLE {
	char name[MAX];
	Name_TUPLELIST next;
};
typedef struct Name_TUPLE Name_TUPLE;

Name_TUPLE *new_Name_TUPLE(char *name);
void Name_TUPLE_print(Name_TUPLELIST n);

SNOP_TUPLE* new_SNOP_TUPLE(char* ssn, char* name, char* office, char* phone);
void SNOP_TUPLE_print(struct SNOP_TUPLE* this);
int h_SNOP_ssn(SNOP_TUPLE* t);

bool SNOP_TUPLE_equals(SNOP_TUPLE* t1, SNOP_TUPLE* t2);
void SNOP_insert(SNOP_TUPLE* t, SNOP_HASHTABLE R);
SNOP_TUPLELIST SNOP_lookup(SNOP_TUPLE* X, SNOP_HASHTABLE R);
void SNOP_delete(SNOP_TUPLE* X, SNOP_HASHTABLE R);
void SNOP_HASHTABLE_init(SNOP_HASHTABLE R);
void SNOP_HASHTABLE_print(SNOP_HASHTABLE table);

void SNOPList_free(SNOP_TUPLELIST list);

#endif //PROJ4_SNOP_H
