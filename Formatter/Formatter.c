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

char* contextReplacer(char* code)
{
    char* result = (char*)calloc(strlen(code) + 1, 1);
    strcpy(result, code);
    bool kavy = 0;
    bool forFlag = false;
    int forBalance = 0;
    for(int i = 0; i < strlen(result); i++) {
        if(result[i] == '"') kavy = !kavy; // checking if we can replace things

        if(!kavy)
        {
            if(result[i] == 'i' && result[i + 1] == 'f' && result[i + 2] == '(') // if statement replacing
                result = replaceOneWord(result, "if(", "if (", i);

            if(result[i] == 'w' && result[i+1] == 'h' && result[i+2] == 'i' &&
            result[i+3] == 'l' && result[i+4] == 'e' && result[i+5] == '(')
                result = replaceOneWord(result, "while(", "while (", i);

            if(result[i] == 'f' && result[i+1] == 'o' && result[i+2] == 'r')
            {
                forFlag = true;
                if(result[i + 3] == '(') result = replaceOneWord(result, "for(", "for (", i);
                i += 4;
            }
            if(forFlag && result[i] == '(') forBalance++;
            if(forFlag && result[i] == ')') forBalance--;
            if(forFlag && forBalance == 0) forFlag = false;

            if(result[i] == ';' && result[i + 1] == ' ' && !forFlag)
                result = replaceOneWord(result, "; ", ";", i);
            if(result[i] == ';' && result[i + 1] != ' ' && forFlag)
                result = replaceOneWord(result, ";", "; ", i);

            if(result[i] == '}' && result[i+1] == ' ') result = replaceOneWord(result, "} ", "}", i);
            if(result[i] == '{' && result[i+1] == ' ') result = replaceOneWord(result, "{ ", "{", i);
            if(result[i] == ')' && result[i+1] == '{') result = replaceOneWord(result, "){", ") {", i);
            if(result[i] == '=' && result[i+1] == '=') {
                result = replaceOneWord(result, "==", " == ", i);
                i+=2;
            }
            if(result[i] == '=' && result[i+1] != '=' && result[i-1] != '=' && result[i-1] != '<' && result[i-1] != '>') {
                result = replaceOneWord(result, "=", " = ", i);
                i+=2;
            }
            if(result[i] == '<' && result[i+1] == '=') {
                result = replaceOneWord(result, "<=", " <= ", i);
                i+=2;
            }
            if(result[i] == '<' && result[i+1] != '=') {
                result = replaceOneWord(result, "<", " < ", i);
                i+=2;
            }
            if(result[i] == '>' && result[i+1] == '=') {
                result = replaceOneWord(result, ">=", " >= ", i);
                i+=2;
            }
            if(result[i] == '>' && result[i+1] != '=') {
                result = replaceOneWord(result, ">", " > ", i);
                i+=2;
            }
            if(result[i] == '+' && result[i+1] == '=') {
                result = replaceOneWord(result, "+=", " += ", i);
                i+=2;
            }
            if(result[i] == '+' && result[i+1] != '=' && result[i + 1] != '+' && result[i - 1] != '+') {
                result = replaceOneWord(result, "+", " + ", i);
                i+=2;
            }
            if(result[i] == '-' && result[i+1] == '=') {
                result = replaceOneWord(result, "-=", " -= ", i);
                i+=2;
            }
            if(result[i] == '-' && result[i+1] != '=' && result[i + 1] != '-' && result[i - 1] != '-') {
                result = replaceOneWord(result, "-", " - ", i);
                i+=2;
            }
            if(result[i] == '*' && result[i+1] == '=') {
                result = replaceOneWord(result, "*=", " *= ", i);
                i+=2;
            }
            if(result[i] == '*' && result[i+1] != '=') {
                result = replaceOneWord(result, "*", " * ", i);
                i+=2;
            }
            if(result[i] == '/' && result[i+1] == '=') {
                result = replaceOneWord(result, "/=", " /= ", i);
                i+=2;
            }
            if(result[i] == '/' && result[i+1] != '=') {
                result = replaceOneWord(result, "/", " / ", i);
                i+=2;
            }
        }
    }
    return result;
}

