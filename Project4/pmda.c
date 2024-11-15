#include "pmda.h"


PMDA_TUPLE* new_PMDA_TUPLE(char* project_id, char* manager_ssn, char* department, char* account) {
	PMDA_TUPLE* t = (PMDA_TUPLE*)malloc(sizeof(PMDA_TUPLE));

	strncpy(t->project_id, project_id, sizeof(t->project_id) - 1);
	t->project_id[sizeof(t->project_id) - 1] = '\0';
	strncpy(t->manager_ssn, manager_ssn, sizeof(t->manager_ssn) - 1);
	t->manager_ssn[sizeof(t->manager_ssn) - 1] = '\0';
	strncpy(t->department, department, sizeof(t->department) - 1);
	t->department[sizeof(t->department) - 1] = '\0';
	strncpy(t->account, account, sizeof(t->account) - 1);
	t->account[sizeof(t->account) - 1] = '\0';

	t->next = NULL;
	return t;

}
void PMDA_TUPLE_print(struct PMDA_TUPLE* this) {
	printf("project_id: %s, manager_ssn: %s, department: %s, account: %s\n", this->project_id, this->manager_ssn, this->department, this->account);
}
int h_PMDA_proj(PMDA_TUPLE* t) {
	int sum = 0;
	for (int i = 0; i < strlen(t->project_id); i++) {
		sum += t->project_id[i];
	}
	return sum % PMDA_HASHTABLE_SIZE;
}

bool PMDA_TUPLE_equals(PMDA_TUPLE* t1, PMDA_TUPLE* t2) {
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
	if (strlen(t1->department) != 0 && strlen(t2->department) != 0) {
		if (strcmp(t1->department, t2->department) != 0) {
			return false;
		}
	}
	if (strlen(t1->account) != 0 && strlen(t2->account) != 0) {
		if (strcmp(t1->account, t2->account) != 0) {
			return false;
		}
	}
	return true;
}


void PMDA_insert(PMDA_TUPLE* t, PMDA_HASHTABLE R) {
	printf("PMDA_insert: ");
	PMDA_TUPLE_print(t);
	int i = h_PMDA_proj(t);
	PMDA_TUPLE* p = R[i];
	while (p != NULL) {
		if (PMDA_TUPLE_equals(p, t)) {
			return;
		}
		else {
			p = p->next;
		}
	}
	t->next = R[i];
	R[i] = t;

}
PMDA_TUPLELIST PMDA_lookup(PMDA_TUPLE* X, PMDA_HASHTABLE R) {
	printf("PMDA_lookup: ");
	PMDA_TUPLE_print(X);
	// if x is hashable
	PMDA_TUPLELIST result = NULL;
	PMDA_TUPLELIST result_return = NULL; // store the header pointer of the result list

	if (X->project_id[0] != '\0') {
		int i = h_PMDA_proj(X);
		PMDA_TUPLE* p = R[i];
		while (p != NULL) {
			if (PMDA_TUPLE_equals(p, X)) {
				if (result == NULL) {
					result = new_PMDA_TUPLE(p->project_id, p->manager_ssn, p->department, p->account);
					result_return = result;
				}
				else {
					result->next = new_PMDA_TUPLE(p->project_id, p->manager_ssn, p->department, p->account);
					result = result->next;
				}
			}
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PMDA_HASHTABLE_SIZE; i++) {
			PMDA_TUPLE* p = R[i];
			while (p != NULL) {
				if (PMDA_TUPLE_equals(p, X)) {
					if (result == NULL) {
						result = new_PMDA_TUPLE(p->project_id, p->manager_ssn, p->department, p->account);
						result_return = result;
					} else {
						result->next = new_PMDA_TUPLE(p->project_id, p->manager_ssn, p->department, p->account);
						result = result->next;
					}
				}
				p = p->next;
			}
		}
	}
	return result_return;

}
void PMDA_delete(PMDA_TUPLE* X, PMDA_HASHTABLE R) {
	printf("PMDA_delete: ");
	PMDA_TUPLE_print(X);
	int i = h_PMDA_proj(X);
	PMDA_TUPLE* p = R[i];
	PMDA_TUPLE* q = NULL;
	while (p != NULL) {
		if (PMDA_TUPLE_equals(p, X)) {
			if (q == NULL) {
				R[i] = p->next;
			}
			else {
				q->next = p->next;
			}
			printf("Deleting: ");
			PMDA_TUPLE_print(p);
			free(p);
			return;
		}
		q = p;
		p = p->next;
	}

}
void PMDA_HASHTABLE_init(PMDA_HASHTABLE R) {
	for (int i = 0; i < PMDA_HASHTABLE_SIZE; i++) {
		R[i] = NULL;
	}

}
void PMDA_HASHTABLE_print(PMDA_HASHTABLE table) {
	for (int i = 0; i < PMDA_HASHTABLE_SIZE; i++) {
		PMDA_TUPLE* p = table[i];
		while (p != NULL) {
			PMDA_TUPLE_print(p);
			p = p->next;
		}
	}
}

DA_TUPLE *new_DA_TUPLE(char *department, char *account) {
	DA_TUPLE *t = (DA_TUPLE *)malloc(sizeof(DA_TUPLE));
	strcpy(t->department, department);
	strcpy(t->account, account);
	t->next = NULL;
	return t;

}
void DA_TUPLELIST_print(DA_TUPLELIST n) {
	DA_TUPLE *p = n;
	while (p != NULL) {
		printf("department: %s, account: %s\n", p->department, p->account);
		p = p->next;
	}
}