
#include "snop.h"

Name_TUPLE *new_Name_TUPLE(char *name) {
	Name_TUPLE *this = (Name_TUPLE *)malloc(sizeof(Name_TUPLE));
	if (this == NULL) {
		printf("Error: malloc failed in new_Name_TUPLE\n");
		exit(1);
	}
	strcpy(this->name, name);
	this->next = NULL;
	return this;
}

void Name_TUPLE_print(Name_TUPLELIST n) {
	printf("Name_TUPLELIST: ");
	for (Name_TUPLE *p = n; p != NULL; p = p->next) {
		printf("%s", p->name);
		if (p->next != NULL) {
			printf(", ");
		}
	}
	printf("\n");
}

// Employees have a unique SSN. Names, addresses, and phone numbers are not necessarily unique.
/**
 * Allocate a new SNOP tuple, initialize it with the given values,
 * and return the reference (pointer) to it.
 */
SNOP_TUPLE* new_SNOP_TUPLE(char* ssn, char* name, char* office, char* phone) {
	SNOP_TUPLE* t = (SNOP_TUPLE*)malloc(sizeof(SNOP_TUPLE));
	if (t == NULL) {
		printf("Error: malloc failed in new_SNOP_TUPLE\n");
		exit(1);
	}
	strncpy(t->ssn, ssn, sizeof(t->ssn) - 1);
	t->ssn[sizeof(t->ssn) - 1] = '\0';
	strncpy(t->name, name, sizeof(t->name) - 1);
	t->name[sizeof(t->name) - 1] = '\0';
	strncpy(t->office, office, sizeof(t->office) - 1);
	t->office[sizeof(t->office) - 1] = '\0';
	strncpy(t->phone, phone, sizeof(t->phone) - 1);
	t->phone[sizeof(t->phone) - 1] = '\0';
	return t;
}

/**
 * Print this given SNOP tuple to stdout.
 */
void SNOP_TUPLE_print(struct SNOP_TUPLE* this) {
	// print the snop tuple in one line
	printf("SNOP_TUPLE(%s, %s, %s, %s)\n", this->ssn, this->name, this->office, this->phone);
}

/**
 * Hash the given SNOP tuple using the studentId attribute and return
 * the index of its bucket in the SNOP hashtable.
 */
int h_SNOP_ssn(SNOP_TUPLE* t) {
	// hash the snop tuple by the ssn attribute
	int hash = 0;
	for (int i=0; i < strlen(t->ssn); i++) {
		hash += t->ssn[i];
	}
	return hash % SNOP_HASHTABLE_SIZE;
}

bool SNOP_TUPLE_equals(SNOP_TUPLE* t1, SNOP_TUPLE* t2) {
	// Compare ssn
	if (strlen(t1->ssn) != 0 && strlen(t2->ssn) != 0) {
		if (strcmp(t1->ssn, t2->ssn) != 0) {
			return false;
		}
	}
	// Compare name
	if (strlen(t1->name) != 0 && strlen(t2->name) != 0) {
		if (strcmp(t1->name, t2->name) != 0) {
			return false;
		}
	}
	// Compare office
	if (strlen(t1->office) != 0 && strlen(t2->office) != 0) {
		if (strcmp(t1->office, t2->office) != 0) {
			return false;
		}
	}
	// Compare phone
	if (strlen(t1->phone) != 0 && strlen(t2->phone) != 0) {
		if (strcmp(t1->phone, t2->phone) != 0) {
			return false;
		}
	}
	return true;
}


/**
 * FOCS p. 418: ``To insert a tuple t, we examine the bucket to check that
 * t is not already there, and we create a new cell on the bucket’s list
 * for t if it is not. [...] An insert operation always specifies the
 * inserted tuple completely.''
 */
void SNOP_insert(SNOP_TUPLE* t, SNOP_HASHTABLE R) {
	printf("SNOP_insert: ");
	SNOP_TUPLE_print(t);
	int i = h_SNOP_ssn(t);
	SNOP_TUPLE* p = R[i];
	while (p != NULL) {
		if (SNOP_TUPLE_equals(p, t)) {
			// Found
			return;
		} else {
			p = p->next;
		}
	}
	// Add t to bucket list i (at the front is easiest)
	t->next = R[i];
	R[i] = t;
}

/**
 * FOCS p. 418: ``To lookup tuples according to a specification X, we again
 * find the domain value from X and hash that value to find the proper bucket.
 * We run down the list for that bucket, producing as an answer each tuple on
 * the list that matches the specification X. [...] If the operation does not
 * specify the domain value, we are not so fortunate. [...] In those cases,
 * we must search all the bucket lists for matching tuples and [...] list
 * them.''
 * You could also gather them into a list, or into a SNOP_HASHTABLE, or ...
 */
