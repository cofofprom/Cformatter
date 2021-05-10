#include "PascalCase.h"

char *replaceWithPascalCase(char *inputString)
{
    char *inner = replaceWithCamelCase(inputString);
    for (int i = 0; i < strlen(inner); i++)
    {
        if (inner[i] != ' ' && inner[i] != '\n' && inner[i] != '\t' && inner[i] != ';')
        {
            if (isFunction(inner, i))
            {
                int id = i;
                while (inner[id] != '(') id++;
                while (inner[id] != ' ') id--;
                id++;
                inner[id] = (char)tolower(inner[id]);
            }
        }
    }
    return inner;
}