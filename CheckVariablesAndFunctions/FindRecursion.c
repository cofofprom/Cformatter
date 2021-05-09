#include "FindRecursion.h"

UserType ListOfUserTypes[MAX_SIZE] = {0};
char ListOfFunctions[SIZE][SIZE] = {0};
int NumberOfSavedTypes = 0, FuncPtr = 0;

int findTypeInList(char *NameOfType)
{
    for (int i = 0; i < NumberOfStdTypes; i++)
    {
        if (strcmp(ListOfUserTypes[i].Name, NameOfType) == 0) return i;
    }
    return -1;
}

int isNameOfSavedType(char *Code,
                      int idx)     //To find out if it is the beginning of any saved type and to return the length of it
{
    char Name[STRING_SIZE] = {0};
    int ptr = 0;
    char *NamesOfStdTypes[NumberOfStdTypes] = {"char", "signed char", "unsigned char", "short", "short int",
                                               "signed short", "signed short int", "unsigned short",
                                               "unsigned short int", "int", "signed", "signed int", "unsigned",
                                               "unsigned int", "long", "long int", "signed long", "signed long int",
                                               "unsigned long", "unsigned long int", "long long", "long long int",
                                               "signed long long", "signed long long int", "unsigned long long",
                                               "unsigned long long int", "float", "double", "long double", "_Bool",
                                               "size_t", "float_t", "double_t", "float _Complex", "double _Complex",
                                               "long double _Complex", "FILE"};
    for (int i = idx; i < strlen(Code); i++)
    {
        if ((Code[i] >= 'a' && Code[i] <= 'z') || (Code[i] >= 'A' && Code[i] <= 'Z') || Code[i] == '_')
        {
            Name[ptr] = Code[i];
            ptr++;
        }
        else break;
    }
    for (int i = 0; i < NumberOfStdTypes; i++)
    {
        if (strlen(NamesOfStdTypes[i]) == strlen(Name) && !strcmp(Name, NamesOfStdTypes[i])) return strlen(Name);
        else continue;
    }
    for (int i = 0; i < NumberOfSavedTypes; i++)
    {
        if (strlen(Name) == ListOfUserTypes[i].NameSize && !strcmp(Name, ListOfUserTypes[i].Name)) return strlen(Name);
        else continue;
    }
    return false;
}

void addAllTypes(char *Code)
{
    char StructString[] = "struct", str[MAX_SIZE] = {0};
    bool isType = false;
    for (int i = 0; i < strlen(Code) - strlen(StructString); i++)
    {
        if (Code[i] == 's' && Code[i - 1] == '\t')
        {
            bool flag = true;
            for (int j = 0; j < strlen(StructString) && i + j < strlen(Code); j++)
            {
                if (StructString[j] != Code[i + j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                int CountBrackets = 0, id = i, StructPtr = 0, TypedefPtr = 0;
                char NameOfStruct[SIZE] = {0}, TypedefName[SIZE] = {0};
                for (int j = i; Code[j] != '\n' && Code[j] != '{'; j++)
                {
                    if (Code[j] != ' ')
                    {
                        NameOfStruct[StructPtr] = Code[j];
                        StructPtr++;
                    }
                }
                for (int j = i; j < strlen(Code); j++)
                {
                    if (Code[j] == '{') CountBrackets++;
                    if (Code[j] == '}') CountBrackets--;
                    if (CountBrackets == 0)
                    {
                        id = j;
                        break;
                    }
                }
                for (int j = id; j < strlen(Code) && Code[j] != ';'; j++)
                {
                    if (Code[j] != ' ')
                    {
                        TypedefName[TypedefPtr] = Code[j];
                        TypedefPtr++;
                    }
                }
                if (TypedefPtr != 0) strcpy(NameOfStruct, TypedefName);
                strcpy(ListOfUserTypes[NumberOfSavedTypes].Name, NameOfStruct);
                ListOfUserTypes[NumberOfSavedTypes].NameSize = (int) strlen(ListOfUserTypes[NumberOfSavedTypes].Name);
                NumberOfSavedTypes++;
            }
            else continue;
        }
    }
}

bool isFunction(char *Code, int idx)
{
    if (isNameOfSavedType(Code, idx))
    {
        bool flag = false, notMacro = false;
        for (int i = idx; i < strlen(Code) && Code[i] != '\n'; i++)
        {
            if (Code[i] == ';' || Code[i] == '=')
            {
                flag = false;
                break;
            }
            if (Code[i] == '(')
            {
                flag = true;
                break;
            }
        }
        return flag;
    }
    else return false;
}

void addAllFunctions(char *Code)
{
    addAllTypes(Code);
    for (int i = 0; i < strlen(Code); i++)
    {
        if (Code[i] != ' ' && Code[i] != '\n' && Code[i] != ';' && Code[i] != '\t')
        {
            if (isNameOfSavedType(Code, i))
            {
                int shift = isNameOfSavedType(Code, i), ptr = 0;
                char NameOfFunction[SIZE] = {0};
                for (int j = i + shift; Code[j] != '('; j++)
                {
                    if (Code[j] != ' ')
                    {
                        NameOfFunction[ptr] = Code[j];
                        ptr++;
                    }
                }
                bool flag = false;
                for (int j = 0; j < FuncPtr; j++)
                {
                    if (strcmp(ListOfFunctions[j], NameOfFunction) == 0)
                    {
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                {
                    strcpy(ListOfFunctions[FuncPtr], NameOfFunction);
                    FuncPtr++;
                }
            }
        }
    }
}

void checkFunctionForRecursion(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    Code = changeTypedef(RawCode);
    addAllFunctions(Code);
    for (int NumberOfFunctionInList = 0; NumberOfFunctionInList < FuncPtr; NumberOfFunctionInList++)
    {
        char OrderOfFunctionCalls[SIZE][SIZE] = {0};
        int ptr = 0;
        for (int i = 0; i < strlen(Code); i++)
        {
            if (Code[i] != ' ' && Code[i] != '\n' && Code[i] != ';' && Code[i] != '\t' &&
                Code[i] == ListOfFunctions[NumberOfFunctionInList][0])
            {
                bool flag = true;
                for (int j = 0; j < strlen(ListOfFunctions[NumberOfFunctionInList]); j++)
                {
                    if (Code[i + j] != ListOfFunctions[NumberOfFunctionInList][j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    int Brackets = 0;
                    bool StartOfFunc = false;
                    for (int j = i; j<strlen(Code); j++)
                    {
                        if (Code[j]=='{')
                        {
                            Brackets++;
                            StartOfFunc = true;
                        }
                        else if (Code[j]=='}')
                        {
                            Brackets--;
                            if (Brackets==0) break;
                        }
                    }
                }
                else continue;
            }
        }
    }
}