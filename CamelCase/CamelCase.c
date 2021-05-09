#include "CamelCase.h"
#include <string.h>
#include "../StringTools/StringTools.h"

#define bool int
#define true 1
#define false 0

char* replaceWithCamelCase(char* inputString) {

    bool kavy = false;
    int firstCharIndex = -1;
    char* inner = (char*)calloc(strlen(inputString), 1);
    strcpy(inner, inputString);
    for(int i = 0; i < strlen(inner); i++) {

        if (inner[i] == '"') kavy = !kavy;

        if (!kavy) {
            if(inner[i] == '_') {
                for(int j = i; j < strlen(inner) - 1; j++) inner[j] = inner[j+1];
                inner[strlen(inner) - 1] = 0;
                if(inner[i] >= 'a' && inner[i] <= 'z') inner[i] -= 32;
            }
            if(inner[i] >= 'a' && inner[i] <= 'z' && (inner[i-1] == ' ' || inner[i-1] == '\n' || inner[i-1] == '\t')) firstCharIndex = i;
            if(inner[i] == '(' && inner[i - 1] >= 'a' && inner[i - 1] <= 'z') inner[firstCharIndex] -= 32;
        }
    }
    return inner;
}