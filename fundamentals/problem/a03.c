#include <stdio.h>
#include <stdbool.h>
int main(void)
{
    int n, k;
    int a[100] = {0};
    int q[100] = {0};
    bool ans = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (k == a[i] + q[i])
            {
                ans = true;
                return;
            }
        }
    }
    return 0;
}