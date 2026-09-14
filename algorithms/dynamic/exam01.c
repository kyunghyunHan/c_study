#include <stdio.h>
void test02()
{
    /*
   +1
   +2
   +5
   이것만 사용해서 10만들기
   dp[i] = 길이가 i인 바닥을
        1칸 타일과 2칸 타일로 채우는 방법의 수
   ㅇ*/
    int dp[11] = {0};

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 5;
    for (int i = 5; i < 11; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    printf("%d\n", dp[10]);
}
void test01()
{
    int dp[11] = {0};
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    dp[4] = 7;
    dp[5] = 13;

    for (int i = 6; i < 11; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    printf("%d", dp[10]);
}
int main(void)
{
    test02();
    return 0;
}