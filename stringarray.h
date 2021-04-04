#ifndef C_FORMATTER_STRINGARRAY_H
#define C_FORMATTER_STRINGARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define STRINGARRAY_MAX_ALLOCATED_LENGTH 1000
#define STRINGARRAY_MAX_STRING_LENGTH 500
#define STRINGARRAY_INITIAL_ALLOCATED_LENGTH 50

struct string_array_struct
{
    int length;
    int allocatedLength;
    char** strings;
};

typedef struct string_array_struct STRING_ARRAY;

STRING_ARRAY* initStringArray();
void freeStringArray(STRING_ARRAY* stringArray);

int appendString(char* inputString, STRING_ARRAY stringArray);

int insertString(char* inputString, int index, STRING_ARRAY stringArray);

int deleteStringAt(int index, STRING_ARRAY stringArray);

#endif //C_FORMATTER_STRINGARRAY_H
