#ifndef CFORMATTER_CHECKVARIABLES_H
#define CFORMATTER_CHECKVARIABLES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Formatter/Formatter.h"
#include "RemovePreprocessors.h"
#include "../StringTools/StringTools.h"
#include "FindRecursion.h"

#define SIZE 100
#define MAX_SIZE 250
#define MAX_VARIABLE_SIZE 500
#define STRING_SIZE 50
#define bool int
#define true 1
#define false 0
#define NumberOfStdTypes 37
#define SIZE_OF_CODE 1024*10

typedef struct Variables
{
    char Name[SIZE];
    char Value[SIZE];
} Variables;

int findVariableInList(char *NameOfVariable);

bool isVariable(char *Code, int idx);

void getVariable(char *Code, int idx);

void findVariables(char *Code);

void printVariables(char *RawCode);

void DEBUG_VARS(char *RawCode);

void checkName(char *RawCode);

#endif //CFORMATTER_CHECKVARIABLES_H