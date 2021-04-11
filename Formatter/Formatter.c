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
    char* clean = deleteFormat(code);
    printf("%s", clean);
    clean = replaceWord(clean, "if(", "if (", 0);
    clean = replaceWord(clean, "while(", "while (", 0);
    clean = replaceWord(clean, "for(", "for (", 0);
    bool preprocFlag = false;
    bool preprocBalance = 0;
    int nesting = 0;
    for(int i = 0; i < strlen(clean); i++)
    {
        // preprocessor format
        if(clean[i] == '#' && (clean[i+1] == 'i')) preprocFlag = true;
        if(preprocFlag && clean[i] == '"' && preprocBalance == 0) preprocBalance++;
        else if(preprocFlag && (clean[i] == '>' || preprocBalance == 1 && clean[i] == '"'))
        {
            clean = replaceOneWord(clean, (char[]) { clean[i], 0}, (char[]){clean[i], '\n', 0}, i);
            preprocFlag = false;
            preprocBalance = 0;
        }
        // nesting format
        if(clean[i] == '{')
        {
            nesting++;
            char nestingNewLine[10] = {'{', '\n', 0};
            for(int j = 2; j - 2 < nesting; j++) nestingNewLine[j] = '\t';
            clean = replaceOneWord(clean, "{", nestingNewLine, i);
        }
        if(clean[i] == '}') {
            char nestingNewLine[10] = {'}', '\n', 0};
            for(int j = 2; j-2 < nesting - 1; j++) nestingNewLine[j] = '\t';
            nesting--;
            clean = replaceOneWord(clean, "}", nestingNewLine, i);
        }
        if (clean[i] == ';') {
            char nestingNewLine[10] = {';', '\n', 0};
            if(clean[i+1] != '}')
                for(int j = 2; j-2 < nesting; j++) nestingNewLine[j] = '\t';
            else
                for(int j = 2; j-2 < nesting - 1; j++) nestingNewLine[j] = '\t';

            clean = replaceOneWord(clean, ";", nestingNewLine, i);
        }
    }
    return clean;
}

char *deleteFormat(char *code) {
    char* result = (char*)calloc(strlen(code), 1);
    char* temp = (char*)calloc(strlen(code), 1);
    strcpy(temp, code);
    char spaces[100] = { 0 };
    int spsz = 0;
    int ptr = 0;
    bool flag = 0;
    for(int i = 0; i < strlen(temp); i++) {
        if (temp[i] == '"' && flag == 0) flag = 1;
        else if (temp[i] == '"' && flag == 1) flag = 0;
        if (temp[i] == '\'' && flag == 0) flag = 2;
        else if (temp[i] == '\'' && flag == 2) flag = 0;
        if(temp[i] == ' ' && (temp[i + 1] == ' ' || spsz > 0))
            spaces[spsz++] = ' ';
        if(temp[i] != ' ' && spsz > 0)
        {
            i -= spsz;
            temp = replaceWord(temp, spaces, "\t", i - spsz);
            for(int j = 0; j < spsz; j++) spaces[j] = 0;
            spsz = 0;
            continue;
        }
        if (!flag && temp[i] != '\t' && temp[i] != '\n' && temp[i] != '\r' && spsz == 0) {
            if(temp[i] == ' ' && (temp[i - 1] == ';' || temp[i - 1] == '{' || temp[i-1] == '}')) continue;
            result[ptr++] = temp[i];
        }
        else if (flag) result[ptr++] = temp[i];
    }
    free(temp);
    return result;
}
