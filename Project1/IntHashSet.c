/**
 * IntHashSet.c
 * Author: George Ferguson
 *
 * Hashtable implementation of a set of ints.
 * @see FOCS pp. 360-363, 415
 *
 * This is a weak example of a set implementation.
 * It doesn't do anything smart about set operations other
 * than making it easy to add an element (int) to the set.
 * And it isn't very smart about that either, to be honest.
 *
 * YOU could probably do better...
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h> // used by toString()

#include "IntHashSet.h"

struct Node {
	int element;
	struct Node* next;
};
typedef struct Node Node;

struct IntHashSet {
	int size;
	Node** buckets; // Array of pointers to first node in list for bucket
	int count;
};

static Node* new_Node(int element) {
	Node* this = (Node*)malloc(sizeof(struct Node));
	this->element = element;
	this->next = NULL;
	return this;
}

/**
 * Allocate and return a new empty IntHashSet.
 */
IntHashSet new_IntHashSet(int size) {
	IntHashSet this = (IntHashSet)malloc(sizeof(struct IntHashSet));
	if (this == NULL) {
		return NULL;
	}
	this->size = size;
	this->buckets = (Node**)calloc(size, sizeof(Node*));
	for (int i=0; i < size; i++) {
		this->buckets[i] = NULL;
	}
	this->count = 0;
	return this;
}

/**
 * Free the given IntHashSet.
 */
void IntHashSet_free(IntHashSet this) {
	if (this == NULL) {
		return;
	}
	// Free all the nodes
	for (int index=0; index < this->size; index++) {
		Node* p = this->buckets[index];
		while (p != NULL) {
			Node* next = p->next;
			free(p);
			p = next;
		}
	}
	// Free the hashtable (array of bucket list headers) itself
	free(this->buckets);
	// Free the struct
	free(this);
}

/**
 * Very simple hash function for IntHashSet.
 * @see FOCS p415.
 */
static int IntHashSet_hash(IntHashSet this, int element) {
	int index = element % this->size;
	return index;
}

/**
 * Insert the given element (int) into the Node list
 * pointed to by pL. That is, pL is the address of a Node.
 * If that address contains NULL, then this is the place
 * to add the element, so fill that address with a new Node.
 * Otherwise, pL points to a Node. If that Node's element
 * is the same as i, then i is already in the set and there
 * is nothing to do. Otherwise, try the next node in the list.
 * @see FOCS Fig 7.14 p. 365
 * We return true if the element was added or false if it was
 * already there, to support keeping track of the count of elements.
 */
static bool IntHashSet_bucketInsert(int element, Node** pL) {
	if ((*pL) == NULL) {
		// Not found in bucket: append
		(*pL) = new_Node(element);
		return true; // Yes added
	} else if ((*pL)->element == element) {
		// Found in bucket
		return false; // Not added
	} else {
		// Keep searching bucket
		return IntHashSet_bucketInsert(element, &((*pL)->next));
	}
}

/**
 * Insert the given element into the given IntHashSet if
 * it isn't already present.
 */
void IntHashSet_insert(IntHashSet this, int element) {
	int index = IntHashSet_hash(this, element);
	if (IntHashSet_bucketInsert(element, &(this->buckets[index]))) {
		this->count += 1;
	}
}

/**
 * Return true if the given element is in the given IntHashSet,
 * otherwise false.
 */
bool IntHashSet_lookup(IntHashSet this, int element) {
	int index = IntHashSet_hash(this, element);
	for (Node* p=this->buckets[index]; p != NULL; p=p->next) {
		if (p->element == element) {
			return true;
		}
	}
	return false;
}

/**
 * Add the contents of another IntHashSet to the given IntHashSet
 * (only adding those elements that aren't already in the first set).
 * This will modify the first set unless the second set is empty or
 * all its elements are already in the first set.
 */
void IntHashSet_union(IntHashSet this, const IntHashSet other) {
	// Iterate over elements of other set, adding to this set
	for (int index=0; index < other->size; index++) {
		for (Node* p=other->buckets[index]; p != NULL; p=p->next) {
			int element = p->element;
			IntHashSet_insert(this, element);
		}
	}
}

