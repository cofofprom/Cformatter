#include "namedvar.h"

NAMED_VAR* initNamedVar() {
    NAMED_VAR* newVar = calloc(1,sizeof(NAMED_VAR));

    if(newVar == NULL)
    {
        return NULL;
    }

    newVar->varName = calloc(NAMED_VAR_INIT_VAR_LENGTH, sizeof(char));
    newVar->allocatedNameLength = NAMED_VAR_INIT_VAR_LENGTH;

    if(newVar->varName == NULL)
    {
        free(newVar);
        return 0;
    }

    newVar->varType = noneVar;

    return newVar;
}

NAMED_VAR *initNamedVarInt(char* varName, int value) {
    if(varName == NULL)
    {
        return NULL;
    }
    NAMED_VAR* newVar = initNamedVar();

    if(newVar == NULL)
    {
        return NULL;
    }

    newVar->varType = integerVar;
    int nameLength = strlen(varName);
    if(nameLength > newVar->allocatedNameLength)
    {
        char* newVarName = realloc(newVar->varName, nameLength);
        if(newVarName == NULL)
        {
            freeNamedVar(newVar);
            return NULL;
        }
        free(newVar->varName);
        newVar->varName = newVarName;
    }
    int result = strcpy_s(newVar->varName,nameLength,varName);
    if(result != 0)
    {
        freeNamedVar(newVar);
        return NULL;
    }

    newVar->intValue = value;

    return newVar;
}

NAMED_VAR *initNamedVarFloat(char* varName, float value) {
    if(varName == NULL)
    {
        return NULL;
    }
    NAMED_VAR* newVar = initNamedVar();

    if(newVar == NULL)
    {
        return NULL;
    }

    newVar->varType = floatVar;
    int nameLength = strlen(varName);
    if(nameLength > newVar->allocatedNameLength)
    {
        char* newVarName = realloc(newVar->varName, nameLength);
        if(newVarName == NULL)
        {
            freeNamedVar(newVar);
            return NULL;
        }
        free(newVar->varName);
        newVar->varName = newVarName;
    }
    int result = strcpy_s(newVar->varName,nameLength,varName);
    if(result != 0)
    {
        freeNamedVar(newVar);
        return NULL;
    }

    newVar->floatValue = value;

    return newVar;
}

NAMED_VAR *initNamedVarDouble(char* varNamed, double value) {
    if(varName == NULL)
    {
        return NULL;
    }
    NAMED_VAR* newVar = initNamedVar();

    if(newVar == NULL)
    {
        return NULL;
    }

    newVar->varType = doubleVar;
    int nameLength = strlen(varName);
    if(nameLength > newVar->allocatedNameLength)
    {
        char* newVarName = realloc(newVar->varName, nameLength);
        if(newVarName == NULL)
        {
            freeNamedVar(newVar);
            return NULL;
        }
        free(newVar->varName);
        newVar->varName = newVarName;
    }
    int result = strcpy_s(newVar->varName,nameLength,varName);
    if(result != 0)
    {
        freeNamedVar(newVar);
        return NULL;
    }

    newVar->doubleValue = doubleVar;

    return newVar;
}

void freeNamedVar(NAMED_VAR *var) {
    if(var == NULL)
    {
        return;
    }

    if(var->varName != NULL)
    {
        free(var->varName);
    }

    free(var);

    return;
}
