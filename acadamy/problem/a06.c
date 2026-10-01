/*1차원 누적합

10 20 30 40
l=2 ,r=4
원하는건 2~4
2 3 4

*/
#include <stdio.h>
#define MAX 100009
int arr[MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        int a;
        scanf("%d", &a);
        arr[i] += arr[i - 1] + a;
    }
    for (int i = 1; i <= q; i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        // printf("%d\n", arr[r] - arr[l]);
        // 10 + 20 + 30 + 40
        //-
        // 10
        printf("%d\n", arr[r] - arr[l - 1]);
    }

    return 0;
}