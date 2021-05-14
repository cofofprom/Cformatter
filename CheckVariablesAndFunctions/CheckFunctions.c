#include "CheckFunctions.h"

UserType ListOfUserTypes[MAX_SIZE] = {0};
UserFunction ListOfFunctions[MAX_SIZE] = {0};
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
                                               "long double _Complex", "FILE", "void", "signed"};
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
        if (strlen(NamesOfStdTypes[i]) == strlen(Name) && !strcmp(Name, NamesOfStdTypes[i])) return (int) strlen(Name);
        else continue;
    }
    for (int i = 0; i < NumberOfSavedTypes; i++)
    {
        if (strlen(Name) == ListOfUserTypes[i].NameSize && !strcmp(Name, ListOfUserTypes[i].Name))
            return (int) strlen(Name);
        else continue;
    }
    return false;
}

bool isNameOfUserType(char *Code, int idx)
{
    char Name[STRING_SIZE] = {0};
    int ptr = 0;
    for (int i = idx; i < strlen(Code) && Code[i] != '\n'; i++)
    {
        if ((Code[i] >= 'a' && Code[i] <= 'z') || (Code[i] >= 'A' && Code[i] <= 'Z') || Code[i] == '_')
        {
            Name[ptr] = Code[i];
            ptr++;
        }
        else break;
    }
    for (int i = 0; i < NumberOfSavedTypes; i++)
    {
        if (strlen(Name) == ListOfUserTypes[i].NameSize && !strcmp(Name, ListOfUserTypes[i].Name)) return true;
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
        if (Code[i] == 's' && (Code[i - 1] == '\n' || Code[i - 1] == '\r' || Code[i - 1] == '\t' || Code[i - 1] == ' '))
        {
            bool flag = true;
            for (int j = 0; j < strlen(StructString); j++)
            {
                if (StructString[j] != Code[i + j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                int idx = i + strlen(StructString) + 1;
                int CountBrackets = 0, id = i, StructPtr = 0, TypedefPtr = 0;
                char NameOfStruct[SIZE] = {0}, TypedefName[SIZE] = {0};
                for (int j = idx; Code[j] != '\n' && Code[j] != '{'; j++)
                {
                    if (Code[j] != ' ')
                    {
                        NameOfStruct[StructPtr] = Code[j];
                        StructPtr++;
                    }
                }
                bool flag = false;
                for (int j = idx; j < strlen(Code); j++)
                {
                    if (Code[j] == '{') CountBrackets++, flag = true;
                    if (Code[j] == '}') CountBrackets--;
                    if (CountBrackets == 0 && flag)
                    {
                        id = j;
                        break;
                    }
                }
                id++;
                for (int j = id; j < strlen(Code) && Code[j] != ';'; j++)
                {
                    if (Code[j] != ' ' && Code[j] != '\n')
                    {
                        TypedefName[TypedefPtr] = Code[j];
                        TypedefPtr++;
                    }
                }
                bool IsAlreadyAdded = false;
                for (int i = 0; i < NumberOfSavedTypes; i++)
                {
                    if ((strlen(NameOfStruct) == ListOfUserTypes[i].NameSize &&
                         !strcmp(NameOfStruct, ListOfUserTypes[i].Name) && TypedefPtr == 0) ||
                        (strlen(TypedefName) == ListOfUserTypes[i].NameSize &&
                         !strcmp(TypedefName, ListOfUserTypes[i].Name) && TypedefPtr != 0))
                        IsAlreadyAdded = true;
                }
                if (!IsAlreadyAdded)
                {
                    if (TypedefPtr != 0) strcpy(NameOfStruct, TypedefName);
                    strcpy(ListOfUserTypes[NumberOfSavedTypes].Name, NameOfStruct);
                    ListOfUserTypes[NumberOfSavedTypes].NameSize = (int) strlen(
                            ListOfUserTypes[NumberOfSavedTypes].Name);
                    NumberOfSavedTypes++;
                }
            }
            else continue;
        }
    }
//    int NewNumberOfSavedTypes = NumberOfSavedTypes;
//    for (int i = NumberOfSavedTypes - 1; i >= 0; i--)
//    {
//        for (int j = 0; j < NumberOfSavedTypes; j++)
//        {
//            if ((strcmp(ListOfUserTypes[j].Name, ListOfUserTypes[i].Name) == 1 &&
//                 (ListOfUserTypes[j].Name[0] == (char) toupper(ListOfUserTypes[i].Name[0]) ||
//                  ListOfUserTypes[j].Name[0] == (char) tolower(ListOfUserTypes[i].Name[0]))) ||
//                (strcmp(ListOfUserTypes[j].Name, ListOfUserTypes[i].Name) == 0)
//        }
//    }
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
                    if (strcmp(ListOfFunctions[j].Name, NameOfFunction) == 0)
                    {
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                {
                    bool isMainFunc = false;
                    if (strlen(NameOfFunction) == 4 && NameOfFunction[0] == 'm' && NameOfFunction[1] == 'a' &&
                        NameOfFunction[2] == 'i' && NameOfFunction[3] == 'n')
                        isMainFunc = true;
                    if (!isMainFunc)
                    {
                        strcpy(ListOfFunctions[FuncPtr].Name, NameOfFunction);
                        ListOfFunctions[FuncPtr].isUsed = 0;
                        FuncPtr++;
                    }
                }
            }
        }
    }
    memset(ListOfUserTypes, '\0', sizeof(ListOfUserTypes));
    NumberOfSavedTypes = 0;
}

