#include "MaxLoopNesting.h"

#define bool int
#define true 1
#define false 0
#define SIZE 100

char *deleteDoWhile(char *InputString, char *OutputString)
{
    char whileString[] = "while";
    for (int i = 0; i < strlen(InputString); i++)
    {
        if (InputString[i] == 'd' && i <= strlen(InputString)-3)
        {
            if (InputString[i+1]=='o' && ((InputString[i+2]==' ' && InputString[i+3]=='{') || (InputString[i+2]=='\n')))
            {
                for (int j=i+1; j<strlen(InputString); j++)
                {
                    if (InputString[j] == 'w' && i <= strlen(InputString) - 5)
                    {
                        bool flag = true;
                        for (int k = 0; k < strlen(whileString); k++)
                        {
                            if (whileString[k] != InputString[j + k])
                            {
                                flag = false;
                                break;
                            }
                        }
                        if (flag)
                        {
                            char temp[SIZE] = {0};
                            int ptr=0;
                            for (int k=0; k<strlen(InputString); k++)
                            {
                                if (InputString[k]!='\n')
                                {
                                    temp[ptr] = InputString[k];
                                    ptr++;
                                }
                                else break;
                            }
                            InputString = replaceOneWord(InputString, temp, " ", i);
                            InputString = replaceOneWord(InputString, "do", temp, i-1);
                            break;
                        }
                    }
                }
            }
        }
    }
    strcpy(OutputString, InputString);
    return OutputString;
}
int findLoop(char *InputString, int idx)
{
    char forString[] = "for", whileString[] = "while";
    for (int i = idx; i < strlen(InputString); i++)
    {
        if (InputString[i] == 'f' && i <= strlen(InputString) - 3)
        {
            bool flag = true;
            for (int j = 0; j < strlen(forString); j++)
            {
                if (forString[j] != InputString[i + j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag) return i;
            else continue;
        }
        else if (InputString[i] == 'w' && i <= strlen(InputString) - 5)
        {
            bool flag = true;
            for (int j = 0; j < strlen(whileString); j++)
            {
                if (whileString[j] != InputString[i + j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag) return i;
            else continue;
        }
        else if (InputString[i] == 'd' && i <= strlen(InputString)-3)
        {
            if (InputString[i+1]=='o' && ((InputString[i+2]==' ' && InputString[i+3]=='{') || (InputString[i+2]=='\n')))
            {
                for (int j=i+1; j<strlen(InputString); j++)
                {
                    if (InputString[j] == 'w' && i <= strlen(InputString) - 5)
                    {
                        bool flag = true;
                        for (int k = 0; k < strlen(whileString); k++)
                        {
                            if (whileString[k] != InputString[j + k])
                            {
                                flag = false;
                                break;
                            }
                        }
                        if (flag)
                        {
                            char temp[SIZE] = {0};
                            int ptr=0;
                            for (int k=0; k<strlen(InputString); k++)
                            {
                                if (InputString[k]!='\n')
                                {
                                    temp[ptr] = InputString[k];
                                    ptr++;
                                }
                                else break;
                            }
                            InputString = replaceOneWord(InputString, temp, " ", i);
                            InputString = replaceOneWord(InputString, "do", temp, i-1);
                            break;
                        }
                    }
                }
                return i;
            }
        }
    }
    return 0;
}

void findMaxLoopNesting(char *InputString)
{
    InputString = deleteDoWhile(InputString, InputString);
    int shift = -1, ans = 0;
    while (findLoop(InputString, shift + 1))
    {
        int CurrentNesting = 1, CurrentCycle = findLoop(InputString, shift + 1);
        for (int i = CurrentCycle; i < strlen(InputString); i++)
        {
            if (InputString[i] == '(')
            {
                int idx = i + 1;
                for (int j = idx; j < strlen(InputString); j++)
                {
                    if (InputString[j] == ')')
                    {
                        idx = j;
                        break;
                    }
                }
            }
        }
    }
}