SNOP_TUPLELIST SNOP_lookup(SNOP_TUPLE* X, SNOP_HASHTABLE R) {
	printf("SNOP_lookup: ");
	SNOP_TUPLE_print(X);
	// create the return array, which stores the address of the answers
	SNOP_TUPLELIST result = NULL;
	SNOP_TUPLELIST result_return = NULL; // store the header pointer of the result list
	if (X->ssn[0] != '\0') {
		int i = h_SNOP_ssn(X);
		// find the target tuple in the bucket
		SNOP_TUPLE* p = R[i];
		while (p != NULL) {
			if (SNOP_TUPLE_equals(p, X)) {
				// Found,we must deepcopy the data in the snop tuple
				if (result == NULL) {
					result = new_SNOP_TUPLE(p->ssn, p->name, p->office, p->phone);
					result_return = result;
				} else {
					result->next = new_SNOP_TUPLE(p->ssn, p->name, p->office, p->phone);
					result = result->next;
				}
			}
			p = p->next;
		}
	}
	else {
		for (int i=0; i < SNOP_HASHTABLE_SIZE; i++) {
			// find the target tuple in the bucket
			SNOP_TUPLE* p = R[i];
			while (p != NULL) {
				if (SNOP_TUPLE_equals(p, X)) {
					// Found,we must deepcopy the data in the snop tuple
					if (result == NULL) {
						result = new_SNOP_TUPLE(p->ssn, p->name, p->office, p->phone);
						result_return = result;
					} else {
						result->next = new_SNOP_TUPLE(p->ssn, p->name, p->office, p->phone);
						result = result->next;
					}
				}
				p = p->next;
			}
		}
	}

	return result_return;
}

/**
 * FOCS p. 418: ``To delete tuples that match a specification X, we find
 * the domain value from X, hash to find the proper bucket, and run down
 * the list for this bucket, deleting each tuple that matches the
 * specification X.''
 */
void SNOP_delete(SNOP_TUPLE* X, SNOP_HASHTABLE R) {
	printf("SNOP_delete: ");
	SNOP_TUPLE_print(X);
	// X is hashable: X->ssn is not NULL
	if (X->ssn[0] != '\0') {
		int i = h_SNOP_ssn(X);
		// find the target tuple in the bucket
		SNOP_TUPLE* p = R[i];
		SNOP_TUPLE* prev = NULL;
		while (p != NULL) {
			if (SNOP_TUPLE_equals(p, X)) {
				// Found
				if (prev == NULL) {
					// p is the first tuple in the bucket
					R[i] = p->next;
				} else {
					prev->next = p->next;
				}
				printf("Deleting: ");
				SNOP_TUPLE_print(p);
				free(p);
			} else {
				// move to the next tuple
				prev = p;
				p = p->next;
			}
		}
	}
	else {
		for (int i=0; i < SNOP_HASHTABLE_SIZE; i++) {
			// find the target tuple in the bucket
			SNOP_TUPLE* p = R[i];
			SNOP_TUPLE* prev = NULL;
			while (p != NULL) {
				if (SNOP_TUPLE_equals(p, X)) {
					// Found
					if (prev == NULL) {
						// p is the first tuple in the bucket
						R[i] = p->next;
					} else {
						prev->next = p->next;
					}
					printf("Deleting: ");
					SNOP_TUPLE_print(p);
					free(p);
				} else {
					// move to the next tuple
					prev = p;
					p = p->next;
				}
			}
		}
	}
}

/**
 * Initialize the given (empty) SNOP hashtable.
 */
void SNOP_HASHTABLE_init(SNOP_HASHTABLE R) {
	for (int i=0; i < SNOP_HASHTABLE_SIZE; i++) {
		R[i] = NULL;
	}
}

/**
 * Print the given SNOP hashtable to stdout.
 * Only print buckets that are not empty.
 */
void SNOP_HASHTABLE_print(SNOP_HASHTABLE table) {
	printf("SNOP hashtable with %d buckets\n", SNOP_HASHTABLE_SIZE);
	for (int i=0; i < SNOP_HASHTABLE_SIZE; i++) {
		if (table[i] != NULL) {
			printf("%d: ", i);
			for (SNOP_TUPLELIST p=table[i]; p != NULL; p=p->next) {
				SNOP_TUPLE_print(p);
				if (p->next != NULL) {
					printf(", ");
				}
			}
			printf("\n");
		}
	}
}

void SNOPList_free(SNOP_TUPLELIST list) {
	SNOP_TUPLELIST p = list;
	while (p != NULL) {
		SNOP_TUPLELIST tmp = p;
		p = p->next;
		free(tmp);
	}
}