#include "stringarray.h"
///Construct a new string array
STRING_ARRAY* initStringArray()
{
    STRING_ARRAY* newArray = NULL;
    newArray = calloc(1,sizeof(STRING_ARRAY));
    if(newArray == NULL)
    {
        //printf("Error! New string array allocation error");
        return NULL;
    }

    newArray->length = 0;
    newArray->strings = calloc(STRINGARRAY_INITIAL_ALLOCATED_LENGTH,sizeof(char*));
    if(newArray->strings == NULL)
    {
        //printf("Error! New string array strings field allocation error!");
        free(newArray);
        return NULL;
    }
    newArray->allocatedLength = STRINGARRAY_INITIAL_ALLOCATED_LENGTH;
    return newArray;
}

///Dispose of string array
///@param stringArray Array to dispose of
void freeStringArray(STRING_ARRAY* stringArray)
{
    if(stringArray == NULL)
    {
        //printf("Error! Attempt to free a NULL string array!");
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
        //printf("WARNING: appendString: attempt to append string to a NULL pointed stringarray");
        return EINVAL;
    }

    if(inputString == NULL)
    {
        //printf("WARNING: appendString: attempt to append a NULL string to stringarray");
        return EINVAL;
    }

    if(strlen(inputString) > STRINGARRAY_MAX_STRING_LENGTH)
    {
        //printf("WARNING: appendString: appended string is length is bigger than limit! (Limit is %d)",STRINGARRAY_MAX_STRING_LENGTH);
        return EOVERFLOW;
    }

    char* newString = calloc(strlen(inputString)+1,sizeof(char));
    if(newString == NULL)
    {
        //printf("WARNING: appendString: error allocating stringarray string attempting to append a new string!");
        return ENOMEM;
    }

    if((*stringArray)->length == (*stringArray)->allocatedLength)
    {
        STRING_ARRAY* newStringArray = realloc(*stringArray,(*stringArray)->allocatedLength*2);
        if(newStringArray == NULL)
        {
            //printf("WARNING: appendString: error reallocating bigger stringarray attempting to append a new string!");
            return ENOMEM;
        }
        *stringArray = newStringArray;
        (*stringArray)->allocatedLength *= 2;
    }

    int result = strcpy_s(newString,strlen(inputString)+1,inputString);
    (*stringArray)->strings[(*stringArray)->length] = newString;
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
        //printf("WARNING: deleteStringAt: attempt to remove string from a NULL pointed stringarray!");
        return EINVAL;
    }

    if(index >= stringArray->length || index < 0)
    {
        //printf("WARNING: deleteStringAt: deletion index out of bounds!");
        return EINVAL;
    }

    if(stringArray->strings[index] == NULL)
    {
        //printf("WARNING: deleteStringAt: deletion index is in bounds, "
        //       "but string pointer is NULL, possible memory corruption!");
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

///Get a copy of string at index, leaving original intact
///@param index Target index string
///@param stringArray Stringarray from which the string is taken
///@note This function returns a malloc'ed copy of original string.
/// Modifications to returned string wont affect the original
const char* getStringAt(int index, STRING_ARRAY *stringArray) {
    if(stringArray == NULL)
    {
        //printf("WARNING: getStringAt: attempt to get string from a NULL pointed stringarray!");
        return NULL;
    }

    if(index >= stringArray->length || index < 0)
    {
        //printf("WARNING: getStringAt: get index out of bounds!");
        return NULL;
    }

    if(stringArray->strings[index] == NULL)
    {
        //printf("WARNING: getStringAt: get index is in bounds, "
        // "but string pointer is NULL, possible memory corruption!");
        return NULL;
    }

    char* newString = calloc(strlen(stringArray->strings[index])+1,sizeof(char));
    if(newString == NULL)
    {
        //printf("WARNING: getStringAt: error allocating stringarray output string attempting to get string!");
        return NULL;
    }
    strcpy_s(newString,strlen(stringArray->strings[index])+1,stringArray->strings[index]);

    return newString;
}
