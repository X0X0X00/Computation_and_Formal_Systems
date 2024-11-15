#ifndef PROJ4_PDA_H
#define PROJ4_PDA_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef struct PDA_TUPLE *PDA_TUPLELIST;
struct PDA_TUPLE {
	char project_id[MAX];
	char department[MAX];
	char account[MAX];
	PDA_TUPLELIST next;
};
#define PDA_HASHTABLE_SIZE 11
typedef PDA_TUPLELIST PDA_HASHTABLE[PDA_HASHTABLE_SIZE];

typedef struct PDA_TUPLE PDA_TUPLE;

PDA_TUPLE* new_PDA_TUPLE(char* project_id, char* department, char* account);
void PDA_TUPLE_print(struct PDA_TUPLE* this);
int h_PDA_proj(PDA_TUPLE* t);

bool PDA_TUPLE_equals(PDA_TUPLE* t1, PDA_TUPLE* t2);
void PDA_insert(PDA_TUPLE* t, PDA_HASHTABLE R);
PDA_TUPLELIST PDA_lookup(PDA_TUPLE* X, PDA_HASHTABLE R);
void PDA_delete(PDA_TUPLE* X, PDA_HASHTABLE R);
void PDA_HASHTABLE_init(PDA_HASHTABLE R);
void PDA_HASHTABLE_print(PDA_HASHTABLE table);
void PDAList_free(PDA_TUPLELIST list);

#endif //PROJ4_PDA_H
