
#ifndef _IntHashSet_h
#define _IntHashSet_h

#include <stdbool.h>

typedef struct IntHashSet* IntHashSet;

extern IntHashSet new_IntHashSet(int size);
extern void IntHashSet_free(IntHashSet this);
extern void IntHashSet_insert(IntHashSet this, int i);
extern bool IntHashSet_lookup(IntHashSet this, int i);
extern void IntHashSet_union(IntHashSet this, const IntHashSet other);
extern void IntHashSet_print(IntHashSet this);
extern int IntHashSet_count(IntHashSet this);
extern bool IntHashSet_isEmpty(IntHashSet this);
extern bool IntHashSet_equals(IntHashSet this, IntHashSet other);
extern void IntHashSet_iterate(const IntHashSet this, void (*func)(int));

typedef struct IntHashSetIterator* IntHashSetIterator;

extern IntHashSetIterator IntHashSet_iterator(const IntHashSet this);
extern bool IntHashSetIterator_hasNext(const IntHashSetIterator this);
extern int IntHashSetIterator_next(IntHashSetIterator this);

extern char* IntHashSet_toString(IntHashSet this);

#endif
