

#include "pda.h"

PDA_TUPLE* new_PDA_TUPLE(char* project_id, char* department, char* account) {
	PDA_TUPLE* t = (PDA_TUPLE*)malloc(sizeof(PDA_TUPLE));
	strncpy(t->project_id, project_id, sizeof(t->project_id) - 1);
	t->project_id[sizeof(t->project_id) - 1] = '\0';
	strncpy(t->department, department, sizeof(t->department) - 1);
	t->department[sizeof(t->department) - 1] = '\0';
	strncpy(t->account, account, sizeof(t->account) - 1);
	t->account[sizeof(t->account) - 1] = '\0';
	t->next = NULL;
	return t;
}
void PDA_TUPLE_print(struct PDA_TUPLE* this) {
	printf("project_id: %s, department: %s, account: %s\n", this->project_id, this->department, this->account);

}
int h_PDA_proj(PDA_TUPLE* t) {
	int sum = 0;
	for (int i = 0; i < strlen(t->project_id); i++) {
		sum += t->project_id[i];
	}
	return sum % PDA_HASHTABLE_SIZE;


}

bool PDA_TUPLE_equals(PDA_TUPLE* t1, PDA_TUPLE* t2) {
	if (strlen(t1->project_id) != 0 && strlen(t2->project_id) != 0) {
		if (strcmp(t1->project_id, t2->project_id) != 0) {
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


void PDA_insert(PDA_TUPLE* t, PDA_HASHTABLE R) {
	printf("PDA_insert: ");
	PDA_TUPLE_print(t);
	int i = h_PDA_proj(t);
	PDA_TUPLE* p = R[i];
	while (p != NULL) {
		if (PDA_TUPLE_equals(p, t)) {
			return;
		}
		else {
			p = p->next;
		}
	}
	t->next = R[i];
	R[i] = t;
}
PDA_TUPLELIST PDA_lookup(PDA_TUPLE* X, PDA_HASHTABLE R) {
	printf("PDA_lookup: ");
	PDA_TUPLE_print(X);
	PDA_TUPLELIST result = NULL;
	PDA_TUPLELIST result_return = NULL; // store the header pointer of the result list
	if(X->project_id[0] != '\0'){
		int i = h_PDA_proj(X);
		PDA_TUPLE* p = R[i];
		while (p != NULL) {
			if (PDA_TUPLE_equals(p, X)) {
				if (result == NULL) {
					result = new_PDA_TUPLE(p->project_id, p->department, p->account);
					result_return = result;
				}
				else {
					result->next = new_PDA_TUPLE(p->project_id, p->department, p->account);
					result = result->next;
				}
			}
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
			PDA_TUPLE *p = R[i];
			while (p != NULL) {
				if (PDA_TUPLE_equals(p, X)) {
					if (result == NULL) {
						result = new_PDA_TUPLE(p->project_id, p->department, p->account);
						result_return = result;
					} else {
						result->next = new_PDA_TUPLE(p->project_id, p->department, p->account);
						result = result->next;
					}
				}
				p = p->next;
			}
		}
	}
	return result_return;
}


void PDA_delete(PDA_TUPLE* X, PDA_HASHTABLE R) {
	printf("PDA_delete: ");
	PDA_TUPLE_print(X);
	if (X->project_id[0] != '\0') {
		int i = h_PDA_proj(X);
		PDA_TUPLE* p = R[i];
		PDA_TUPLE* prev = NULL;
		while (p != NULL) {
			if (PDA_TUPLE_equals(p, X)) {
				if (prev == NULL) {
					R[i] = p->next;
				}
				else {
					prev->next = p->next;
				}
				printf("Deleting: ");
				PDA_TUPLE_print(p);
				free(p);
				return;
			}
			prev = p;
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
			PDA_TUPLE* p = R[i];
			PDA_TUPLE* prev = NULL;
			while (p != NULL) {
				if (PDA_TUPLE_equals(p, X)) {
					if (prev == NULL) {
						R[i] = p->next;
					}
					else {
						prev->next = p->next;
					}
					printf("Deleting: ");
					PDA_TUPLE_print(p);
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


void PDA_HASHTABLE_init(PDA_HASHTABLE R) {
	for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
		R[i] = NULL;
	}
}
void PDA_HASHTABLE_print(PDA_HASHTABLE table) {
	for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
		PDA_TUPLE* p = table[i];
		while (p != NULL) {
			PDA_TUPLE_print(p);
			p = p->next;
			if (p != NULL) {
				printf("\n");
			}
		}
	}
}

void PDAList_free(PDA_TUPLELIST list) {
	PDA_TUPLELIST p = list;
	while (p != NULL) {
		PDA_TUPLELIST temp = p;
		p = p->next;
		free(temp);
	}
}