#include <stdio.h>

int main()
{
    int n, k;
    int cnt = 0;
    n = 3;
    k = 6;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            for (int e = 1; e <= 3; e++)
            {
                if (i + e + j == 6)
                {
                    cnt += 1;
                }
            }
        }
    }
    printf("%d", cnt);
}