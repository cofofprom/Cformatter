#include "MaxLoopNesting.h"

#define bool int
#define true 1
#define false 0
#define SIZE 1000

char *deleteDoWhile(char *InputString, char *OutputString)
{
    char whileString[] = "while";
    for (int i = 0; i < strlen(InputString); i++)
    {
        if (InputString[i] == 'd' && i <= strlen(InputString) - 3)
        {
            if (InputString[i + 1] == 'o' &&
                ((InputString[i + 2] == ' ' && InputString[i + 3] == '{') || (InputString[i + 2] == '\n')))
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
                for (int j = idx; j < strlen(InputString); j++)
                {
                    if (InputString[j] == 'w')
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

                OutputString = replaceOneWord(InputString, temp, " ", i);

                OutputString = replaceOneWord(InputString, "do", temp, i - 1);

                break;
            }
        }
    }
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

char *makeAllLoopsMultiline(char *InputString)
{
    int countLoops = 0;
    int id = 0;
    while (findLoop(InputString, id))
    {
        countLoops++;
        id = findLoop(InputString, id) + 1;
    }
    char *OutputString = (char *) malloc(strlen(InputString) + countLoops * 100);
    OutputString = deleteDoWhile(InputString, InputString);
    int idx = 0, ans = 0;
    while (findLoop(InputString, idx))
    {
        bool flag = false;
        int type = 0;
        int i = findLoop(OutputString, idx);
        if (OutputString[i] == 'f')
        {
            int cnt = 0;
            type = 1;
            for (int j = i; j < strlen(OutputString); j++)
            {
                if (OutputString[j] == '{')
                {
                    break;
                }
                if (OutputString[j] == ';') cnt++;
                if (cnt == 3 && !flag)
                {
                    flag = true;
                    break;
                }
            }
        }
        else if (OutputString[i] == 'w')
        {
            type = 2;
            for (int j = i; j < strlen(OutputString); j++)
            {
                if (OutputString[j] == '{')
                {
                    break;
                }
                if (OutputString[j] == ';' && !flag)
                {
                    flag = true;
                    break;
                }
            }
        }
        if (flag)
        {
            int cnt = 0;
            for (int j = i; j < strlen(OutputString); j++)
            {
                if (OutputString[j] == '\t')
                {
                    for (int k = j; OutputString[k] == '\t'; k++) cnt++;
                    break;
                }
            }
            char tabs[SIZE] = {0};
            tabs[0] = ';';
            tabs[1] = '\n';
            for (int j = 2; j <= cnt + 1; j++) tabs[j] = '\t';
            tabs[strlen(tabs)] = '}';
            if (type == 1)
            {
                int count = 0;
                for (int j = i; j < strlen(OutputString); j++)
                {
                    if (OutputString[j] == ';') count++;
                    if (count == 2)
                    {
                        OutputString = replaceOneWord(OutputString, ";", tabs, j + 2);
                        break;
                    }
                }
            }
            else OutputString = replaceOneWord(OutputString, ";", tabs, i + 4);
            for (int j = 0; j < strlen(tabs); j++) tabs[j] = '\0';
            tabs[0] = ')', tabs[1] = '{', tabs[2] = '\n';
            for (int j = 3; j < cnt + 4; j++) tabs[j] = '\t';
            tabs[strlen(tabs)];
            int id = 0, CountBrackets = 0;
            bool EndBrackets = false;
            for (int j = i;; j++)
            {
                if (OutputString[j] == '(') CountBrackets++, EndBrackets = true;
                if (OutputString[j] == ')') CountBrackets--;
                if (CountBrackets == 0 && EndBrackets)
                {
                    id = j;
                    break;
                }
            }
            OutputString = replaceOneWord(OutputString, ")", tabs, id);
        }
        idx = i + 4;
    }
    return OutputString;
}

void findMaxLoopNesting(char *InputString, int *Shift, int *Ans)
{
    int temp = findLoop(InputString, *Shift);
    int CountBrackets = 0, idx = 0;
    bool flag = false;
    for (int i = temp; i < strlen(InputString); i++)
    {
        if (InputString[i] == '{') CountBrackets++, flag = true;
        else if (InputString[i] == '}') CountBrackets--;
        if (CountBrackets == 0 && flag)
        {
            idx = i;
            break;
        }
    }
    int CountBracketsInLoop = 0;
    for (int i = temp; i < strlen(InputString); i++)
    {
        if (InputString[i] == '(') CountBracketsInLoop++;
        else if (InputString[i] == ')') CountBracketsInLoop--;
        if (CountBracketsInLoop == 0)
        {
            (*Shift) = i;
            break;
        }
    }
    (*Shift)++;
    if (findLoop(InputString, *Shift) <= idx && findLoop(InputString, *Shift) != 0 )
    {
        (*Ans)++;
    }
    int FindMax[SIZE] = {0};
    int ptr = 0, count = 0;
    while (findLoop(InputString, *Shift) <= idx && findLoop(InputString, *Shift) != 0)
    {
        int cnt = *Ans;
        findMaxLoopNesting(InputString, &(*Shift), &cnt);
        FindMax[ptr] = cnt;
    }
    for (int i=0; i<SIZE; i++)
    {
        if (FindMax[i]>*Ans)
        {
            *Ans = FindMax[i];
        }
    }
    return;
}

void printMaxLoopNesting(char *InputString)
{
    InputString = deleteDoWhile(InputString, InputString);
    InputString = makeAllLoopsMultiline(InputString);
    int idx = 0, ans = 0;
    while (findLoop(InputString, idx))
    {
        int cnt = 1;
        findMaxLoopNesting(InputString, &idx, &cnt);
        if (cnt > ans) ans = cnt;
    }
    printf("Maximum depth of nested loops is %d", ans);
}
