
README for CSC173 Project 1 Sample code

This bundle includes the following:

- dfa.h and nfa.h: Examples of APIs for your data structures
  for representing automata
  - YOU have to write the C code that goes with them
    - in separate .c files that use the header files properly...
  
- IntHashSet.[ch]: Implementation of a hashtable representation
  of a set of ints, based on description in FOCS pp. 360-363, 415.
  This may be useful if you need to store sets of integers.
  Note that the implementations of the set operations that it
  supports are NOT optimized. YOU could do better.
  
- LinkedList.[ch]: Implementation of a ``generic'' linked list
  that can store any type of object (void*). This may be useful
  if you need to store things but don't know how many you
  will need at the outset. It's not the worst list implementation,
  I'll say that.
  
- BitSet.[ch]: Implementation of a set of small non-negative integers
  using a bit-vector representation. This is significantly faster
  than the IntHashSet. Most operations are constant-time. The catch
  is that you can't store elements (ints) larger than 63 (31 on some
  platforms). But if it works for what you need, give it a try.
  -> I recommend that you NOT use it.
  
- Set.h: A header that allows code written for IntHashSet sets to
  use BitSets without changing anything. Well, ALMOST anything.
  This is somewhat advanced magic. Use at your own risk.

- Makefile: A simple makefile that builds the test programs for the
  data structures included in the bundle, and also shows how you
  might get it to build YOUR program for the project.
