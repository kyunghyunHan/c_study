#include <stdio.h>
int main(void)
{
    int a, b;
    int arr[100] = {0};
    char *str = "No";
    scanf("%d %d", &a, &b);
    for (int i = 0; i < a; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] == b)
        {
            str = "Yes";
            break;
        }
    }
    printf("%s\n", str);
    return 0;
}