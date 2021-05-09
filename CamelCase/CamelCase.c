#include "CamelCase.h"
#include <string.h>
#include "../StringTools/StringTools.h"

#define bool int
#define true 1
#define false 0

char* replaceWithCamelCase(char* inputString) {

    bool kavy = false;
    char* inner = (char*)calloc(strlen(inputString), 1);
    strcpy(inner, inputString);
    for(int i = 0; i < strlen(inner); i++) {

        if (inner[i] == '"' && kavy) kavy = false;
        if (inner[i] == '"' && !kavy) kavy = true;

        if (!kavy) {

            if(inner[i] == '_') {
                for(int j = i; j < strlen(inner) - 1; j++) inner[j] = inner[j+1];
                inner[strlen(inner) - 1] = 0;
                if(inner[i] >= 'a' && inner[i] <= 'z') inner[i] -= 32;
            }

        }

    }
    return inner;
}