#include <stdio.h>

int main(void)
{
    long long arr[4][2];
    long long total = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            scanf("%lld", &arr[i][j]);
            total += arr[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        long long sum = 0;

        for (int j = 0; j < 2; j++)
        {
            sum += arr[i][j];
        }

        printf("%lld", sum / 2);

        if (i < 3)
            printf(" ");
    }

    printf("\n");

    for (int j = 0; j < 2; j++)
    {
        long long sum = 0;

        for (int i = 0; i < 4; i++)
        {
            sum += arr[i][j];
        }

        printf("%lld", sum / 4);

        if (j < 1)
            printf(" ");
    }

    printf("\n");
    printf("%lld\n", total / 8);

    return 0;
}