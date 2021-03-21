#ifndef C_FORMATTER_STRINGARRAY_H
#define C_FORMATTER_STRINGARRAY_H

#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define STRINGARRAY_MAX_ALLOCATED_LENGTH 1000
#define STRINGARRAY_MAX_STRING_LENGTH 500

typedef struct string_array_struct STRING_ARRAY;

STRING_ARRAY* initStringArray();
void freeStringArray(STRING_ARRAY* stringArray);

int appendString(char* inputString, STRING_ARRAY stringArray);
int insertString(char* inputString,int index, STRING_ARRAY stringArray,);

int deleteStringAt(int index, STRING_ARRAY stringArray);

#endif //C_FORMATTER_STRINGARRAY_H
