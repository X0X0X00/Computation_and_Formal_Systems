
#include "pm.h"

PM_TUPLE* new_PM_TUPLE(char* project_id, char* manager_ssn) {
	PM_TUPLE* t = (PM_TUPLE*)malloc(sizeof(PM_TUPLE));
	strncpy(t->project_id, project_id, sizeof(t->project_id) - 1);
	t->project_id[sizeof(t->project_id) - 1] = '\0';
	strncpy(t->manager_ssn, manager_ssn, sizeof(t->manager_ssn) - 1);
	t->manager_ssn[sizeof(t->manager_ssn) - 1] = '\0';
	t->next = NULL;
	return t;

}

void PM_TUPLE_print(struct PM_TUPLE* this) {
	printf("project_id: %s, manager_ssn: %s\n", this->project_id, this->manager_ssn);

}
int h_PM_proj(PM_TUPLE* t) {
	int sum = 0;
	for (int i = 0; i < strlen(t->manager_ssn); i++) {
		sum += t->manager_ssn[i];
	}
	return sum % PM_HASHTABLE_SIZE;

}


bool PM_TUPLE_equals(PM_TUPLE* t1, PM_TUPLE* t2) {
	if (strlen(t1->project_id) != 0 && strlen(t2->project_id) != 0) {
		if (strcmp(t1->project_id, t2->project_id) != 0) {
			return false;
		}
	}
	if (strlen(t1->manager_ssn) != 0 && strlen(t2->manager_ssn) != 0) {
		if (strcmp(t1->manager_ssn, t2->manager_ssn) != 0) {
			return false;
		}
	}
	return true;
}

void PM_insert(PM_TUPLE* t, PM_HASHTABLE R) {
	printf("PM_insert: ");
	PM_TUPLE_print(t);
	int i = h_PM_proj(t);
	PM_TUPLE* p = R[i];
	while (p != NULL) {
		if (PM_TUPLE_equals(p, t)) {
			return;
		}
		else {
			p = p->next;
		}
	}
	t->next = R[i];
	R[i] = t;
}


PM_TUPLELIST PM_lookup(PM_TUPLE* X, PM_HASHTABLE R) {
	printf("PM_lookup: ");
	PM_TUPLE_print(X);
	// if x is hashable
	PM_TUPLELIST result = NULL;
	PM_TUPLELIST result_return = NULL; // store the header pointer of the result list

	if(X->manager_ssn[0] != '\0'){
		int i = h_PM_proj(X);
		PM_TUPLE* p = R[i];
		while (p != NULL) {
			if (PM_TUPLE_equals(p, X)) {
				if (result == NULL) {
					result = new_PM_TUPLE(p->project_id, p->manager_ssn);
					result_return = result;
				}
				else {
					result->next = new_PM_TUPLE(p->project_id, p->manager_ssn);
					result = result->next;
				}
			}
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
			PM_TUPLE* p = R[i];
			while (p != NULL) {
				if (PM_TUPLE_equals(p, X)) {
					if (result == NULL) {
						result = new_PM_TUPLE(p->project_id, p->manager_ssn);
						result_return = result;
					}
					else {
						result->next = new_PM_TUPLE(p->project_id, p->manager_ssn);
						result = result->next;
					}
				}
				p = p->next;
			}
		}

	}
	return result_return;
}
void PM_delete(PM_TUPLE* X, PM_HASHTABLE R) {
	printf("PM_delete: ");
	PM_TUPLE_print(X);
	if (X->manager_ssn[0] != '\0') {
		int i = h_PM_proj(X);
		PM_TUPLE* p = R[i];
		PM_TUPLE* prev = NULL;
		while (p != NULL) {
			if (PM_TUPLE_equals(p, X)) {
				if (prev == NULL) {
					R[i] = p->next;
				}
				else {
					prev->next = p->next;
				}
				printf("Deleting: ");
				PM_TUPLE_print(p);
				free(p);
				return;
			}
			prev = p;
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
			PM_TUPLE* p = R[i];
			PM_TUPLE* prev = NULL;
			while (p != NULL) {
				if (PM_TUPLE_equals(p, X)) {
					if (prev == NULL) {
						R[i] = p->next;
					}
					else {
						prev->next = p->next;
					}
					printf("Deleting: ");
					PM_TUPLE_print(p);
					free(p);
					p = prev->next;
				}
				else {
					prev = p;
					p = p->next;
				}
			}
		}
	}


}
void PM_HASHTABLE_init(PM_HASHTABLE R) {
	for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
		R[i] = NULL;
	}

}
void PM_HASHTABLE_print(PM_HASHTABLE table) {
	for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
		printf("Bucket %d: \n", i);
		for (PM_TUPLELIST p = table[i]; p != NULL; p = p->next) {
			PM_TUPLE_print(p);
		}
		printf("\n");
	}
}