#include "pd.h"


PD_TUPLE* new_PD_TUPLE(char* project_id, char* manager_ssn) {
	PD_TUPLE* t = (PD_TUPLE*)malloc(sizeof(PD_TUPLE));
	strncpy(t->project_id, project_id, sizeof(t->project_id) - 1);
	t->project_id[sizeof(t->project_id) - 1] = '\0';
	strncpy(t->depends_on, manager_ssn, sizeof(t->depends_on) - 1);
	t->depends_on[sizeof(t->depends_on) - 1] = '\0';
	t->next = NULL;
	return t;

}
void PD_TUPLE_print(struct PD_TUPLE* this) {
	printf("project_id: %s, depends_on: %s\n", this->project_id, this->depends_on);


}
int h_PD_proj(PD_TUPLE* t) {
	int sum = 0;
	for (int i = 0; i < strlen(t->depends_on); i++) {
		sum += t->depends_on[i];
	}
	return sum % PD_HASHTABLE_SIZE;
}


bool PD_TUPLE_equals(PD_TUPLE* t1, PD_TUPLE* t2) {
	if (strlen(t1->project_id) != 0 && strlen(t2->project_id) != 0) {
		if (strcmp(t1->project_id, t2->project_id) != 0) {
			return false;
		}
	}
	if (strlen(t1->depends_on) != 0 && strlen(t2->depends_on) != 0) {
		if (strcmp(t1->depends_on, t2->depends_on) != 0) {
			return false;
		}
	}
	return true;
}

void PD_insert(PD_TUPLE* t, PD_HASHTABLE R) {
	printf("PD_insert: ");
	PD_TUPLE_print(t);
	int i = h_PD_proj(t);
	PD_TUPLE* p = R[i];
	while (p != NULL) {
		if (PD_TUPLE_equals(p, t)) {
			return;
		}
		else {
			p = p->next;
		}
	}
	t->next = R[i];
	R[i] = t;
}
PD_TUPLELIST PD_lookup(PD_TUPLE* X, PD_HASHTABLE R) {
	printf("PD_lookup: ");
	PD_TUPLE_print(X);
	// if x is hashable
	PD_TUPLELIST result = NULL;
	PD_TUPLELIST result_return = NULL; // store the header pointer of the result list

	if (X->depends_on[0] != '\0') {
		int i = h_PD_proj(X);
		PD_TUPLE* p = R[i];
		while (p != NULL) {
			if (PD_TUPLE_equals(p, X)) {
				if (result == NULL) {
					result = new_PD_TUPLE(p->project_id, p->depends_on);
					result_return = result;
				}
				else {
					result->next = new_PD_TUPLE(p->project_id, p->depends_on);
					result = result->next;
				}
			}
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
			PD_TUPLE* p = R[i];
			while (p != NULL) {
				if (PD_TUPLE_equals(p, X)) {
					if (result == NULL) {
						result = new_PD_TUPLE(p->project_id, p->depends_on);
					}
					else {
						result->next = new_PD_TUPLE(p->project_id, p->depends_on);
						result = result->next;
					}
				}
				p = p->next;
			}
		}
	}
	return result_return;

}
void PD_delete(PD_TUPLE* X, PD_HASHTABLE R) {
	printf("PD_delete: ");
	PD_TUPLE_print(X);
	if (X->depends_on[0] != '\0') {
		int i = h_PD_proj(X);
		PD_TUPLE* p = R[i];
		PD_TUPLE* prev = NULL;
		while (p != NULL) {
			if (PD_TUPLE_equals(p, X)) {
				if (prev == NULL) {
					R[i] = p->next;
				}
				else {
					prev->next = p->next;
				}
				printf("Deleting: ");
				PD_TUPLE_print(p);
				free(p);
				return;
			}
			else {
				prev = p;
				p = p->next;
			}
		}
	}
	else {
		for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
			PD_TUPLE* p = R[i];
			PD_TUPLE* prev = NULL;
			while (p != NULL) {
				if (PD_TUPLE_equals(p, X)) {
					if (prev == NULL) {
						R[i] = p->next;
					}
					else {
						prev->next = p->next;
					}
					printf("Deleting: ");
					PD_TUPLE_print(p);
					free(p);
					break;
				}
				else {
					prev = p;
					p = p->next;
				}
			}
		}
	}

}
void PD_HASHTABLE_init(PD_HASHTABLE R) {
	for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
		R[i] = NULL;
	}
}
void PD_HASHTABLE_print(PD_HASHTABLE table) {
	for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
		printf("Bucket %d: \n", i);
		for (PD_TUPLELIST p = table[i]; p != NULL; p = p->next) {
			PD_TUPLE_print(p);
		}
		printf("\n");
	}
}