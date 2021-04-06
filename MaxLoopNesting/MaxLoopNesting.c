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
        if (InputString[i] == 'd' && i <= strlen(InputString) - 3)
        {
            if (InputString[i + 1] == 'o' && ((InputString[i + 2] == ' ' && InputString[i + 3] == '{') || (InputString[i + 2] == '\n')))
            {
                int CountBrackets = 0, idx = i;
                bool flag = false;
                for (int j = i + 1; j < strlen(InputString); j++)
                {
                    if (InputString[j] == '{') CountBrackets++, flag = true;
                    else if (InputString[j] == '}') CountBrackets--;
                    if (flag && CountBrackets == 0)
                    {
                        idx = j;
                        break;
                    }
                }
                for (int j = idx; j<strlen(InputString); j++)
                {
                    if (InputString[j]=='w')
                    {
                        idx = j;
                        break;
                    }
                }
                char temp[SIZE] = {0};
                int ptr = 0;
                for (int k = idx; k < strlen(InputString); k++)
                {
                    if (InputString[k] != '\n')
                    {
                        temp[ptr] = InputString[k];
                        ptr++;
                    }
                    else break;
                }
                InputString = replaceOneWord(InputString, temp, " ", i);

                InputString = replaceOneWord(InputString, "do", temp, i - 1);
                break;
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
    }
    return 0;
}

void findMaxLoopNesting(char *InputString, int *Shift, int *Ans)
{
    (*Ans)++;
    int temp = findLoop(InputString, *Shift);
//    printf("%d\n", temp);
//    (*Shift)++;
    int CountBrackets = 0, idx = 0;
    bool flag = false;
    for (int i=temp; i<strlen(InputString); i++)
    {
        if (InputString[i]=='{') CountBrackets++, flag = true;
        else if (InputString[i]=='}') CountBrackets--;
        if (CountBrackets==0 && flag)
        {
            idx = i;
            break;
        }
    }
    int CountBracketsInLoop = 0;
    for (int i=temp; i<strlen(InputString); i++)
    {
        if (InputString[i]=='(') CountBracketsInLoop++;
        else if (InputString[i]==')') CountBracketsInLoop--;
        if (CountBracketsInLoop==0)
        {
            (*Shift) = i;
            break;
        }
    }
    (*Shift)++;
//    printf("%d %d\n", findLoop(InputString, *Shift), idx);
    if (findLoop(InputString, *Shift)<=idx && findLoop(InputString, *Shift)!=0) findMaxLoopNesting(InputString, &(*Shift), &(*Ans));
    else return;
}

void printMaxLoopNesting(char *InputString)
{
    InputString = deleteDoWhile(InputString, InputString);
    int idx = 0, ans = 0;
    while (findLoop(InputString, idx))
    {
        int cnt = 0;
        findMaxLoopNesting(InputString, &idx, &cnt);
        if (cnt>ans) ans = cnt;
//        printf("%d\n", cnt);
    }
    printf("Maximum depth of nested loops is %d", ans);
}