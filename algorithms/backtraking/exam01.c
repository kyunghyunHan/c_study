#include <stdio.h>
int arr[2] = {0};
/*백트레킹 */
void test01(int l)
{
    if (l == 2)
    {
        printf("%d %d\n", arr[0], arr[1]);
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        arr[l] = i;
        test01(l + 1);
    }
}
int main(void)
{
    test01(0);
    return 0;
}