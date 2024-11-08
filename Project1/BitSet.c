/*
 * File: BitSet.c
 * Creator: George Ferguson
 * Created: Thu Aug  3 17:36:24 2017
 *
 * A BitSet represents a set of integers using bits of an int.
 * This makes most of the set operations constant-time.
 * The maximum value that can be stored in the set is limited
 * by the number of bits in the biggest int we can get
 * (typically 64, sometimes 32).
 */
#include <stdlib.h>
#include <stdio.h>
#include "BitSet.h"

// Use the longest int we can get
typedef unsigned long long int bitset_t;

#define NUMBITS (sizeof(bitset_t) * 8)

struct BitSet {
	bitset_t bits;
};

/**
 * Return the largest value that can be stored in a BitSet.
 * BitSets can store elements with values from 0 to this value.
 */
int BitSet_maxValue() {
	return NUMBITS - 1;
}

/**
 * Allocate, initialize and return a new (empty) BitSet.
 */
BitSet new_BitSet() {
	BitSet this = (BitSet)malloc(sizeof(struct BitSet));
	this->bits = 0;
	return this;
}

/**
 * Free the memory used for the given BitSet.
 */
void BitSet_free(BitSet this) {
	if (this) {
		free(this);
	}
}

/**
 * Return true if the given BitSet is empty.
 */
bool BitSet_isEmpty(const BitSet set) {
	return set->bits == 0;
}

/**
 * Add given element (int) to the given BitSet (if it's not already there).
 */
void BitSet_insert(BitSet set, int element) {
	// Range check
	if (element < 0 || element >= NUMBITS) {
		fprintf(stderr, "BitSet_insert: element out of range: %d\n", element);
		abort();
	}
	set->bits |= (1L << element);
}

/**
 * Return true if the given BitSet contains the given element (int).
 */
bool BitSet_lookup(const BitSet this, int element) {
	// Range check
	if (element < 0 || element >= NUMBITS) {
		fprintf(stderr, "BitSet_lookup: element out of range: %d\n", element);
		abort();
	}
	return this->bits & (1L << element);
}

/**
 * Add the contents of the second BitSet to the first BitSet (adding those elements
 * that aren't already in set1). This will modify the first set unless the second
 * set is empty or all its elements are already in in the first set.
 */
void BitSet_union(BitSet this, const BitSet other) {
	this->bits |= other->bits;
}

/**
 * Return true if the first BitSet contains every element in the second
 * BitSet.
 */
bool BitSet_containsAll(BitSet this, BitSet other) {
	return (this->bits | other->bits) == this->bits;
}

/**
 * Return true if the two given BitSets contain exactly the same elements,
 * otherwise false.
 */
bool BitSet_equals(BitSet this, BitSet other) {
	return this->bits == other->bits;
}

/**
 * Call the given function on each element of given BitSet, passing the
 * element (int) to the function.
 */
void BitSet_iterate(const BitSet this, void (*func)(int)) {
	for (int i=0; i < NUMBITS; i++) {
		if (BitSet_lookup(this, i)) {
			func(i);
		}
	}
}

struct BitSetIterator {
	BitSet set;
	int index;
};

/**
 * Return an BitSetIterator for the given BitSet.
 * Don't forget to free() this when you're done iterating.
 */
BitSetIterator BitSet_iterator(const BitSet this) {
	BitSetIterator iterator = (BitSetIterator)malloc(sizeof(struct BitSetIterator));
	iterator->set = this;
	iterator->index = 0;
	return iterator;
}

/**
 * Return true if the next call to BitSetIterator_next on the given
 * BitSetIterator will not fail.
 * Note that this function changes the iterator, advancing it to the
 * next 1 bit (or the end of the set).
 */
bool BitSetIterator_hasNext(BitSetIterator this) {
	while (this->index < NUMBITS) {
		if (BitSet_lookup(this->set, this->index)) {
			return true;
		} else {
			this->index += 1;
		}
	}
	return false;
}

/**
 * Return the next element (int) in the BitSet underlying the
 * given BitSetIterator, or -1 if there is no such element.
 */
int BitSetIterator_next(BitSetIterator this) {
	if (BitSetIterator_hasNext(this)) {
		// iterator index will point to next 1 bit
		int value = this->index;
		this->index += 1;
		return value;
	} else {
		return -1;
	}
}

