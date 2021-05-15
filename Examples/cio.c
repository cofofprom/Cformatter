#include <stdio.h>
#define int long long
#define SIZE 1000

typedef struct T
{
    int test;
}
test_struct;



int Fact_func(int n)
{
int answer;
if(n==1)
{return 1;}
answer = Fact_func(n-1)*n;
return (answer);
}


int not_camel_style(int n)
{

if(n==1)
{return 1;}
}
signed main()
{

int n;
int unuseful = 8;
int unvalue, no_value;
int count=0;
int a;
scanf("%d", &n);
    for (int i = 0; i < n;    i++) {
scanf("%d", &a);
if ((a == 3) || (a==4)) {
    count++;
}
while (1)
{
    break;
}
    }

    return 0;
}