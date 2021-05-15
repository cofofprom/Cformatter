#include "CheckVariables.h"

Variables ListOfVariables[MAX_VARIABLE_SIZE] = {0};
int NumberOfVariables = 0;

int findVariableInList(char *NameOfVariable)       //Returns -1 if variable is new and the index
{                                                  //of the variable in list in other case
    for (int i = 0; i < NumberOfVariables; i++)
    {
        if (strcmp(NameOfVariable, ListOfVariables[i].Name) == 0) return i;
    }
    return -1;
}

bool isVariable(char *Code, int idx)    //Check if line contains definition of any variable or variables
{
    if (isNameOfSavedType(Code, idx))
    {
        bool flag = true, notMacro = false;
        for (int i = idx; Code[i] != '\n'; i++)
        {
            if (Code[i] == ';')
            {
                notMacro = true;
                break;
            }
            else if (Code[i] == '(')
            {
                flag = false;
                break;
            }
        }
        if (!flag) return false;
        else
        {
            if (!notMacro) return false;
            else return true;
        }
    }
    else return false;
}

void getVariable(char *Code, int idx)           //Put new variables into the list
{
    char Name[SIZE] = {0}, str[SIZE] = {0}, NameOfType[SIZE] = {0};
    int ptr = 0, TypePtr = 0;
    for (int i = idx; i < strlen(Code) && Code[i] != '\n'; i++)
    {
        str[ptr] = Code[i];
        ptr++;
    }
    strcpy(str, replaceWord(str, " = ", "=", 0));
    strcpy(str, replaceWord(str, ", ", ",", 0));
    int SpaceCounter = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ') SpaceCounter++;
        if (str[i] == ',' || str[i] == ';' || str[i] == '=') break;
    }
    int VarIdx = 0, cnt = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (SpaceCounter == cnt)
        {
            VarIdx = i;
            break;
        }
        else
        {
            NameOfType[TypePtr] = str[i];
            TypePtr++;
        }
        if (str[i] == ' ') cnt++;
    }
    int NamePtr = 0, VarInList = 0, VarPtr = 0;
    bool flag = false;
    for (int i = VarIdx; i < strlen(str); i++)
    {
        if (str[i] == '=')
        {
            char tmp[SIZE] = {0};
            strcpy(tmp, NameOfType);
            strcat(tmp, Name);
            if (findVariableInList(tmp) != -1)
            {
                VarInList = findVariableInList(tmp);
            }
            else
            {
                strcpy(ListOfVariables[NumberOfVariables].Name, tmp);
                VarInList = NumberOfVariables;
                NumberOfVariables++;
            }
            flag = true;
        }
        else if (str[i] == ',')
        {
            if (flag)
            {
                VarPtr = 0;
                VarInList = 0;
                flag = false;
            }
            else
            {
                char tmp[SIZE] = {0};
                strcpy(tmp, NameOfType);
                strcat(tmp, Name);
                if (findVariableInList(tmp) != -1)
                {
                    VarInList = findVariableInList(tmp);
                }
                else
                {
                    strcpy(ListOfVariables[NumberOfVariables].Name, tmp);
                    VarInList = NumberOfVariables;
                    NumberOfVariables++;
                }
                strcpy(ListOfVariables[VarInList].Value, "-");
            }
            VarInList = 0;
            NamePtr = 0;
            memset(Name, 0, sizeof(Name));
        }
        else if (str[i] == ';')
        {
            char tmp[SIZE] = {0};
            strcpy(tmp, NameOfType);
            strcat(tmp, Name);
            if (findVariableInList(tmp) != -1)
            {
                VarInList = findVariableInList(tmp);
            }
            else
            {
                strcpy(ListOfVariables[NumberOfVariables].Name, tmp);
                VarInList = NumberOfVariables;
                NumberOfVariables++;
            }
            if (!flag) strcpy(ListOfVariables[VarInList].Value, "-");
            else
            {
                VarInList = 0;
                NamePtr = 0;
                memset(Name, 0, sizeof(Name));
            }
            break;
        }
        else
        {
            if (!flag)
            {
                Name[NamePtr] = str[i];
                NamePtr++;
            }
            else if (flag)
            {
                ListOfVariables[VarInList].Value[VarPtr] = str[i];
                VarPtr++;
            }
        }
    }
}

