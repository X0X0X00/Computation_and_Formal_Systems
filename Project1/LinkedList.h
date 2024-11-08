/*
 * File: LinkedList.h
 * Creator: George Ferguson
 * Created: Thu Jun 30 14:43:29 2016
 *
 * Singly-linked list with end pointers.
 */

#ifndef _LinkedList_h_gf
#define _LinkedList_h_gf

#include <stdbool.h>

// Partial declaration
typedef struct LinkedList* LinkedList;

/**
 * Allocate, initialize and return a new (empty) LinkedList.
 */
extern LinkedList new_LinkedList();

/**
 * Free the memory used for the given LinkedList.
 * If boolean free_data_also is true, also free the data associated with
 * each element.
 */
extern void LinkedList_free(LinkedList list, bool free_data_also);

/**
 * Return true if the given LinkedList is empty.
 */
extern bool LinkedList_isEmpty(const LinkedList this);

/**
 * Add the given element (void*) at the front of the given LinkedList.
 */
extern void LinkedList_add_at_front(LinkedList this, void *value);

/**
 * Add the given element (void*) at the end of the given LinkedList.
 */
extern void LinkedList_add_at_end(LinkedList this, void *value);

/**
 * Return true if then given LinkedList contains given void* value.
 * Note this doesn't any kind of equals function, just plain ``==''.
 */
extern bool LinkedList_contains(const LinkedList this, void *value);

/**
 * Remove the given void* value from the given LinkedList if it is there.
 * This function uses ``=='' to test for the element.
 * Note that this does not free the data associated with the element.
 */
extern void LinkedList_remove(LinkedList this, void *data);

/**
 * Return the void* value at the given index in the given LinkedList, or
 * NULL if there is no such.
 * Note that this means you can't store NULL in a LinkedList. C'est la vie.
 */
extern void *LinkedList_elementAt(LinkedList this, int index);

/**
 * Remove and return the first element from the given LinkedList.
 * Returns NULL if the list is empty.
 */
extern void *LinkedList_pop(LinkedList this);

/**
 * Call the given function on each element of given LinkedList, passing the
 * void* value to the function.
 */
extern void LinkedList_iterate(const LinkedList this, void (*func)(void*));

// Partial declaration
typedef struct LinkedListIterator *LinkedListIterator;

/**
 * Return an LinkedListIterator for the given LinkedList.
 * Don't forget to free() this when you're done iterating.
 */
extern LinkedListIterator LinkedList_iterator(const LinkedList this);

/**
 * Return true if the given LinkedListIterator will return another element
 * if LinkedListIterator_next() is called.
 */
extern bool LinkedListIterator_hasNext(const LinkedListIterator iterator);

/**
 * Return the next value from the given LinkedListIterator and increment it
 * to point to the next element.
 * Will return NULL if there is no such element.
 * This means that you can't store NULL in a LinkedList. C'est la vie (again).
 */
extern void *LinkedListIterator_next(LinkedListIterator iterator);

/**
 * Print the given LinkedList to stdout, assuming that the values are
 * all null-terminated strings.
 */
extern void LinkedList_print_string_list(LinkedList this);

#endif
