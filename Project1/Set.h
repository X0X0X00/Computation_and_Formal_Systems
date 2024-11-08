/**
 * Definitions of the Set type and functions to use either
 * IntHashSet (based on the code in FOCS) or the bit-vector
 * implementation BitSet.
 * Note that the latter will only work if you don't need to
 * store int values greater than 63 (31 on some platforms)
 * in your Sets.
 */

//#define USE_BITSET

#ifndef USE_BITSET
# include "IntHashSet.h"
# define Set IntHashSet
# define new_Set(N) new_IntHashSet(N)
# define Set_free IntHashSet_free
# define Set_isEmpty IntHashSet_isEmpty
# define Set_insert IntHashSet_insert
# define Set_union IntHashSet_union
# define Set_equals IntHashSet_equals
# define Set_print IntHashSet_print
# define Set_toString IntHashSet_toString
# define SetIterator IntHashSetIterator
# define Set_iterator IntHashSet_iterator
# define SetIterator_hasNext IntHashSetIterator_hasNext
# define SetIterator_next IntHashSetIterator_next
#else
# include "BitSet.h"
# define Set BitSet
# define new_Set(N) new_BitSet()
# define Set_free BitSet_free
# define Set_isEmpty BitSet_isEmpty
# define Set_insert BitSet_insert
# define Set_union BitSet_union
# define Set_equals BitSet_equals
# define Set_print BitSet_print
# define Set_toString BitSet_toString
# define SetIterator BitSetIterator
# define Set_iterator BitSet_iterator
# define SetIterator_hasNext BitSetIterator_hasNext
# define SetIterator_next BitSetIterator_next
#endif
