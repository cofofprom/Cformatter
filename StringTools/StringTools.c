#include "StringTools.h"

#define bool int
#define true 1
#define false 0
#define SIZE 1000

char *replaceWord(char *s, const char *oldW, const char *newW, int ptr)
{
    char result[SIZE] = {0}, temp[SIZE] = {0}, *source = (char*)malloc(strlen(s)+1) , *str = (char*)malloc(strlen(s)+1);
    strcpy(str, s);
    int idx = 0, len = strlen(str);
    for (int k = ptr; k < len; k++)
    {
        temp[idx] = str[k];
        idx++;
    }
    strcpy(source, str);
    strcpy(str, temp);
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    for (i = 0; str[i] != '\0'; i++)
    {
        if (strstr(&str[i], oldW) == &str[i])
        {
            cnt++;

            i += oldWlen - 1;
        }
    }
    i = 0;
    while (*str)
    {
        if (strstr(str, oldW) == str)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            str += oldWlen;
        }
        else result[i++] = *str++;
    }
    result[i] = '\0';
    int j, k = 0;
    for (j = ptr, k = 0; k<strlen(result); j++, k++)
    {
        source[j] = result[k];
    }
    for (int t=strlen(source)-1; t>=j; t--)
    {
        source[t] = '\0';
    }
    return source;
}

char *replaceOneWord(char *s, const char *oldW, const char *newW, int ptr)
{
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    char result[SIZE] = {0}, temp[SIZE] = {0}, *source = (char *) malloc(strlen(s) + (newWlen - oldWlen) + 1), *str = (char*)malloc(strlen(s)+1);
    strcpy(str, s);
    int idx = 0;
    int len = strlen(s);
    for (int k = ptr; k < len; k++)
    {
        temp[idx] = str[k];
        idx++;
    }
    strcpy(source, str);
    strcpy(str, temp);
    int i, cnt = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (strstr(&str[i], oldW) == &str[i])
        {
            i += oldWlen - 1;
            break;
        }
    }
    i = 0;
    bool flag = false;
    while (*str)
    {
        if (strstr(str, oldW) == str && !flag)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            str += oldWlen;
            flag = true;
        }
        else result[i++] = *str++;
    }
    result[i] = '\0';
    int j, k = 0;
    for (j = ptr, k = 0; k<strlen(result); j++, k++)
    {
        source[j] = result[k];
    }
    for (int t=strlen(source)-1; t>=j; t--)
    {
        source[t] = '\0';
    }
    return source;
}

int countSubstring(char *String, char *Substring)
{
    int count = 0;
    const char *temp = String;
    while (temp = strstr(temp, Substring))
    {
        count++;
        temp++;
    }
    return count;
}