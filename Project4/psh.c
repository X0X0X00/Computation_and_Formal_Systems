#include "psh.h"


PSH_TUPLE* new_PSH_TUPLE(char* project_id, char* ssn, double hours) {
	PSH_TUPLE* t = (PSH_TUPLE*)malloc(sizeof(PSH_TUPLE));
	strncpy(t->project_id, project_id, sizeof(t->project_id) - 1);
	t->project_id[sizeof(t->project_id) - 1] = '\0';
	strncpy(t->ssn, ssn, sizeof(t->ssn) - 1);
	t->ssn[sizeof(t->ssn) - 1] = '\0';
	t->hours = hours;
	t->next = NULL;
	return t;
}

void PSH_TUPLE_print(struct PSH_TUPLE* this) {
	printf("project_id: %s, ssn: %s, hours: %f\n", this->project_id, this->ssn, this->hours);
}

int h_PSH_proj(PSH_TUPLE* t) {
	int sum = 0;
	for (int i = 0; i < strlen(t->project_id); i++) {
		sum += t->project_id[i];
	}
	return sum % PSH_HASHTABLE_SIZE;

}

bool PSH_TUPLE_equals(PSH_TUPLE* t1, PSH_TUPLE* t2) {
	if (strlen(t1->project_id) != 0 && strlen(t2->project_id) != 0) {
		if (strcmp(t1->project_id, t2->project_id) != 0) {
			return false;
		}
	}
	if (strlen(t1->ssn) != 0 && strlen(t2->ssn) != 0) {
		if (strcmp(t1->ssn, t2->ssn) != 0) {
			return false;
		}
	}
	if (t1->hours != -1 && t2->hours != -1) {
		if (t1->hours != t2->hours) {
			return false;
		}
	}
	return true;
}
void PSH_insert(PSH_TUPLE* t, PSH_HASHTABLE R) {
	printf("PSH_insert: ");
	PSH_TUPLE_print(t);
	int i = h_PSH_proj(t);
	PSH_TUPLE* p = R[i];
	while (p != NULL) {
		if (PSH_TUPLE_equals(p, t)) {
			return;
		}
		else {
			p = p->next;
		}
	}
	t->next = R[i];
	R[i] = t;
}
PSH_TUPLELIST PSH_lookup(PSH_TUPLE* X, PSH_HASHTABLE R) {
	printf("PSH_lookup: ");
	PSH_TUPLE_print(X);
	// if x is hashable
	PSH_TUPLELIST result = NULL;
	PSH_TUPLELIST result_return = NULL; // store the header pointer of the result list
	if (X->project_id[0] != '\0') {
		int i = h_PSH_proj(X);
		PSH_TUPLE* p = R[i];
		while (p != NULL) {
			if (PSH_TUPLE_equals(p, X)) {
				if (result == NULL) {
					result = new_PSH_TUPLE(p->project_id, p->ssn, p->hours);
					result_return = result;
				}
				else {
					result->next = new_PSH_TUPLE(p->project_id, p->ssn, p->hours);
					result = result->next;
				}
			}
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
			PSH_TUPLE* p = R[i];
			while (p != NULL) {
				if (PSH_TUPLE_equals(p, X)) {
					if (result == NULL) {
						result = new_PSH_TUPLE(p->project_id, p->ssn, p->hours);
						result_return = result;
					}
					else {
						result->next = new_PSH_TUPLE(p->project_id, p->ssn, p->hours);
						result = result->next;
					}
				}
				p = p->next;
			}
		}
	}
	return result_return;
}
void PSH_delete(PSH_TUPLE* X, PSH_HASHTABLE R) {
	printf("PSH_delete: ");
	PSH_TUPLE_print(X);
	if (X->project_id[0] != '\0') {
		int i = h_PSH_proj(X);
		PSH_TUPLE* p = R[i];
		PSH_TUPLE* q = NULL;
		while (p != NULL) {
			if (PSH_TUPLE_equals(p, X)) {
				if (q == NULL) {
					R[i] = p->next;
				}
				else {
					q->next = p->next;
				}
				printf("Deleting: ");
				PSH_TUPLE_print(p);
				free(p);
				return;
			}
			q = p;
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
			PSH_TUPLE* p = R[i];
			PSH_TUPLE* q = NULL;
			while (p != NULL) {
				if (PSH_TUPLE_equals(p, X)) {
					if (q == NULL) {
						R[i] = p->next;
					}
					else {
						q->next = p->next;
					}
					printf("Deleting: ");
					PSH_TUPLE_print(p);
					free(p);
					return;
				}
				q = p;
				p = p->next;
			}
		}
	}
}

void PSH_HASHTABLE_init(PSH_HASHTABLE R) {
	for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
		R[i] = NULL;
	}

}

void PSH_HASHTABLE_print(PSH_HASHTABLE table) {
	for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
		printf("Bucket %d: \n", i);
		for (PSH_TUPLE* p = table[i]; p != NULL; p = p->next) {
			PSH_TUPLE_print(p);
		}
		printf("\n");
	}
}

void PSH_TUPLELIST_print(PSH_TUPLELIST list) {
	for (PSH_TUPLELIST p = list; p != NULL; p = p->next) {
		PSH_TUPLE_print(p);
	}
	printf("\n");
}

void PSHList_free(PSH_TUPLELIST list) {
	PSH_TUPLELIST p = list;
	while (p != NULL) {
		PSH_TUPLELIST temp = p;
		p = p->next;
		free(temp);
	}
}