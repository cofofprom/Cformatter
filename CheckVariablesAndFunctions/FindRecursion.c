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
    if (isNameOfSavedType(Code, idx) && (Code[idx - 1] == '\t' || Code[idx - 1] == '\n'))
    {
        bool flag = false;
        for (int i = idx; i < strlen(Code) && Code[i] != '\n'; i++)
        {
            if (Code[i] == ';' || Code[i] == '=' || Code[i] == '\n')
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
            if (isNameOfSavedType(Code, i) && isFunction(Code, i))
            {
                char NameOfFunction[SIZE] = {0};
                int ptr = 0;
                int id = i;
                while (Code[id] != '(') id++;
                while (Code[id] != ' ') id--;
                id++;
                for (int j = id; Code[j] != '('; j++)
                {
                    NameOfFunction[ptr] = Code[j];
                    ptr++;
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

bool checkList(char (*OrderOfFunctionCalls)[SIZE], char *CurrentFunction, int ptr)
{
    for (int i = 0; i < ptr; i++)
    {
        if (strcmp(OrderOfFunctionCalls[i], CurrentFunction) == 0)
        {
            return true;
        }
    }
    return false;
}

bool findFunc(char (*OrderOfFunctionCalls)[SIZE], char *CurrentFunction, char *Code, int ptr)
{
    if (checkList(OrderOfFunctionCalls, CurrentFunction, ptr))
    {
        printf("Recursive transition detected in functions ");
        for (int i = 0; i < ptr; i++)
        {
            printf("%s -> ", OrderOfFunctionCalls[i]);
        }
        printf("%s -> ...\n", CurrentFunction);
        return true;
    }
    strcpy(OrderOfFunctionCalls[ptr], CurrentFunction);
    ptr++;
    for (int i = 0; i < strlen(Code); i++)
    {
        if (Code[i] != ' ' && Code[i] != '\n' && Code[i] != ';' && Code[i] != '\t' &&
            Code[i] == CurrentFunction[0])
        {
            bool flag = true;
            for (int j = 0; j < strlen(CurrentFunction); j++)
            {
                if (Code[i + j] != CurrentFunction[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                int Brackets = 0;
                bool Found = false;
                for (int j = i + strlen(CurrentFunction)+1; j < strlen(Code); j++)
                {
                    if (Code[j] == '{')
                    {
                        Brackets++;
                    }
                    else if (Code[j] == '}')
                    {
                        Brackets--;
                        if (Brackets == 0) break;
                    }
                    else
                    {
                        if (Code[j] == '(' &&
                            (Code[j - 1] >= 'A' && Code[j - 1] <= 'Z' ||
                             Code[j - 1] >= 'a' && Code[j - 1] <= 'z'))
                        {
                            int k = j;
                            while (Code[k] != ' ') k--;
                            k++;
                            char temp[SIZE] = {0};
                            int StrPtr = 0;
                            for (k; Code[k] != '('; k++)
                            {
                                temp[StrPtr] = Code[k];
                                StrPtr++;
                            }
                            bool isFunc = false;
                            for (int z = 0; z < FuncPtr; z++)
                            {
                                if (strcmp(temp, ListOfFunctions[z]) == 0)
                                {
                                    isFunc = true;
                                    break;
                                }
                            }
                            if (isFunc)
                            {
                                return findFunc(OrderOfFunctionCalls, temp, Code, ptr);
                            }
                        }
                    }
                }

            }
            else continue;
        }
    }
    return false;
}

void checkFunctionsForRecursion(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    Code = changeTypedef(Code);
    addAllFunctions(Code);
    bool flag = false;
    for (int NumberOfFunctionInList = 0; NumberOfFunctionInList < FuncPtr; NumberOfFunctionInList++)
    {
        char OrderOfFunctionCalls[SIZE][SIZE] = {0}, CurrentFunction[SIZE] = {0};
        strcpy(CurrentFunction, ListOfFunctions[NumberOfFunctionInList]);
        int ptr = 0;
        if (findFunc(OrderOfFunctionCalls, CurrentFunction, Code, ptr)) flag = true;
    }
    if (!flag)
    {
        printf("No recursive calls were detected in the program code\n");
    }
}

void DEBUG_FUNC(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    Code = changeTypedef(Code);
    addAllFunctions(Code);
    printf("%s\n", Code);
    printf("All user types:\n");
    for (int i = 0; i < NumberOfSavedTypes; i++)
    {
        printf("%d) %s\n", i + 1, ListOfUserTypes[i].Name);
    }
    printf("All functions in program:\n");
    for (int i = 0; i < FuncPtr; i++)
    {
        printf("%d) %s\n", i + 1, ListOfFunctions[i]);
    }
}