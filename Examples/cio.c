#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define SIZE 1000
int factr(int n)
{
    int answer;
    if(n==1)
    {return (1);}
    answer = factr(n-1)*n;
    return(answer);
}


int not_camel_style(int n)
{

    int answer;
    if(n==1)
    {return (1);}
    answer = factr(n-1)*n;
    return(answer);
}
int main()
{

    int n;
    int unuseful = 8;
    int unvalue;
    int count=0;

    int a[SIZE] = {    0 };
    scanf("%d", &n);
    for (int i = 0; i < n;    i++) {
        scanf("%d", &a[i]);
        if ((a[i] < a[i + 1]) && (a[
                                          i] < a[i - 1])) {
            count = count + 1;

        }
    }
    printf("%d", count    );

    return 0;
}

