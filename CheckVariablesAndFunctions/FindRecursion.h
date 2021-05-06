#ifndef CFORMATTER_FINDRECURSION_H
#define CFORMATTER_FINDRECURSION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Formatter/Formatter.h"

#define SIZE 100
#define MAX_SIZE 250
#define MAX_VARIABLE_SIZE 500
#define STRING_SIZE 50
#define bool int
#define true 1
#define false 0
#define NumberOfStdTypes 37

typedef struct UserType
{
    char Name[SIZE];
    int NameSize;
} UserType;


bool isNameOfSavedType(char *Code, int idx);

void addAllTypes(char *FileName);

#endif //CFORMATTER_FINDRECURSION_H