/*
그리디
8그램 사용 x
1 2 3 16추가만 각각 10개사용
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c1, c2, c3, c8, c16, n;
    int sum = 0;
    int cnt;

    freopen("jungol.txt", "r", stdin);
    scanf("%d %d %d %d %d %d", &c1, &c2, &c3, &c8, &c16, &n);

    while (n > 0)
    {
        if (n > 8 && c8 > 0)
        {
            n -= 8;
            c8 -= 1;
        }
    }

    return 0;
}