/**
 * Print the given BitSet to stdout.
 * Note that this allocates an
 */
void
BitSet_print(BitSet this) {
	printf("{");
	bool firstElement = true;
	for (int i=0; i < NUMBITS; i++) {
		if (BitSet_lookup(this, i)) {
			if (!firstElement) {
				printf(",");
			} else {
				firstElement = false;
			}
			printf("%d", i);
		}
	}
	printf("}");
}

#include <string.h>

/**
 * Return the string representation of the given BitSet.
 * Don't forget to free() this string.
 */
char* BitSet_toString(BitSet this) {
	char *result = NULL;
	BitSetIterator iterator = BitSet_iterator(this);
	while (BitSetIterator_hasNext(iterator)) {
		int value = BitSetIterator_next(iterator);
		static char buf[256];
		snprintf(buf, sizeof(buf)-2, "%d", value);
		if (BitSetIterator_hasNext(iterator)) {
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
	printf("creating initial set...\n");
	BitSet set1 = new_BitSet();
	printf("testing insert...\n");
	BitSet_insert(set1, 0);
	BitSet_insert(set1, 1);
	BitSet_insert(set1, 2);
	BitSet_print(set1);
	printf("\n");
	printf("testing insert existing elements...\n");
	BitSet_insert(set1, 0);
	BitSet_print(set1);
	BitSet_insert(set1, 1);
	BitSet_print(set1);
	BitSet_insert(set1, 2);
	BitSet_print(set1);
	printf("\n");
	printf("testing insert to force overflow...\n");
	BitSet_insert(set1, 3);
	BitSet_insert(set1, 4);
	BitSet_insert(set1, 5);
	BitSet_insert(set1, 6);
	BitSet_insert(set1, 7); // index 0: 0,7,1,2,3,4,5,6
	BitSet_print(set1);
	printf("\n");
	printf("testing lookup...\n");
	printf("lookup 0: %d\n", BitSet_lookup(set1, 0));
	printf("lookup 3: %d\n", BitSet_lookup(set1, 3));
	printf("lookup 7: %d\n", BitSet_lookup(set1, 7));
	printf("lookup 8: %d\n", BitSet_lookup(set1, 8));
	printf("testing iterate...\n");
	BitSet_iterate(set1, callback);
	printf("testing iterator...\n");
	BitSetIterator iterator = BitSet_iterator(set1);
	while (BitSetIterator_hasNext(iterator)) {
		int element = BitSetIterator_next(iterator);
		printf("%d ", element);
	}
	printf("\n");
	printf("freeing iterator\n");
	free(iterator);
	printf("creating new set...\n");
	BitSet set2 = new_BitSet();
	BitSet_insert(set2, 0);
	BitSet_insert(set2, 1);
	BitSet_insert(set2, 2);
	BitSet_print(set2);
	printf("\n");
	printf("set1 equals set2? %d\n", BitSet_equals(set1, set2));
	printf("set2 equals set1? %d\n", BitSet_equals(set2, set1));
	BitSet_insert(set2, 3);
	BitSet_insert(set2, 4);
	BitSet_insert(set2, 5); // index 0
	BitSet_insert(set2, 6); // index 1
	BitSet_insert(set2, 7); // index 2
	BitSet_print(set2);
	printf("\n");
	printf("set1 equals set2? %d\n", BitSet_equals(set1, set2));
	printf("set2 equals set1? %d\n", BitSet_equals(set2, set1));
	printf("testing set1 with more elements...\n");
	for (int i=8; i < NUMBITS; i+=2) {
		BitSet_insert(set1, i);
	}
	BitSet_print(set1);
	printf("\n");
	printf("lookup 48: %d\n", BitSet_lookup(set1, 48));
	printf("lookup 49: %d\n", BitSet_lookup(set1, 49));
	printf("testing toString...\n");
	char *s1 = BitSet_toString(set1);
	printf("s1=\"%s\"\n", s1);
	free(s1);
	char *s2 = BitSet_toString(set2);
	printf("s2=\"%s\"\n", s2);
	free(s2);
	printf("freeing both sets\n");
	BitSet_free(set1);
	BitSet_free(set2);
}

#endif
