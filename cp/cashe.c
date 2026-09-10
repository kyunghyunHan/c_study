#include <string.h>
#include <stdio.h>
#define DUMBCORY                \
    for (i = 0; i < 65536; i++) \
    destination[i] = source[i]

#define SMARTCOPY memcpy(destination, source, 65536);
union
{
    char a[10]; // 원래 1바이트씩 증가
    int i;

} u;

// struct node *p, *start, *tmp;
int main(void)
{
    /*현재 u.ap[1]가 1001인데 1004가 아니라 에러
    일반적으로 바이트배열이면 memcpy사용
    */
    int *p = (int *)&(u.a[1]);
    *p = 17; //*p에 저장된 정렬이 잘못된 주소로 인해 버스오류
    char source[65536], destination[65536];
    int i, j;
    for (j = 0; j < 100; j++)
    {
        SMARTCOPY;
    }
    printf("%d", *p);
}