bool isFunctionInCode(char *Code, int idx)
{
    addAllFunctions(Code);
    bool flag = false;
    char Name[SIZE] = {0};
    for (int i = idx; i < strlen(Code) && Code[i] != '\n'; i++)
    {
        if (Code[i] == ';' || Code[i] == '=' || Code[i] == '\n' || Code[i] == '"')
        {
            flag = false;
            break;
        }
        if (Code[i] == '(')
        {
            flag = true;
            int id = i;
            while (Code[id] != ' ' && Code[id] != '\t' && Code[id] != '\n') id--;
            id++;
            for (int k = id, ptr = 0; Code[k] != '('; k++, ptr++)
            {
                Name[ptr] = Code[k];
            }
            break;
        }
    }
    if (flag)
    {
        for (int i = 0; i < FuncPtr; i++)
        {
            if (strcmp(ListOfFunctions[i].Name, Name) == 0)
            {
                ListOfFunctions[i].isUsed = 1;
                memset(ListOfFunctions, 0, sizeof(ListOfFunctions));
                FuncPtr = 0;
                return true;
            }
        }
    }
    memset(ListOfFunctions, '\0', sizeof(ListOfFunctions));
    FuncPtr = 0;
    return false;
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
    addAllFunctions(Code);
    addAllTypes(Code);
    if (checkList(OrderOfFunctionCalls, CurrentFunction, ptr))
    {
        printf("The program contains recursive functions\n");
        memset(ListOfFunctions, '\0', sizeof(ListOfFunctions));
        FuncPtr = 0;
        memset(ListOfUserTypes, '\0', sizeof(ListOfUserTypes));
        NumberOfSavedTypes = 0;
        return true;
    }
    strcpy(OrderOfFunctionCalls[ptr], CurrentFunction);
    ptr++;
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
                if (strcmp(NameOfFunction, CurrentFunction) == 0) flag = true;
                if (flag)
                {
                    int Brackets = 0;
                    bool Found = false;
                    for (int j = id + ptr + 1; j < strlen(Code); j++)
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
                                while (Code[k] != ' ' && Code[k] != '\n' && Code[k] != '\r' && Code[k] != '\t') k--;
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
                                    if (strcmp(temp, ListOfFunctions[z].Name) == 0)
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
            else continue;
        }
    }
    memset(ListOfFunctions, '\0', sizeof(ListOfFunctions));
    FuncPtr = 0;
    memset(ListOfUserTypes, '\0', sizeof(ListOfUserTypes));
    NumberOfSavedTypes = 0;
    return false;
}

void checkFunctionsForRecursion(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
//    Code = changeTypedef(Code);
    addAllFunctions(Code);
    addAllTypes(Code);
    bool flag = false;
    for (int NumberOfFunctionInList = 0; NumberOfFunctionInList < FuncPtr; NumberOfFunctionInList++)
    {
        if (flag) break;
        char OrderOfFunctionCalls[SIZE][SIZE] = {0}, CurrentFunction[SIZE] = {0};
        strcpy(CurrentFunction, ListOfFunctions[NumberOfFunctionInList].Name);
        int ptr = 0;
        if (findFunc(OrderOfFunctionCalls, CurrentFunction, Code, ptr)) flag = true;
    }
    if (!flag)
    {
        printf("No recursive calls were detected in the program code\n");
    }
    memset(ListOfFunctions, '\0', sizeof(ListOfFunctions));
    FuncPtr = 0;
    memset(ListOfUserTypes, '\0', sizeof(ListOfUserTypes));
    NumberOfSavedTypes = 0;
}

void printUnusedFunctions(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    addAllFunctions(Code);
    addAllTypes(Code);
    bool flag = false;
    for (int i = 0; i < FuncPtr; i++)
    {
        if (!ListOfFunctions[i].isUsed)
        {
            if (!flag)
            {
                printf("These functions were never used: ");
                flag = true;
                printf("%s", ListOfFunctions[i].Name);
            }
            else if (flag)
            {
                printf(", %s", ListOfFunctions[i].Name);
            }
        }
    }
    if (!flag) printf("Each function in code has been used at least once.\n");
    else printf("\n");
    memset(ListOfFunctions, '\0', sizeof(ListOfFunctions));
    FuncPtr = 0;
    memset(ListOfUserTypes, '\0', sizeof(ListOfUserTypes));
    NumberOfSavedTypes = 0;
}

void DEBUG_FUNC(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
//    Code = changeTypedef(Code);
    addAllFunctions(Code);
    addAllTypes(Code);
//    printf("%s\n", Code);
    printf("All user types:\n");
    for (int i = 0; i < NumberOfSavedTypes; i++)
    {
        printf("%d) %s\n", i + 1, ListOfUserTypes[i].Name);
    }
    printf("All functions in program:\n");
    for (int i = 0; i < FuncPtr; i++)
    {
        printf("%d) %s\n", i + 1, ListOfFunctions[i].Name);
    }
    memset(ListOfFunctions, '\0', sizeof(ListOfFunctions));
    FuncPtr = 0;
    memset(ListOfUserTypes, '\0', sizeof(ListOfUserTypes));
    NumberOfSavedTypes = 0;
}