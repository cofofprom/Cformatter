#include "Formatter.h"
#include <stdio.h>
#include <stdlib.h>
#include "../StringTools/StringTools.h"

#define bool int
#define true 1
#define false 0

char* readCode(const char* filename)
{
    char* content = (char*)calloc(1024*10, 1);
    FILE* desc = fopen(filename, "rb");
    fread((void*)content, 1, 1024*10, desc);
    return content;
}

char* formatCode(char *code) {
    char* formatted = (char*)calloc(10*1024, 1);
    strcpy(formatted, replaceWord(code, "    ", "\t", 0));
    strcpy(formatted, replaceWord(formatted, "if(", "if (", 0));
    strcpy(formatted, replaceWord(formatted, "while(", "while (", 0));
    strcpy(formatted, replaceWord(formatted, "for(", "for (", 0));
    bool constrFlag = false;
    int brackets = 0;
    for(int i = 0; i < strlen(formatted); i++)
    {
        char curr = code[i];
        if(code[i] == 'i' && code[i + 1] == 'f')
        {
            constrFlag = true;
            i += 2;
            curr = code[i];
        }

        if(constrFlag && code[i] == '(') brackets++;
        if(constrFlag && code[i] == ')') brackets--;
        if(constrFlag && brackets == 0) {
            if(code[i] == ')' && code[i+1] != '\n') {
                strcpy(formatted, replaceOneWord(formatted, ") ", ")\n", i));
                constrFlag = false;
            }
        }
    }
    return formatted;
}
