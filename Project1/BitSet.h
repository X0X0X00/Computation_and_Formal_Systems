/*
 * File: BitSet.h
 * Creator: George Ferguson
 * Created: Fri Jul  1 09:41:51 2016
 *
 * A BitSet represents a set of integers using bits of an int.
 * This makes most of the set operations constant-time.
 * The maximum value that can be stored in the set is limited
 * by the number of bits in the biggest int we can get
 * (typically 64, sometimes 32).
 */

#ifndef _BitSet_h
#define _BitSet_h

#include <stdbool.h>

typedef struct BitSet* BitSet;

/**
 * Return the largest value that can be stored in a BitSet.
 * BitSets can store elements with values from 0 to this value.
 */
extern int BitSet_maxValue();

/**
 * Allocate, initialize and return a new (empty) BitSet.
 */
extern BitSet new_BitSet();

/**
 * Free the memory used for the given Bitset.
 */
extern void BitSet_free(BitSet this);

/**
 * Return true if the given BitSet is empty.
 */
extern bool BitSet_isEmpty(const BitSet this);

/**
 * Add given element (int) to the given BitSet (if it's not already there).
 * The maximum element value that can be stored in a BitSet is limited
 * by the number of bits in a long int (typically 64, sometimes 32).
 */
extern void BitSet_insert(BitSet this, int value);

/**
 * Return true if the given BitSet contains the given int value.
 */
extern bool BitSet_lookup(const BitSet this, int value);

/**
 * Add the contents of the second BitSet to the first BitSet (adding those elements
 * that aren't already in set1). This will modify the first set unless the second
 * set is empty or all its elements are already in in the first set.
 */
extern void BitSet_union(BitSet this, const BitSet other);

/**
 * Return true if the first BitSet contains every member of the second
 * BitSet.
 */
extern bool BitSet_containsAll(BitSet this, BitSet other);

/**
 * Return true if the two given BitSet contain exactly the same members,
 * otherwise false.
 */
extern bool BitSet_equals(BitSet this, BitSet other);

/**
 * Call the given function on each element of given BitSet, passing the
 * int value to the function.
 */
extern void IntSet_iterate(const BitSet this, void (*func)(int));

typedef struct BitSetIterator *BitSetIterator;

/**
 * Return an BitSetIterator for the given BitSet.
 * Don't forget to free() this when you're done iterating.
 */
extern BitSetIterator BitSet_iterator(const BitSet set);

/**
 * Return true if the given BitSetIterator will return another element
 * if BitSetIterator_next() is called.
 */
extern bool BitSetIterator_hasNext(const BitSetIterator this);

/**
 * Return the next int from the given BitSetIterator and increment it
 * to point to the next element.
 */
extern int BitSetIterator_next(BitSetIterator this);

/**
 * Print the given BitSet to stdout.
 */
extern void BitSet_print(BitSet this);

/**
 * Return the string representation of the given BitSet.
 * Don't forget to free() this string.
 */
extern char *BitSet_toString(BitSet this);

#endif
