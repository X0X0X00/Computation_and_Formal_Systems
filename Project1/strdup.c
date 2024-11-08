/*
 * File: strdup.c
 * Creator: George Ferguson
 * Created: Tue Aug  8 10:05:19 2017
 *
 * Incredibly, strdup is in string.h but not part of ANSI standard C.
 */

#include <stdlib.h>
#include "strdup.h"

/**
 * From strdup(3): allocates sufficient memory for a copy of the
 * string s, does the copy, and returns a pointer to it.
 */
char*
strdup(const char* s) {
    if (s == NULL) {
	return NULL;
    }
    char* t = malloc(strlen(s)+1);
    strcpy(t, s);
    return t;
}