void findVariables(char *Code)          //Check if there are another definitions and values of exist variables in list
{
    for (int i = 0; i < NumberOfVariables; i++)
    {
        char temp[MAX_SIZE] = {0};
        int ptr = 0;
        int id = 0;
        for (int j = strlen(ListOfVariables[i].Name) - 1; ListOfVariables[i].Name[j] != ' '; j--) id = j;
        for (int j = id; j < strlen(ListOfVariables[i].Name); j++)
        {
            if (ListOfVariables[i].Name[j] != ' ') temp[ptr] = ListOfVariables[i].Name[j], ptr++;
        }
        strcat(temp, " = ");
        char NewCode[SIZE_OF_CODE] = {0};
        strcpy(NewCode, Code);
        while (strstr(NewCode, temp) != NULL)
        {
            memset(ListOfVariables[i].Value, 0, sizeof(ListOfVariables[i].Value));
            char *pt = strstr(NewCode, temp);
            int ValPtr = 0;
            for (int j = strlen(temp); pt[j] != ',' && pt[j] != ';' && pt[j] != '\n' && j < strlen(pt); j++)
            {
                ListOfVariables[i].Value[ValPtr] = pt[j];
                ValPtr++;
            }
            strcpy(NewCode, pt + 3);
        }
    }
    for (int i = 0; i < NumberOfVariables; i++)
    {
        char temp[MAX_SIZE] = {0};
        int ptr = 0;
        int id = 0;
        for (int j = strlen(ListOfVariables[i].Name) - 1; ListOfVariables[i].Name[j] != ' '; j--) id = j;
        for (int j = id; j < strlen(ListOfVariables[i].Name); j++)
        {
            if (ListOfVariables[i].Name[j] != ' ') temp[ptr] = ListOfVariables[i].Name[j], ptr++;
        }
        char t[SIZE] = {0};
        strcpy(t, "&");
        strcat(t, temp);
        if (strstr(Code, t) != NULL)
        {
            strcpy(ListOfVariables[i].Value, "+");
        }
    }
}

void printVariables(char *RawCode)         //Output function
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    Code = changeTypedef(Code);
    for (int i = 0; i < strlen(Code) - 3; i++)
    {
        if (Code[i] == 's' && Code[i + 1] == 't' && Code[i + 2] == 'r' && Code[i + 3] == 'u' && Code[i + 4] == 'c' &&
            Code[i + 5] == 't' && i < strlen(Code) - 5)
        {
            int Brackets = 0, flag = false;
            for (int j = i; j < strlen(Code); j++)
            {
                if (Code[j] == '{' && !flag)
                {
                    flag = true;
                    Brackets++;
                }
                else if (Code[j] == '}') Brackets--;
                if (Brackets == 0)
                {
                    i = j;
                    break;
                }
            }
        }
        if (Code[i] != ' ' && Code[i] != '\n' && Code[i] != ';' && Code[i] != '\t')
        {
            if (isNameOfSavedType(Code, i))
            {
                int temp = isNameOfSavedType(Code, i);
                if (isVariable(Code, i))
                {
                    getVariable(Code, i);
                }
                i += temp + 1;
            }
        }
    }
    findVariables(Code);
    bool flag = true;
    for (int i = 0; i < NumberOfVariables; i++)
    {
        if (!strcmp(ListOfVariables[i].Value, "-"))
        {
            flag = false;
            break;
        }
    }
    if (!flag)
    {
        printf("These variables do not have any value:\n");
        for (int i = 0; i < NumberOfVariables; i++)
        {
            if (!strcmp(ListOfVariables[i].Value, "-"))
            {
                if (findTypeInList(ListOfVariables[i].Name) == -1)
                {
                    printf("  %s\n", ListOfVariables[i].Name);
                }
            }
        }
        printf("\n");
    }
    else
    {
        printf("Each variable is assigned a value.\n\n");
    }
}

void printUnusedVariables(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    for (int i=0; i<NumberOfVariables; i++)
    {
        if (countSubstring(Code, ListOfVariables[i].Name)>=2)
        {
            ListOfVariables[i].isUsed = 1;
        }
        else ListOfVariables[i].isUsed = 0;
    }
    bool flag = false;
    for (int i=0; i<NumberOfVariables; i++)
    {
        if (ListOfVariables[i].isUsed == 0 && !flag)
        {
            flag = true;
            printf("These variables were never used: %s", ListOfVariables[i].Name);
        }
        else if (ListOfVariables[i].isUsed == 0 && flag)
        {
            printf(", %s", ListOfVariables[i].Name);
        }
    }
    if (!flag) printf("All variables were used at least once.\n\n");
    else printf(".\n\n");
}

