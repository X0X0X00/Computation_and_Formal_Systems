/* -*- compile-command: "gcc -o focs_11_27_gf -std=c99 -Wall -Werror focs_11_27_gf.c"; -*-
 *
 * focs_11_27_gf.c
 *
 * George Ferguson's adaptation of the code from FOCS Fig. 11.27 for
 * parsing strings of balanced parentheses.
 *
 * Changes from the code in focs_11_27.c:
 * - Define and use functions lookahead and match rather than direct
 *   string manipulation in the parsing function
 *   - These use type bool, so include stdbool.h
 * - Write parsing function B MECHANICALLY based on the productions, as seen
 *   in class.
 * - Define and use function parse to check that the entire was consumed
 *   after the parsing function returns successfully
 * - Define a stub for printing the parse tree, but you will need to write
 *   this yourself
 *   - This uses printf, so include stdio.h
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define FAILED NULL

typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4); TREE B();

TREE parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */

/**
 * Returns true if the current input symbol is the given char, otherwise false.
 */
bool lookahead(char c) {
    return *nextTerminal == c;
}

/**
 * If the current input symbol is the given char, advance to the next
 * character of the input and return true, otherwise leave it and return false.
 */
bool match(char c) {
    if (lookahead(c)) {
	nextTerminal += 1;
	return true;
    } else {
	return false;
    }
}

/**
 * Attempt to parse the given string as a string of balanced parentheses.
 * If the parse succeeds, return the parse tree, else return FAILED (NULL).
 */
TREE parse(char* input) {
    nextTerminal = input;
    TREE parseTree = B();
    if (parseTree != NULL && lookahead('\0')) {
	return parseTree;
    } else {
	return FAILED;
    }
}

int main()
{
    parseTree = parse("()()"); /* in practice, a string of terminals would be read from input */
    printf("%p\n", parseTree); /* you need to pretty-print the parse tree */
}

TREE makeNode0(char x)
{
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t)
{
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

TREE B()
{
    if (!lookahead('(')) {
	// Use production 1
        return makeNode1('B', makeNode0('e'));
    } else {
	// Use production 2
        if (!match('(')) return FAILED;
	TREE firstB = B();
        if (firstB == NULL) return FAILED;
        if (!match(')')) return FAILED;
	TREE secondB = B();
        if (secondB == NULL) return FAILED;
	return makeNode4('B',
		   makeNode0('('),
		   firstB,
		   makeNode0(')'),
		   secondB);
    }
}