/**
 * Print the given IntHashSet to stdout.
 */
void IntHashSet_print(IntHashSet this) {
	printf("{");
	int n = 0;
	for (int index=0; index < this->size; index++) {
		for (Node* p=this->buckets[index]; p != NULL; p=p->next) {
			int element = p->element;
			printf("%d", element);
			n += 1;
			if (n < this->count) {
				printf(",");
			}
		}
	}
	printf("}");
}

/**
 * Return the number of elements (ints) in the given IntHashSet.
 */
int IntHashSet_count(IntHashSet this) {
	// Cached count saves scanning the entire hashtable every time
	return this->count;
}

/**
 * Return true if this IntHashSet is empty (contains no elements).
 */
bool IntHashSet_isEmpty(IntHashSet this) {
	// Ditto
	return this->count == 0;
}

/**
 * Return true if the two given IntHashSets contain exactly the
 * name elements (ints), otherwise false.
 */
bool IntHashSet_equals(IntHashSet this, IntHashSet other) {
	// Cached count may short-circuit this test
	if (this->count != other->count) {
		return false;
	}
	// Otherwise have to scan and test each element
	// You might be able to figure out which is better to scan over...
	for (int index=0; index < this->size; index++) {
		for (Node* p=this->buckets[index]; p != NULL; p=p->next) {
			int element = p->element;
			if (!IntHashSet_lookup(other, element)) {
				return false;
			}
		}
	}
	return true;
}

/**
 * Call the given function on each element of the given
 * IntHashSet, calling the given function on each int value
 * one after the other.
 */
void IntHashSet_iterate(const IntHashSet this, void (*func)(int)) {
	for (int index=0; index < this->size; index++) {
		for (Node* p=this->buckets[index]; p != NULL; p=p->next) {
			int element = p->element;
			func(element);
		}
	}
}

/**
 * An IntHashSetIterator iterates over the elements (ints)
 * in an IntHashSet.
 */
struct IntHashSetIterator {
	IntHashSet set;
	int count;
	int index;	// bucket
	Node *node;	// Node within bucket
};

/**
 * Return an IntHashSetIterator for the given IntHashSet.
 * Don't forget to free() this when you're done iterating.
 */
IntHashSetIterator IntHashSet_iterator(const IntHashSet this) {
	IntHashSetIterator iterator = (IntHashSetIterator)malloc(sizeof(struct IntHashSetIterator));
	iterator->set = this;
	iterator->count = 0;
	iterator->index = 0;
	iterator->node = this->buckets[0];
	return iterator;
}

/**
 * Return true if the next call to IntHashSetIterator_next on the given
 * IntHashSetIterator will not fail.
 */
bool IntHashSetIterator_hasNext(const IntHashSetIterator this) {
	return this->count < this->set->count;
}

/**
 * Return the next int in the IntHashSet underlying the given
 * IntHashSetIterator, or -1 if there is no such element (even though
 * -1 could be a value in an IntHashSet).
 */
int IntHashSetIterator_next(IntHashSetIterator this) {
	while (this->node == NULL) {
		if (this->index >= this->set->size) {
			// Not found!
			return -1;
		}
		this->index += 1;
		this->node = this->set->buckets[this->index];
	}
	int element = this->node->element;
	this->node = this->node->next;
	this->count += 1;
	return element;
}

/**
 * Return the string representation of the given IntHashSet.
 * Don't forget to free() this string.
 */
char* IntHashSet_toString(IntHashSet this) {
	char *result = NULL;
	IntHashSetIterator iterator = IntHashSet_iterator(this);
	while (IntHashSetIterator_hasNext(iterator)) {
		int value = IntHashSetIterator_next(iterator);
		static char buf[256];
		snprintf(buf, sizeof(buf)-1, "%d", value);
		if (IntHashSetIterator_hasNext(iterator)) {
			strcat(buf, ",");
		}
		if (result == NULL) {
			result = malloc(strlen(buf)+1);
			strcpy(result, buf);
		} else {
			char *old_result = result;
			result = (char*)malloc(strlen(old_result)+strlen(buf)+1);
			strcpy(result, old_result);
			strcat(result, buf);
			free(old_result);
		}
	}
	free(iterator);
	return result;
}

