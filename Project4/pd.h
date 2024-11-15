#ifndef PROJ4_PD_H
#define PROJ4_PD_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef struct PD_TUPLE *PD_TUPLELIST;
struct PD_TUPLE {
	char project_id[MAX];
	char depends_on[MAX];
	PD_TUPLELIST next;
};
#define PD_HASHTABLE_SIZE 11
typedef PD_TUPLELIST PD_HASHTABLE[PD_HASHTABLE_SIZE];

typedef struct PD_TUPLE PD_TUPLE;


PD_TUPLE* new_PD_TUPLE(char* project_id, char* manager_ssn);
void PD_TUPLE_print(struct PD_TUPLE* this);
int h_PD_proj(PD_TUPLE* t);

bool PD_TUPLE_equals(PD_TUPLE* t1, PD_TUPLE* t2);
void PD_insert(PD_TUPLE* t, PD_HASHTABLE R);
PD_TUPLELIST PD_lookup(PD_TUPLE* X, PD_HASHTABLE R);
void PD_delete(PD_TUPLE* X, PD_HASHTABLE R);
void PD_HASHTABLE_init(PD_HASHTABLE R);
void PD_HASHTABLE_print(PD_HASHTABLE table);

#endif //PROJ4_PD_H
