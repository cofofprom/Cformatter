#ifndef CFORMATTER_PASCALCASE_H
#define CFORMATTER_PASCALCASE_H

#include <string.h>
#include <ctype.h>
#include "../StringTools/StringTools.h"
#include "../CheckVariablesAndFunctions/FindRecursion.h"
#include "CamelCase.h"

char* replaceWithPascalCase(char* inputString);

#endif //CFORMATTER_PASCALCASE_H