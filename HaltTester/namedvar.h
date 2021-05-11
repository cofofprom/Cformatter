#ifndef CFORMATTER_NAMEDVAR_H
#define CFORMATTER_NAMEDVAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

#define NAMED_VAR_INIT_VAR_LENGTH 100

typedef enum var_types_enum {noneVar,integerVar, floatVar, doubleVar} VARIABLE_TYPE;

typedef struct named_var_struct
{
    char* varName;
    int allocatedNameLength;
    VARIABLE_TYPE varType;
    int intValue;
    float floatValue;
    double doubleValue;
} NAMED_VAR;

NAMED_VAR* initNamedVar();
NAMED_VAR* initNamedVarInt(char* varName, int value);
NAMED_VAR* initNamedVarFloat(char* varName, float value);
NAMED_VAR* initNamedVarDouble(char* varNamed, double value);

void freeNamedVar(NAMED_VAR* var);

#endif //CFORMATTER_NAMEDVAR_H
