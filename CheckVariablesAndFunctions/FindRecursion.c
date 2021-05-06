#include "FindRecursion.h"

UserType ListOfUserTypes[MAX_SIZE] = {0};
int TypesPtr = 0;

int isNameOfSavedType(char *Code, int idx)
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
        if ((Code[i] >= 'a' && Code[i] <= 'z') || (Code[i] >= 'A' && Code[i] <= 'Z'))
        {
            Name[ptr] = Code[i];
            ptr++;
        }
        else break;
    }
    for (int i = 0; i < NumberOfStdTypes; i++)
    {
        if (strlen(NamesOfStdTypes[i]) == strlen(Name))
        {
            bool flag = true;
            for (int j = 0; j < strlen(Name); j++)
            {
                if (NamesOfStdTypes[i][j] != Name[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag) return strlen(Name);
            else continue;
        }
    }
//    for (int i = 0; i < TypesPtr; i++)
//    {
//        if (strlen(Name) == ListOfUserTypes[i].NameSize)
//        {
//            bool flag = true;
//            for (int j = 0; j < strlen(Name); j++)
//            {
//                if (ListOfUserTypes[i].Name[j] != Name[j])
//                {
//                    flag = false;
//                    break;
//                }
//            }
//            if (flag) return 1;
//            else continue;
//        }
//    }
    return 0;
}

void addAllTypes(char *Code)
{
    char StructString[] = "struct", TypedefString[] = "typedef", str[MAX_SIZE] = {0};
    for (int i = 0; i < strlen(Code); i++)
    {
        if (Code[i] == 's' && Code[i-1]=='\t')
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
                int CountBrackets = 0, id = i;
                for (int j=i; j<strlen(Code); j++)
                {
                    if (Code[j]=='{') CountBrackets++;
                    if (Code[j]=='}') CountBrackets--;
                    if (CountBrackets==0)
                    {
                        id = j;
                        break;
                    }
                }
//                for (int )
            }
        }
    }
}