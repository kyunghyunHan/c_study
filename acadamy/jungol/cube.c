/*
큐브돌리기

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char cube[6][3][3];
char arr[6][3][3];
char color[6] = {'w', 'y', 'r', 'o', 'g', 'b'};
/*

위   0
아래 1
앞 2
뒤 3
왼 4
오 5

w:휜
y:노
r:
o
g
b

+는 시계방향
- 는 반시계방향
*/
void f(char ss)
{
    // printf("%c\n", ss);

    if (ss == 'U')
    {
        // 어케돌리니
        /*
        123
        456
        789

            2 1 0
            0 1 2

        741   i+2  i+1  i
              j    j    j

        852   i+2  i+1  i
              j+1  j+1  j+1

        963   i+2  i+1  i
              j+2  j+2  j+2





              1 2 3 -> 7 8 9 ->
              4 5 6    4 5 6
              7 8 9    7 8 9
        */

        char temp[3][3];
        memcpy(temp, cube[0], sizeof(temp));

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[0][i][j] = temp[2 - j][i];
            }
        }

        // 주변 4면 회전
        char qq[3];

        // 원래 F 윗줄 보관
        memcpy(qq, cube[2][0], 3); // F 저장

        memcpy(cube[2][0], cube[5][0], 3); // F ← R
        memcpy(cube[5][0], cube[3][0], 3); // R ← B
        memcpy(cube[3][0], cube[4][0], 3); // B ← L
        memcpy(cube[4][0], qq, 3);         // L ← F
    }
    if (ss == 'D')
    {
        char temp[3][3];
        memcpy(temp, cube[1], sizeof(temp));

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[1][i][j] = temp[2 - j][i];
            }
        }

        char qq[3];
        memcpy(qq, cube[2][2], 3);
        memcpy(cube[2][2], cube[4][2], 3);
        memcpy(cube[4][2], cube[3][2], 3);
        memcpy(cube[3][2], cube[5][2], 3);
        memcpy(cube[5][2], qq, 3);
    }
    // 앞
    if (ss == 'F')
    {
        char temp[3][3];
        memcpy(temp, cube[2], sizeof(temp));

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[2][i][j] = temp[2 - j][i];
            }
        }

        char qq[3];
        char dd[3];
        char rr[3];

        memcpy(qq, cube[0][2], 3);
        // 앞->2 왼쪽 4

        for (int i = 0; i < 3; i++)
        {
            dd[i] = cube[4][i][2];

            rr[i] = cube[5][i][0]; // 추가
        }

        for (int i = 0; i < 3; i++)
        { // 위       //왼
            cube[0][2][i] = dd[2 - i];

            // 왼쪽
            cube[4][i][2] = cube[1][0][i];
            // 아래        //오른쪽
            cube[1][0][i] = rr[2 - i]; // 여기만 변경

            cube[5][i][0] = qq[i];
            // 오른쪽
        }
    }
    if (ss == 'B')
    {
        char temp[3][3];
        memcpy(temp, cube[3], sizeof(temp));

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[3][i][j] = temp[2 - j][i];
            }
        }

        char qq[3];
        char dd[3];

        memcpy(qq, cube[0][0], 3);
        for (int i = 0; i < 3; i++)
        {
            dd[i] = cube[1][2][i];
        }
        for (int i = 0; i < 3; i++)
        {
            // 위 오
            cube[0][0][i] = cube[5][i][2];

            // 오 아래
            cube[5][i][2] = dd[2 - i];
            // 아래 왼
            cube[1][2][i] = cube[4][i][0];

            // 왼쪽   위 (역순)
            cube[4][i][0] = qq[2 - i];
        }
    }
    if (ss == 'L')
    {
        // L면 자체 회전
        char temp[3][3];
        memcpy(temp, cube[4], sizeof(temp));

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[4][i][j] = temp[2 - j][i];
            }
        }
        // u의 왼쪽
        char ull[3];
        char back[3];
        char down[3];
        // 값뺴놓기
        for (int i = 0; i < 3; i++)
        {
            ull[i] = cube[0][i][0];
            back[i] = cube[3][i][2];
            down[i] = cube[1][i][0];
        }

        for (int i = 0; i < 3; i++)
        {
            cube[0][i][0] = back[2 - i];

            cube[3][i][2] = down[2 - i]; // 변경

            cube[1][i][0] = cube[2][i][0];

            cube[2][i][0] = ull[i];
        }
    }
    if (ss == 'R')
    {
        char temp[3][3];
        memcpy(temp, cube[5], sizeof(temp));

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[5][i][j] = temp[2 - j][i];
            }
        }

        char qq[3];
        char back[3];

        for (int i = 0; i < 3; i++)
        {
            qq[i] = cube[0][i][2];
            back[i] = cube[3][i][0];
        }

        for (int i = 0; i < 3; i++)
        {
            cube[0][i][2] = cube[2][i][2];

            cube[2][i][2] = cube[1][i][2];

            cube[1][i][2] = back[2 - i];

            cube[3][i][0] = qq[2 - i];
        }
    }
}

int main(void)
{
    freopen("data.txt", "r", stdin);
    int t;
    scanf("%d", &t);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cube[i][j][k] = color[i];
            }
        }
    }

    memcpy(arr, cube, sizeof(arr));

    for (int i = 0; i < t; i++)
    {
        memcpy(cube, arr, sizeof(arr));

        int n;
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            char s[3];
            int cnt;
            scanf("%2s", s);
            // printf("%c", s[1]);
            if (s[1] == '+')
            {
                cnt = 1;
            }
            else
            {
                cnt = 3;
            }
            for (int i = 0; i < cnt; i++)
            {
                f(s[0]);
            }
        }
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                printf("%c", cube[0][y][x]);
            }
            printf("\n");
        }
    }

    return 0;
}