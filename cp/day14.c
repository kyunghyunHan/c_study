#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#if 0
#ifdef __APPLE__
#define DATADIR "/usn1/data"
#else
#define DATADIR "\use\data"
#endif
#define SUMXY x + y
#define MUL1(x, y) x *y
#define MUL2(x, y) ((x) * (y))

int main(void)
{
    int x = 10, y = 20;
    int a = 100, b = 200;

    printf("x+y=%d\n", SUMXY);
    printf("a+b=%d\n", SUMXY);
    printf("%d\n", 30 / MUL1(2, 5));
    printf("%d\n", 30 / MUL2(2, 5)); // 먼저 처리가 댐
    printf("%d\n", 300 / MUL1(2, 5));
}
#endif

#if 0
int main()
{
    /*
    fsseek() ->파일에도위치이동
    ftell()->현재 위치가 몇 바이트인지 확인
    malloc()->그만큼 메모리 확보
    fread()파일 내용을 확보한 메모리로 복사
    fread(저장할_주소, 원소_하나의_크기, 원소_개수, 읽을_파일);
    feskk(fp,0,SEEK_END) 파일 끝으로 이동
    */
    FILE *fp = fopen("student.txt", "r");

    if (fp == NULL)
    {
        printf("파일 열기 실패\n");
        return 1;
    }

    /* 파일 끝으로 이동 */
    fseek(fp, 0, SEEK_END);

    /* 파일 크기 */
    long size = ftell(fp);

    /* 다시 파일 처음으로 */
    fseek(fp, 0, SEEK_SET);

    /* 파일 크기 + '\0' 공간 */
    char *buffer = malloc((size_t)size + 1);

    if (buffer == NULL)
    {
        fclose(fp);
        return 1;
    }

    /* 파일 전체 읽기 */
    size_t n = fread(buffer, 1, (size_t)size, fp);

    /* C 문자열로 만들기 */
    buffer[n] = '\0';

    /* =========================
       여기부터 문자열 파싱
       ========================= */

    int row = 0;
    int col = 0;
    int pos = 0;

    /* row, col을 읽고 몇 글자 읽었는지도 저장 */
    sscanf(buffer, "%d %d%n", &row, &col, &pos);

    printf("row = %d\n", row);
    printf("col = %d\n", col);
    printf("pos = %d\n", pos);

    /*
        buffer
        ↓
        5 3\n1 90 86 78 TOM...
           ↑
           buffer + pos
    */

    char *cursor = buffer + pos;

    /* 공백과 개행 건너뛰기 */
    while (*cursor == ' ' || *cursor == '\n')
    {
        cursor++;
    }

    /* 첫 번째 학생의 id 읽기 */
    int id = 0;
    int used = 0;

    sscanf(cursor, "%d%n", &id, &used);

    /* 읽은 만큼 cursor 이동 */
    cursor += used;

    printf("id = %d\n", id);

    free(buffer);
    fclose(fp);

    return 0;
}
#endif
#if 0
#define string(x) printf(#x " is %d\n", (x))
#define charr(x) printf("%s is %d\n", #x, x)
#define concat(x, y) printf(#x #y " is %d\n", x##y)

int main(void)
{
    int s = 10, c = 97, ca = 7, cb = 9;
    string(s);
    charr(c);
    concat(c, a);
    concat(c, b);
    return 0;
}

struct pid_tag
{
    unsigned int innactive : 1;
    unsigned int : 1;/*패딩용 1비트 */
};
union secondary{
    char has_fur;
};
#endif

#if 1
#include <stdio.h>
#include <assert.h>
#define NDEBOG
int main()
{
    int x;

    printf("\nEnter an integer value: ");
    (void)scanf("%d", &x);

    assert(x >= 0);

    printf("You entered %d.", x);

    return (0);
}
#endif

/*
char * const * (*next) ()

    next는 char을 가리키는 가리키는 상수 포인터에 대한 포인터를 반환하는 함수 포인터

*/

/*
c 는 char을 가리키는 포인터를 반환하고 매개변수를 이중포인터를 받는 함수의 포인터를 10개 저장하는 배열
*/