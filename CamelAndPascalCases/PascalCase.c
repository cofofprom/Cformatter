#include "PascalCase.h"

char *replaceWithPascalCase(char *inputString)
{
    bool kavy = false;
    bool header = false;
    char *inner = replaceWithCamelCase(inputString);
    for (int i = 0; i < strlen(inner); i++)
    {
        if (inner[i] == '"') kavy = !kavy;
        if (!kavy)
        {
            if (inner[i] == '#') header = true;
            if (inner[i] == '\n' && header) header = false;
            if (!header)
            {
                if (inner[i] != ' ' && inner[i] != '\n' && inner[i] != '\t' && inner[i] != ';')
                {
                    if (isFunctionInCode(inner, i) || isFunction(inner, i))
                    {
                        int id = i;
                        while (inner[id] != '(') id++;
                        while (inner[id] != ' ' && inner[id] != '\t' && inner[id] != '\n') id--;
                        id++;
                        inner[id] = (char) tolower(inner[id]);
                    }
                }
            }
        }
    }
    return inner;
}