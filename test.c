#include "acadamy/cp/02_cll.h"
char text[100001] = {0};
int main(void)
{

    char cmd, ch;
    int n;

    (void)scanf("%s", text);
    (void)scanf("%d", &n);
    printf("%s %d\n", text, n);
    for (int i = 0; i < n; i++)
    {
        (void)scanf(" %c", &cmd);
        printf("%c\n", cmd);
        if (cmd == 'P')
        {
            (void)scanf(" %c", &ch);
            printf("%c\n", ch);
        }
        if (cmd == 'L')
        {
            printf("%c\n", ch);
        }
        if (cmd == 'D')
        {
            printf("%c\n", ch);
        }
        if (cmd == 'B')
        {
            printf("%c\n", ch);
        }
    }

    return 0;
}