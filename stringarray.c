#include "stringarray.h"

STRING_ARRAY* initStringArray()
{
    STRING_ARRAY* newArray = NULL;
    newArray = calloc(1,sizeof(STRING_ARRAY));
    if(newArray == NULL)
    {
        printf("Error! New string array allocation error");
        return NULL;
    }

    newArray->length = 0;
    newArray->strings = calloc(STRINGARRAY_INITIAL_ALLOCATED_LENGTH,sizeof(char));
    if(newArray->strings = NULL)
    {
        printf("Error! New string array strings field allocation error!");
        free(newArray);
        return NULL;
    }
    newArray->allocatedLength = STRINGARRAY_INITIAL_ALLOCATED_LENGTH;
    return newArray;
}

void freeStringArray(STRING_ARRAY* stringArray)
{
    if(stringArray == NULL)
    {
        printf("Error! Attempt to free a NULL string array!");
        return;
    }
    for(int i = 0; i < stringArray->length; i++)
    {
        free(stringArray->strings[i]);
    }

    free(stringArray->strings);
    free(stringArray);
}