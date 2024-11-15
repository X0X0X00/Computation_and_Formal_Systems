
#ifndef PROJ4_PM_H
#define PROJ4_PM_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef struct PM_TUPLE *PM_TUPLELIST;
struct PM_TUPLE {
	char project_id[MAX];
	char manager_ssn[MAX];
	PM_TUPLELIST next;
};
#define PM_HASHTABLE_SIZE 11
typedef PM_TUPLELIST PM_HASHTABLE[PM_HASHTABLE_SIZE];

typedef struct PM_TUPLE PM_TUPLE;


PM_TUPLE* new_PM_TUPLE(char* project_id, char* manager_ssn);
void PM_TUPLE_print(struct PM_TUPLE* this);
int h_PM_proj(PM_TUPLE* t);

bool PM_TUPLE_equals(PM_TUPLE* t1, PM_TUPLE* t2);
void PM_insert(PM_TUPLE* t, PM_HASHTABLE R);
PM_TUPLELIST PM_lookup(PM_TUPLE* X, PM_HASHTABLE R);
void PM_delete(PM_TUPLE* X, PM_HASHTABLE R);
void PM_HASHTABLE_init(PM_HASHTABLE R);
void PM_HASHTABLE_print(PM_HASHTABLE table);



#endif //PROJ4_PM_H
