#ifndef CFORMATTER_PASCALCASE_H
#define CFORMATTER_PASCALCASE_H

#include <string.h>
#include <ctype.h>
#include "../StringTools/StringTools.h"
#include "../CheckVariablesAndFunctions/CheckFunctions.h"
#include "CamelCase.h"
#include "../CheckVariablesAndFunctions/CheckVariables.h"

char* replaceWithPascalCase(char* inputString);

#endif //CFORMATTER_PASCALCASE_H