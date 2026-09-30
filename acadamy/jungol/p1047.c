#include <stdio.h>
int n, cnt;
void f(int p, int c)
{
    cnt++;

    if (cnt == n)
    {
        printf("%d\n", p);
        return;
    }
    f(c, p + c);
}

int main(void)
{
    cnt = 0;

    scanf("%d", &n);
    f(1, 1);
    return 0;
}