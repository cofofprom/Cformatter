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
    newArray->strings = calloc(STRINGARRAY_INITIAL_ALLOCATED_LENGTH,sizeof(char*));
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

///Append string to a provided array, reallocates it if it runs out of space
///@param inputString String to be appended
///@param stringArray array to append to
///@return 0 on success, error code from errono.h on error. Does not update errno!
int appendString(char *inputString, STRING_ARRAY** stringArray) {
    if(stringArray == NULL)
    {
        printf("WARNING: appendString: attempt to append string to a NULL pointed stringarray");
        return EINVAL;
    }

    if(inputString == NULL)
    {
        printf("WARNING: appendString: attempt to append a NULL string to stringarray");
        return EINVAL;
    }

    if((*stringArray)->length == (*stringArray)->allocatedLength)
    {
        STRING_ARRAY* newStringArray = realloc(*stringArray,(*stringArray)->allocatedLength*2);
        if(newStringArray == NULL)
        {
            printf("WARNING: appendString: error reallocating bigger stringarray attempting to append a new string!");
            return ENOMEM;
        }
        *stringArray = newStringArray;
        (*stringArray)->allocatedLength *= 2;
    }

    (*stringArray)->strings[(*stringArray)->length] = inputString;
    (*stringArray)->length++;
    return 0;
}

///Remove string at specified index
///@param index index to remove string at
///@param array to remove from
///@return 0 on success, error code from errono.h on error. Does not update errno!
int deleteStringAt(int index, STRING_ARRAY* stringArray) {
    if(stringArray == NULL)
    {
        printf("WARNING: deleteStringAt: attempt to remove string from a NULL pointed stringarray!");
        return EINVAL;
    }

    if(index >= stringArray->length || index < 0)
    {
        printf("WARNING: deleteStringAt: deletion index out of bounds!");
        return EINVAL;
    }

    if(stringArray->strings[index] == NULL)
    {
        printf("WARNING: deleteStringAt: deletion index is in bounds, "
               "but string pointer is NULL, possible memory corruption!");
        return EFAULT;
    }

    //Free string at requested index
    free(stringArray->strings[index]);

    //Move all pointers above the removed one to remove the gap
    while(index < stringArray->length - 1)
    {
        stringArray->strings[index] = stringArray->strings[index + 1];
        index++;
    }

    stringArray->length--;

    return 0;
}

///Get string at index, and check it for NULL pointer at the same time!
const char* getStringAt(int index, STRING_ARRAY *stringArray) {
    if(stringArray == NULL)
    {
        printf("WARNING: getStringAt: attempt to get string from a NULL pointed stringarray!");
        return EINVAL;
    }

    if(index >= stringArray->length || index < 0)
    {
        printf("WARNING: getStringAt: get index out of bounds!");
        return EINVAL;
    }

    if(stringArray->strings[index] == NULL)
    {
        printf("WARNING: getStringAt: get index is in bounds, "
               "but string pointer is NULL, possible memory corruption!");
        return EFAULT;
    }

    return stringArray->strings[index];
}
