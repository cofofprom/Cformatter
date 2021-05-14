#ifndef CFORMATTER_FINDRECURSION_H
#define CFORMATTER_FINDRECURSION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../Formatter/Formatter.h"
#include "RemovePreprocessors.h"

#define SIZE 100
#define MAX_SIZE 250
#define MAX_VARIABLE_SIZE 500
#define STRING_SIZE 50
#define bool int
#define true 1
#define false 0
#define NumberOfStdTypes 39

typedef struct UserTypes
{
    char Name[SIZE];
    int NameSize;
    int isUsed;
} UserType;

typedef struct UserFunc
{
    char Name[SIZE];
    bool isUsed;
} UserFunction;

int findTypeInList(char *NameOfType);

int isNameOfSavedType(char *Code, int idx);

bool isNameOfUserType(char *Code, int idx);

void addAllTypes(char *Code);

bool isFunction(char *Code, int idx);

void addAllFunctions(char *Code);

bool isFunctionInCode(char *Code, int idx);

bool checkList(char (*OrderOfFunctionCalls)[SIZE], char *CurrentFunction, int ptr);

bool findFunc(char (*OrderOfFunctionCalls)[SIZE], char *CurrentFunction, char *Code, int ptr);

void checkFunctionsForRecursion(char *RawCode);

void printUnusedFunctions(char *Code);

void DEBUG_FUNC(char *RawCode);

#endif //CFORMATTER_FINDRECURSION_H