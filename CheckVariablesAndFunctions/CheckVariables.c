#include "CheckVariables.h"

Variables ListOfVariables[MAX_VARIABLE_SIZE] = {0};
int NumberOfVariables = 0;

int findVariableInList(char NameOfVariable[])
{
    for (int i = 0; i < NumberOfVariables; i++)
    {
        if (!strcmp(NameOfVariable, ListOfVariables[i].Name))
            return i;
    }
    return NumberOfVariables;
}

bool isVariable(char *Code, int idx)
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

void getVariable(char *Code, int idx)
{
    char Name[SIZE] = {0};
    int ptr = 0;
    for (int i = idx; i < strlen(Code) && Code[i] != '\n'; i++)
    {
        if (Code[i] == ',' || Code[i] == ';' || Code[i] == ' ')
        {
            int id = i;
            for (int j = i; Code[j] != ' '; j--) id = j;
            id++;
            for (int j = id; j < i; j++)
            {
                Name[ptr] = Code[j];
                ptr++;
            }
            bool fl = false;
            int EqId = 0;
            for (int j = 0; j < ptr; j++)
            {
                if (Name[j] == '=')
                {
                    fl = true;
                    EqId = j;
                    break;
                }
            }
            if (fl)
            {
                char Var[SIZE] = {0}, Val[SIZE] = {0};
                for (int k = 0; k < EqId - 1; k++)
                {
                    Var[k] = Name[k];
                }
                for (int k = 0; EqId + k + 2 < ptr; k++)
                {
                    Val[k] = Name[EqId + k + 2];
                }
                if (findVariableInList(Var) != NumberOfVariables)
                {
                    memset(ListOfVariables[findVariableInList(Var)].Value, 0, sizeof(ListOfVariables[findVariableInList(Var)].Value));
                    strcpy(ListOfVariables[findVariableInList(Var)].Value, Val);
                }
                else
                {
                    strcpy(ListOfVariables[NumberOfVariables].Name, Var);
                    strcpy(ListOfVariables[NumberOfVariables].Value, Val);
                    NumberOfVariables++;
                }
            }
            else
            {
                if (findVariableInList(Name)!=NumberOfVariables)
                {
                    memset(ListOfVariables[findVariableInList(Name)].Value, 0, sizeof(ListOfVariables[findVariableInList(Name)].Value));
                    strcpy(ListOfVariables[findVariableInList(Name)].Value, "-");
                }
                else
                {
                    strcpy(ListOfVariables[NumberOfVariables].Name, Name);
                    strcpy(ListOfVariables[NumberOfVariables].Value, "-");
                    NumberOfVariables++;
                }
            }
        }
    }
}

void findVariables(char *Code)
{
    char *NewCode = (char *) calloc(SIZE_OF_CODE, 1);
    strcpy(NewCode, Code);
    NewCode = changeMacro(NewCode);
    NewCode = changeTypedef(NewCode);
    for (int i=0; i<NumberOfVariables; i++)
    {
        char temp[MAX_SIZE] = {0};
        strcpy(temp, ListOfVariables[i].Name);
        strcat(temp, " = ");
        while (strstr(NewCode, temp)!=NULL)
        {
            memset(ListOfVariables[i].Value, 0, sizeof(ListOfVariables[i].Value));
            char *pt = strstr(NewCode, temp);
            int ValPtr = 0;
            for (int j=strlen(ListOfVariables[i].Name)+3; pt[j]!=',' && pt[j]!=';' && pt[j]!='\n'; j++)
            {
                ListOfVariables[i].Value[ValPtr] = pt[j];
                ValPtr++;
            }
        }
    }
}

void printVariables(char *Code)
{
    printf("%d\n", NumberOfVariables);
    for (int i=0; i<strlen(Code)-3; i++)
    {
        if (Code[i]!=' ' && Code[i]!='\n' && Code[i]!=';' && Code[i]!='\t')
        {
            if (isNameOfSavedType(Code, i))
            {
                if (isVariable(Code, i))
                {
                    getVariable(Code, i);
                }
            }
        }
    }
//    findVariables(Code);
    printf("%d\n", NumberOfVariables);
    for (int i = 0; i < NumberOfVariables; i++)
    {
        printf("%s = %s\n", ListOfVariables[i].Name, ListOfVariables[i].Value);
    }
}