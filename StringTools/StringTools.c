#include "StringTools.h"

#define bool int
#define true 1
#define false 0
#define SIZE 1000

char *replaceWord(char *s, const char *oldW, const char *newW, int ptr)
{
    char *result, temp[SIZE] = {0}, *source;
    int idx = 0;
    for (int k = ptr; k < strlen(s); k++)
    {
        temp[idx] = s[k];
        idx++;
    }
    source = (char*) malloc(strlen(s)+1);
    strcpy(source, s);
    strcpy(s, temp);

    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;

            i += oldWlen - 1;
        }
    }
    result = (char *) malloc(i + cnt * (newWlen - oldWlen) + 1);
    i = 0;
    while (*s)
    {
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else result[i++] = *s++;
    }
    result[i] = '\0';

    for (int j = ptr, k = 0; k<strlen(result); j++, k++)
    {
        source[j] = result[k];
    }

    return source;
}

char *replaceOneWord(char *s, const char *oldW, const char *newW, int ptr)
{
    char *result, temp[SIZE] = {0}, *source;
    int idx = 0;
    for (int k = ptr; k < strlen(s); k++)
    {
        temp[idx] = s[k];
        idx++;
    }
    source = (char*) malloc(strlen(s)+1);
    strcpy(source, s);
    strcpy(s, temp);
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            i += oldWlen - 1;
            break;
        }
    }
    result = (char *) malloc(i + cnt * (newWlen - oldWlen) + 1);
    i = 0;
    bool flag = false;
    while (*s)
    {
        if (strstr(s, oldW) == s && !flag)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
            flag = true;
        }
        else result[i++] = *s++;
    }
    result[i] = '\0';

    for (int j = ptr, k = 0; k<strlen(result)+1; j++, k++)
    {
        source[j] = result[k];
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