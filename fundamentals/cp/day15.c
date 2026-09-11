#include <stdio.h>

enum
{
    N = 5,
    PICK_COUNT = 3,
    NUMBER_MAX = 6,
    TARGET_SUM = 10
};

int arr[PICK_COUNT] = {0};

/* 1 2 3 4 5 */
void test01(int l)
{
    if (l > N)
    {
        return;
    }

    printf("%d ", l);
    test01(l + 1);
}

/* 1 2 3 4 5 5 4 3 2 1 */
void test02(int l)
{
    if (l > N)
    {
        return;
    }

    printf("%d ", l);
    test02(l + 1);
    printf("%d ", l);
}

/* 1 2 3 4 5 4 3 2 1 */
void test03(int l)
{
    if (l == N)
    {
        printf("%d ", l);
        return;
    }

    printf("%d ", l);
    test03(l + 1);
    printf("%d ", l);
}

/* 1 2 3 4 5 1 2 3 4 */
void test04(int l)
{
    if (l > N)
    {
        return;
    }

    printf("%d ", l);
    test04(l + 1);

    if (l > 1)
    {
        printf("%d ", N - l + 1);
    }
}

/*
1~3에서 숫자 3개를 중복을 허용하여 선택한다.

1 1 1
1 1 2
1 1 3
1 2 1
...
*/
void test05(int l)
{
    if (l == PICK_COUNT)
    {
        printf("%d %d %d\n", arr[0], arr[1], arr[2]);
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        arr[l] = i;
        test05(l + 1);
    }
}

/* 1~6에서 서로 다른 숫자 3개를 오름차순으로 선택한다. */
void test06(int l)
{
    if (l == PICK_COUNT)
    {
        printf("%d %d %d\n", arr[0], arr[1], arr[2]);
        return;
    }

    for (int i = 1; i <= NUMBER_MAX; i++)
    {
        if (l > 0 && arr[l - 1] >= i)
        {
            continue;
        }

        arr[l] = i;
        test06(l + 1);
    }
}

/* test06의 조합 중 합이 10인 경우만 출력한다. */
void test07(int l, int sum)
{
    if (l == PICK_COUNT)
    {
        if (sum == TARGET_SUM)
        {
            printf("%d %d %d\n", arr[0], arr[1], arr[2]);
        }
        return;
    }

    for (int i = 1; i <= NUMBER_MAX; i++)
    {
        if (l > 0 && arr[l - 1] >= i)
        {
            continue;
        }

        arr[l] = i;
        test07(l + 1, sum + i);
    }
}

int main(void)
{
    test07(0, 0);

    return 0;
}
