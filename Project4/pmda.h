#ifndef PROJ4_PMDA_H
#define PROJ4_PMDA_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef struct PMDA_TUPLE *PMDA_TUPLELIST;
struct PMDA_TUPLE {
	char project_id[MAX];
	char manager_ssn[MAX];
	char department[MAX];
	char account[MAX];
	PMDA_TUPLELIST next;
};
#define PMDA_HASHTABLE_SIZE 11
typedef PMDA_TUPLELIST PMDA_HASHTABLE[PMDA_HASHTABLE_SIZE];
typedef struct PMDA_TUPLE PMDA_TUPLE;

typedef struct DA_TUPLE *DA_TUPLELIST;
struct DA_TUPLE {
	char department[MAX];
	char account[MAX];
	DA_TUPLELIST next;
};
typedef struct DA_TUPLE DA_TUPLE;


DA_TUPLE *new_DA_TUPLE(char *department, char *account);
void DA_TUPLELIST_print(DA_TUPLELIST n);
PMDA_TUPLE* new_PMDA_TUPLE(char* project_id, char* manager_ssn, char* department, char* account);
void PMDA_TUPLE_print(struct PMDA_TUPLE* this);
int h_PMDA_proj(PMDA_TUPLE* t);

bool PMDA_TUPLE_equals(PMDA_TUPLE* t1, PMDA_TUPLE* t2);
void PMDA_insert(PMDA_TUPLE* t, PMDA_HASHTABLE R);
PMDA_TUPLELIST PMDA_lookup(PMDA_TUPLE* X, PMDA_HASHTABLE R);
void PMDA_delete(PMDA_TUPLE* X, PMDA_HASHTABLE R);
void PMDA_HASHTABLE_init(PMDA_HASHTABLE R);
void PMDA_HASHTABLE_print(PMDA_HASHTABLE table);
#endif //PROJ4_PMDA_H
