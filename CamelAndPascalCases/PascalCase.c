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
                    if (isNameOfUserType(inner, i))
                    {
                        int id = i;
                        while (inner[id] != ' ' && inner[id] != '\r' && inner[id] != '\t' && inner[id] != '\n') id++;
                        id--;
                        while (inner[id] != ' ' && inner[id] != '\r' && inner[id] != '\t' && inner[id] != '\n') id--;
                        id++;
                        inner[id] = (char) toupper(inner[id]);
                        for (int j = i; inner[j] != '\n' && j < strlen(inner); j++) i = j;
                    }
                    else if (isVariable(inner, i))
                    {
                        int id = i, SpaceCounter = 0;
                        while (SpaceCounter != 2)
                        {
                            if (inner[id] == ' ' || inner[id] == '\n')
                            {
                                SpaceCounter++;
                            }
                            id++;
                        }
                        id--;
                        while (inner[id] != ' ') id--;
                        id++;
                        inner[id] = (char) tolower(inner[id]);
                        for (int j = i; inner[j] != '\n' && j < strlen(inner); j++) i = j;
                    }
                    else if (isTypedef(inner, i))
                    {
                        inner[isTypedef(inner, i)] = (char) toupper((inner[isTypedef(inner, i)]));
                        for (int j = i; inner[j] != '\n' && j < strlen(inner); j++) i = j;
                    }
                    else if (isFunction(inner, i) || isFunctionInCode(inner, i))
                    {
                        int id = i;
                        while (inner[id] != '(') id++;
                        id--;
                        while (inner[id] != ' ' && inner[id] != '\r' && inner[id] != '\t' && inner[id] != '\n') id--;
                        id++;
                        if (inner[id] != 'm' && inner[id + 1] != 'a' && inner[id + 2] != 'i' &&
                            inner[id + 3] != 'n')
                            inner[id] = (char) toupper(inner[id]);
                        for (int j = i; inner[j] != '\n' && j < strlen(inner); j++) i = j;
                    }
                }
            }
        }
    }
    return inner;
}