/*
 * File: strdup.c
 * Creator: George Ferguson
 * Created: Tue Nov 29 14:47:55 2022
 */
#include <stdlib.h>
#include <string.h>
#include "strdup.h"

/**
 * strdup is not in the C99 standard library, although it is in the POSIX
 * spec and hence available on most Unix/Linux platforms.
 * It is available as _strdup on windows FWIW.
 * Returns NULL if malloc fails (with errno == ENOMEM).
 */
char *STRDUP(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p) {
	strcpy(p, s);
    }
    return p;
}

