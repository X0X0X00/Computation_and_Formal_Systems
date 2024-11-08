/*
 * string-extras.c
 * George Ferguson
 */
#include <stdbool.h>
#include <string.h>
#include "string-extras.h"

/**
 * Return true if the two given strings are equal, otherwise false.
 */
bool streq(char* s1, char* s2) {
    return strcmp(s1, s2) == 0;
}

/**
 * Return true if the given string is empty, otherwise false.
 */
bool strempty(char* s) {
    return (*s) == '\0';
}

