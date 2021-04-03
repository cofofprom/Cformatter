#ifndef CFORMATTER_STRINGTOOLS_H

#define CFORMATTER_STRINGTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replaceWord(char *s, const char *oldW, const char *newW, int ptr);

char *replaceOneWord(char *s, const char *oldW, const char *newW, int ptr);

int countSubstring(char *String, char *Substring);

#endif //CFORMATTER_STRINGTOOLS_H
