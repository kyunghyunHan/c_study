/*
떡 먹는 호랑이
*/

int main(void)
{
    int a = 6, b = 41;
    int dp[100000];

    dp[0] = 0;

    for (int i = 1; i <= 30; i++)
    {
        for (int j = i; j <= 30; j++)
        {
            dp[i] = dp[i] + dp[i - 1];
            if (dp[i] > b)
            {
                break;
            }
            if (dp[i] == b)
            {
                printf("%d %d", i, j);
                return;
            }
        }
    }
    return 0;
}