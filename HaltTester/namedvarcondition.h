#ifndef CFORMATTER_NAMEDVARCONDITION_H
#define CFORMATTER_NAMEDVARCONDITION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include "namedvar.h"

typedef enum condition_types {lessThan,biggerThan,equalTo,lessThanorEqual,biggerThanorEqual,notEqual} CONDITION_TYPE;

typedef struct named_var_condition_struct
{
    CONDITION_TYPE conditionType;
    NAMED_VAR* leftSide;
    NAMED_VAR* rightSide;
} NAMED_VAR_CONDITION;

NAMED_VAR_CONDITION* initNamedVarCond();
NAMED_VAR_CONDITION* initNamedVarCondFromParams(NAMED_VAR* leftOperand,NAMED_VAR* rightOperand, CONDITION_TYPE condType);

void freeNamedVarCondition(NAMED_VAR_CONDITION* namedVarCondition);

int evaluateCondition(NAMED_VAR_CONDITION* condition);

#endif //CFORMATTER_NAMEDVARCONDITION_H
