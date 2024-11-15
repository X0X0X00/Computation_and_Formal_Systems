#ifndef PROJ4_PSH_H
#define PROJ4_PSH_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef struct PSH_TUPLE *PSH_TUPLELIST;
struct PSH_TUPLE {
	char project_id[MAX];
	char ssn[MAX];
	double hours;
	PSH_TUPLELIST next;
};
#define PSH_HASHTABLE_SIZE 11
typedef PSH_TUPLELIST PSH_HASHTABLE[PSH_HASHTABLE_SIZE];

typedef struct PSH_TUPLE PSH_TUPLE;


PSH_TUPLE* new_PSH_TUPLE(char* project_id, char* ssn, double hours);
void PSH_TUPLE_print(struct PSH_TUPLE* this);
int h_PSH_proj(PSH_TUPLE* t);

bool PSH_TUPLE_equals(PSH_TUPLE* t1, PSH_TUPLE* t2);
void PSH_insert(PSH_TUPLE* t, PSH_HASHTABLE R);
PSH_TUPLELIST PSH_lookup(PSH_TUPLE* X, PSH_HASHTABLE R);
void PSH_delete(PSH_TUPLE* X, PSH_HASHTABLE R);
void PSH_HASHTABLE_init(PSH_HASHTABLE R);
void PSH_HASHTABLE_print(PSH_HASHTABLE table);
void PSH_TUPLELIST_print(PSH_TUPLELIST list);
void PSHList_free(PSH_TUPLELIST list);

#endif //PROJ4_PSH_H
