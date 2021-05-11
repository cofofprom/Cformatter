#ifndef CFORMATTER_HALTTESTER_H
#define CFORMATTER_HALTTESTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include "namedvarcondition.h"
#include "..\regex\regex.h"

typedef enum loop_types_enum {ForLoop, WhileLoop, DoWhileLoop} LOOP_TYPE;

struct loop_struct
{
    LOOP_TYPE loopType;
    NAMED_VAR init_value
    NAMED_VAR

};

#endif //CFORMATTER_HALTTESTER_H