void DEBUG_VARS(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
//    Code = changeTypedef(Code);
    for (int i = 0; i < strlen(Code) - 3; i++)
    {
        if (Code[i] == 's' && Code[i + 1] == 't' && Code[i + 2] == 'r' && Code[i + 3] == 'u' && Code[i + 4] == 'c' &&
            Code[i + 5] == 't' && i < strlen(Code) - 5)
        {
            int Brackets = 0, flag = false;
            for (int j = i; j < strlen(Code); j++)
            {
                if (Code[j] == '{' && !flag)
                {
                    flag = true;
                    Brackets++;
                }
                else if (Code[j] == '}') Brackets--;
                if (Brackets == 0)
                {
                    i = j;
                    break;
                }
            }
        }
        if (Code[i] != ' ' && Code[i] != '\n' && Code[i] != ';' && Code[i] != '\t')
        {
            if (isNameOfSavedType(Code, i))
            {
                int temp = isNameOfSavedType(Code, i);
                if (isVariable(Code, i))
                {
                    getVariable(Code, i);
                }
                i += temp + 1;
            }
        }
    }
    findVariables(Code);
    printf("%d\n", NumberOfVariables);
    for (int i = 0; i < NumberOfVariables; i++)
    {
        printf("%s = %s\n", ListOfVariables[i].Name, ListOfVariables[i].Value);
    }
}

void checkName(char *RawCode)
{
    char *Code = (char *) calloc(SIZE_OF_CODE, 1);
    Code = changeMacro(RawCode);
    Code = changeTypedef(Code);
    for (int i = 0; i < strlen(Code) - 3; i++)
    {
        if (Code[i] != ' ' && Code[i] != '\n' && Code[i] != ';' && Code[i] != '\t')
        {
            if (isNameOfSavedType(Code, i))
            {
                int temp = isNameOfSavedType(Code, i);
                if (isVariable(Code, i))
                {
                    getVariable(Code, i);
                }
                i += temp + 1;
            }
        }
    }
    bool flag = false;
    for (int i = 0; i < NumberOfVariables; i++)
    {
        char temp[MAX_SIZE] = {0};
        int ptr = 0;
        int id = 0;
        for (int j = strlen(ListOfVariables[i].Name) - 1; ListOfVariables[i].Name[j] != ' '; j--) id = j;
        for (int j = id; j < strlen(ListOfVariables[i].Name); j++)
        {
            if (ListOfVariables[i].Name[j] != ' ') temp[ptr] = ListOfVariables[i].Name[j], ptr++;
        }
        char *NameOfVar = (char *) calloc(sizeof(ListOfVariables[i].Name), 1);
        strcpy(NameOfVar, temp);
        if (strlen(NameOfVar) == 1 &&
            !((NameOfVar[0] >= 'a' && NameOfVar[0] <= 'z') || (NameOfVar[0] >= 'A' && NameOfVar[0] <= 'Z')))
        {
            flag = true;
            printf("Wrong name of the variable (%s).\nThe name with only one symbol must be a Latin letter.\n",
                   NameOfVar);
            continue;
        }
        if (NameOfVar[0] >= '0' && NameOfVar[0] <= '9')
        {
            flag = true;
            printf("Wrong name of the variable (%s).\nThe name of the variable must begin with a Latin letter of with a '_'\n",
                   NameOfVar);
            continue;
        }
        for (int j = 0; j < strlen(NameOfVar); j++)
        {
            if (!((NameOfVar[j] >= '0' && NameOfVar[j] <= '9') || (NameOfVar[j] >= 'a' && NameOfVar[j] <= 'z') ||
                  (NameOfVar[j] >= 'A' && NameOfVar[j] <= 'Z') || NameOfVar[j] == '_'))
            {
                if (j == 0 && NameOfVar[0] == '*') continue;
                else
                {
                    flag = true;
                    printf("Wrong name of the variable (%s).\nOnly numbers, Latin letters, and the symbol '_' are allowed.\n");
                    break;
                }
            }
        }
    }
    if (!flag)
    {
        printf("Names of all variables are correct.\n\n");
    }
}

int isTypedef(char *Code, int idx)              //Returns index of the name of a type if it is typedef
{
    char *TypedefString = "typedef";
    for (int i = idx; i < strlen(Code); i++)
    {
        if (Code[i] == 't')
        {
            bool flag = true;
            for (int j = i; j < strlen(TypedefString); j++)
            {
                if (TypedefString[j] != Code[i + j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                int Brackets = 0;
                for (int j = i; j < strlen(Code); j++)
                {
                    if (Code[j] == '{') Brackets++;
                    else if (Code[j] == '}') Brackets--;
                    if (Code[j] == ';' && Brackets == 0)
                    {
                        for (int k = j; k >= i; k--)
                        {
                            if (Code[k] == ' ' || Code[k] == '}')
                            {
                                return k + 1;
                            }
                        }
                    }
                }
            }
        }
        else return 0;
    }
    return 0;
}