#ifdef MAIN

static void callback(int element) {
	printf("callback: %d\n", element);
}

int main(int argc, char* argv[]) {
	printf("creating set with size 7...\n");
	IntHashSet set1 = new_IntHashSet(7);
	printf("testing insert...\n");
	IntHashSet_insert(set1, 0);
	IntHashSet_insert(set1, 1);
	IntHashSet_insert(set1, 2);
	IntHashSet_print(set1);
	printf("\n");
	printf("testing insert existing elements...\n");
	IntHashSet_insert(set1, 0);
	IntHashSet_print(set1);
	IntHashSet_insert(set1, 1);
	IntHashSet_print(set1);
	IntHashSet_insert(set1, 2);
	IntHashSet_print(set1);
	printf("\n");
	printf("testing insert to force overflow...\n");
	IntHashSet_insert(set1, 3);
	IntHashSet_insert(set1, 4);
	IntHashSet_insert(set1, 5);
	IntHashSet_insert(set1, 6);
	IntHashSet_insert(set1, 7); // index 0: 0,7,1,2,3,4,5,6
	IntHashSet_print(set1);
	printf("\n");
	printf("testing lookup...\n");
	printf("lookup 0: %d\n", IntHashSet_lookup(set1, 0));
	printf("lookup 3: %d\n", IntHashSet_lookup(set1, 3));
	printf("lookup 7: %d\n", IntHashSet_lookup(set1, 7));
	printf("lookup 8: %d\n", IntHashSet_lookup(set1, 8));
	printf("testing iterate...\n");
	IntHashSet_iterate(set1, callback);
	printf("testing iterator...\n");
	IntHashSetIterator iterator = IntHashSet_iterator(set1);
	while (IntHashSetIterator_hasNext(iterator)) {
		int element = IntHashSetIterator_next(iterator);
		printf("%d ", element);
	}
	printf("\n");
	printf("freeing iterator\n");
	free(iterator);
	printf("creating new set with size 5...\n");
	IntHashSet set2 = new_IntHashSet(5);
	IntHashSet_insert(set2, 0);
	IntHashSet_insert(set2, 1);
	IntHashSet_insert(set2, 2);
	IntHashSet_print(set2);
	printf("\n");
	printf("set1 equals set2? %d\n", IntHashSet_equals(set1, set2));
	printf("set2 equals set1? %d\n", IntHashSet_equals(set2, set1));
	IntHashSet_insert(set2, 3);
	IntHashSet_insert(set2, 4);
	IntHashSet_insert(set2, 5); // index 0
	IntHashSet_insert(set2, 6); // index 1
	IntHashSet_insert(set2, 7); // index 2
	IntHashSet_print(set2);
	printf("\n");
	printf("set1 equals set2? %d\n", IntHashSet_equals(set1, set2));
	printf("set2 equals set1? %d\n", IntHashSet_equals(set2, set1));
	printf("testing set1 with more elements...\n");
	for (int i=8; i < 100; i++) {
		IntHashSet_insert(set1, i);
	}
	IntHashSet_print(set1);
	printf("\n");
	printf("lookup 77: %d\n", IntHashSet_lookup(set1, 77));
	printf("lookup 666: %d\n", IntHashSet_lookup(set1, 666));
	printf("testing toString...\n");
	char *s1 = IntHashSet_toString(set1);
	printf("s1=\"%s\"\n", s1);
	free(s1);
	char *s2 = IntHashSet_toString(set2);
	printf("s2=\"%s\"\n", s2);
	free(s2);
	printf("freeing both sets\n");
	IntHashSet_free(set1);
	IntHashSet_free(set2);
}

#endif

