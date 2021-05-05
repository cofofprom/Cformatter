#include "RemovePreprocessors.h"

char *changeMacro(char *Code)
{
    char *NewCode = (char *) calloc(SIZE_OF_CODE, 1);
    strcpy(NewCode, Code);
    const char DefineString[] = "define";
    for (int i = 0; i < strlen(NewCode); i++)
    {
        if (NewCode[i - 1] == '#')
        {
            bool flag = true;
            for (int j = 0; j < strlen(DefineString); j++)
            {
                if (NewCode[i + j] != DefineString[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                char *Preproc = (char *) calloc(SIZE, 1), *WhatToChange = (char *) calloc(SIZE, 1), *ChangeFor = (char *) calloc(SIZE, 1);
                int ptr = 0, SpaceCounter = 0;
                for (int j = i - 1; j < strlen(NewCode) && NewCode[j] != '\n'; j++)
                {
                    Preproc[ptr] = NewCode[j];
                    ptr++;
                    if (NewCode[j] == ' ')
                    {
                        SpaceCounter++;
                        if (SpaceCounter == 1)
                        {
                            for (int k = j + 1, id = 0; NewCode[k] != ' '; k++, id++)
                            {
                                WhatToChange[id] = NewCode[k];
                            }
                        }
                        else if (SpaceCounter == 2)
                        {
                            for (int k = j + 1, id = 0; NewCode[k] != '\n'; k++, id++)
                            {
                                ChangeFor[id] = NewCode[k];
                            }
                        }
                    }
                }
                ChangeFor[strlen(ChangeFor) - 1] = '\0';
                Preproc[strlen(Preproc) - 1] = '\0';
                NewCode = replaceOneWord(NewCode, Preproc, "", 1);
                NewCode = replaceWord(NewCode, WhatToChange, ChangeFor, i);
            }
            else continue;
        }
    }
    return NewCode;
}

char *changeTypedef(char *Code)
{
    char *NewCode = (char *) calloc(SIZE_OF_CODE, 1);
    strcpy(NewCode, Code);
    const char TypedefString[] = "typedef";
    for (int i = 1; i < strlen(NewCode); i++)
    {
        if (NewCode[i - 1] == '\t' || NewCode[i - 1] == '\n')
        {
            bool flag = true;
            for (int j = 0; j < strlen(TypedefString); j++)
            {
                if (NewCode[i + j] != TypedefString[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                bool f = false;
                char *TypeDefName = (char *) calloc(SIZE, 1), *WhatToChange = (char *) calloc(SIZE, 1), *ChangeFor = (char *) calloc(SIZE, 1);
                int ptr = 0, SpaceCounter = 0, cnt = 0;
                for (int k = i; NewCode[k] != '\n'; k++)
                {
                    if (NewCode[k] == ' ') cnt++;
                }
                int ptr1 = 0, ptr2 = 0;
                for (int j = i; j < strlen(NewCode) && NewCode[j] != '\n'; j++)
                {
                    TypeDefName[ptr] = NewCode[j];
                    ptr++;
                    if (NewCode[j] == ' ') SpaceCounter++;
                    if (SpaceCounter == 1 && NewCode[j]==' ') continue;
                    else
                    {
                        if (SpaceCounter < cnt && SpaceCounter > 0)
                        {
                            ChangeFor[ptr2] = NewCode[j];
                            ptr2++;
                        }
                        else if (SpaceCounter==cnt && !f)
                        {
                            for (int k=j+1; NewCode[k]!=';'; k++)
                            {
                                WhatToChange[ptr1] = NewCode[k];
                                ptr1++;
                            }
                            f = true;
                        }
                        else continue;
                    }
                }
                TypeDefName[strlen(TypeDefName) - 1] = '\0';
                NewCode = replaceOneWord(NewCode, TypeDefName, " ", 1);
                NewCode = replaceWord(NewCode, WhatToChange, ChangeFor, 1);
            }
            else continue;
        }
    }
    return NewCode;
}
