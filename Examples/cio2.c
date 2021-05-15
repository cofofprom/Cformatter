#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>


#include <stdio.h>

#include <math.h>
#define ROW 100

#define COL 100
int main2()
{

    /*dfvdfvndfuj
     * fdvrs
     */
    int n,count=0;

    int mat[ROW][COL] = { 0 };
    int a[ROW] = { 0 };


    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &mat[i][j]);
        }

}
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            if (mat[i][count] == 0) {
                  a[count] = i;
                count++;
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", mat[a[i]][j]);
        }
        printf("\n");
    }
    return 0;
}

