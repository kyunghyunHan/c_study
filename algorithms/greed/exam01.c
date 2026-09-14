#include <stdio.h>
/* 동전 문제  */
void test02()
{
    // 6
    int money = 1260;
    int coins[] = {500, 100, 50, 10};
    int cnt = 0;
    int index = 0;
    while (money > 0)
    {
        if (money >= coins[index])
        {
            money -= coins[index];
            printf("%d\n", money);
            cnt++;
        }
        else
        {
            index++;
        }
    }
    printf("%d", cnt);
}

void test()
{

    int start[] = {1, 3, 0, 5, 8, 5};
    int end[] = {2, 4, 6, 7, 9, 9};
    int last_end = 0;
    int ans = 0;

    for (int i = 0; i < 6; i++)
    {
        if (start[i] >= last_end)
        {
            last_end = end[i];
            ans += 1;
        }
    }
    printf("%d\n", ans);
    /*


회의 시간이 다음과 같이 주어진다.

회의 A : 1 ~ 3
회의 B : 2 ~ 5
회의 C : 4 ~ 6
회의 D : 6 ~ 7


예를 들어 A를 선택하면:

A : 1 ─── 3
B :   2 ───── 5   ← A와 겹침
C :       4 ─── 6
D :             6 ─ 7

일단 코드는 짜지 말고, A, B, C, D 중 어떤 회의들을 선택하면 가장 많이 선택할 수 있을까?
    */
}
int comp(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    return (x < y) - (x > y);
}
void test3()
{
    int arr[] = {2, 4, 1, 7, 3};
    qsort(arr, 5, sizeof(int), comp);
    printf("%d", arr[0] + arr[1] + arr[2]);
    return;
}
int main(void)
{
    test3();
    return 0;
}