#include "ChangeComments.h"
#include "../StringTools/StringTools.h"
#define SIZE 10000

#define bool int
#define true 1
#define false 0

char *changeCommet(char *code)
{
    char* temp = (char*)calloc(1024*10, 1);
    strcpy(temp, code);
    bool flag = false;
    for (int i=0; i<strlen(temp)-1; i++)
    {
        if (temp[i] == '/' && temp[i+1] == '*' && !flag)
        {
            strcpy(temp, replaceOneWord(temp, "/*", "", i));
            int j;
            for (j=i; j>0; j--)
            {
                if (temp[j]=='\n') break;
            }
            if (j==0)
            {
                strcpy(temp, replaceOneWord(temp, "#", "//#", 0));
            }
            else
            {
                strcpy(temp, replaceOneWord(temp, "\n", "\n//", j - 1));
            }
            flag = true;
        }
        if (temp[i]=='\n' && flag)
        {
            strcpy(temp, replaceOneWord(temp, "\n", "\n//", i-1));
        }
        if (temp[i] == '*' && temp[i+1] == '/' && flag)
        {
            if (temp[i - 3] == '\n')
            {
                strcpy(temp, replaceOneWord(temp, "//*/", "//", i - 3));
            }
            else
            {
                strcpy(temp, replaceOneWord(temp, "*/", "", i-1));
            }
            flag = false;
        }
    }
    return temp;
}