char* formatCode(char *code) {
    char* clean = deleteFormat(code);
    //printf("%s", clean);
    /*clean = replaceWord(clean, "if(", "if (", 0);
    clean = replaceWord(clean, "while(", "while (", 0);
    clean = replaceWord(clean, "for(", "for (", 0);
    clean = replaceWord(clean, "; ", ";", 0);
    clean = replaceWord(clean, "{ ", "{", 0);
    clean = replaceWord(clean, "} ", "}", 0);
    clean = replaceWord(clean, "){", ") {", 0);
    clean = replaceWord(clean, "==", " == ", 0);
    clean = replaceWord(clean, "<=", " <= ", 0);
    clean = replaceWord(clean, ">=", " >= ", 0);*/
    //clean = replaceWord(clean, "+", " + ", 0);
    //clean = replaceWord(clean, "-", " - ", 0);
    clean = contextReplacer(clean);
    clean = deleteFormat(clean);
    printf("%s", clean);
    bool preprocFlag = false;
    bool preprocBalance = 0;
    int nesting = 0;
    for(int i = 0; i < strlen(clean); i++)
    {
        // preprocessor format
        /*if(clean[i] == '#' && (clean[i+1] == 'i')) preprocFlag = true;
        if(preprocFlag && clean[i] == '"' && preprocBalance == 0) preprocBalance++;
        else if(preprocFlag && (clean[i] == '>' || preprocBalance == 1 && clean[i] == '"'))
        {
            clean = replaceOneWord(clean, (char[]) { clean[i], 0}, (char[]){clean[i], '\n', 0}, i);
            preprocFlag = false;
            preprocBalance = 0;
        }*/
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
            if(clean[i+1] != '}') {
                for (int j = 2; j - 2 < nesting - 1; j++) nestingNewLine[j] = '\t';
                nesting--;
                clean = replaceOneWord(clean, "}", nestingNewLine, i);
            }
            else
            {
                for (int j = 2; j - 2 < nesting - 2; j++) nestingNewLine[j] = '\t';
                nesting--;
                clean = replaceOneWord(clean, "}", nestingNewLine, i);
            }
        }
        if (clean[i] == ';' && clean[i+1] != ' ') {
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
    char* result = (char*)calloc(strlen(code) + 1, 1);
    char* temp = (char*)calloc(strlen(code) + 1, 1);
    strcpy(temp, code);
    char spaces[100] = { 0 };
    int spsz = 0;
    int ptr = 0;
    bool flag = 0;
    bool macroFlag = 0;
    for(int i = 0; i < strlen(temp); i++) {
        if (temp[i] == '"' && flag == 0) flag = 1;
        else if (temp[i] == '"' && flag == 1) flag = 0;
        if (temp[i] == '\'' && flag == 0) flag = 2;
        else if (temp[i] == '\'' && flag == 2) flag = 0;
        if(!flag && temp[i] == '#') macroFlag = 1;
        if(macroFlag && temp[i] == '\n') macroFlag = 0;
        if(temp[i] == ' ' && (temp[i + 1] == ' ' || spsz > 0))
            spaces[spsz++] = ' ';
        if(temp[i] != ' ' && spsz > 0)
        {
            i -= spsz;
            temp = replaceWord(temp, spaces, " ", i - spsz);
            for(int j = 0; j < spsz; j++) spaces[j] = 0;
            spsz = 0;
            continue;
        }
        if (!flag && !macroFlag && temp[i] != '\t' && temp[i] != '\n' && temp[i] != '\r' && spsz == 0) {
            if(temp[i] == ' ' && (temp[i - 1] == ';' || temp[i - 1] == '{' || temp[i-1] == '}' || temp[i - 1] == '(' || temp[i + 1] == ')')) continue;
            result[ptr++] = temp[i];
        }
        else if (flag || macroFlag) result[ptr++] = temp[i];
    }
    //free(temp);
    return result;
}
