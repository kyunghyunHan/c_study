/*
큐브돌리기

*/
#include <stdio.h>
#include <stdlib.h>
int arr[6][3][3];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        int n; // 회전횟수
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            char s[3];
            scanf("%2s", s);
            printf("%2s", s);
        }
    }
    return 0;
}