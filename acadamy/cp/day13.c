#include <stdio.h>
#include <stdlib.h>

#if 0
typedef struct student
{
    int id;
    int *score;
    char name[20];
} Student;
int input_data(Student **stu, int *col)
{

    int row;
    int count = 0;
    // row col 받고
    // scanf는 입력받은 개수를 가져옴 2개가 아니면 실패
    if (scanf("%d %d", &row, col) != 2 || row <= 0 || *col <= 0)
        return 0;
    // row 만큼 메모리할당 0으로
    *stu = (Student *)calloc(row, sizeof(Student));
    if (*stu == NULL)
        return 0;
    // row만큼
    for (int i = 0; i < row; i++)
    {
        // i 번째 stu 배열에 scroe에 메모리 할당 col만큼
        Student *sp = *stu + i;
        sp->score = (int *)malloc(sizeof(int) * (*col));
        // sp->scroe 이 NULL이거나 값을 못받앗으면 할당헤제
        if (sp->score == NULL || scanf("%d", &sp->id) != 1)
        {
            free(sp->score);
            sp->score = NULL;
            break;
        }
        // j번 반복해서 score에 입력값
        int j;
        for (j = 0; j < *col; j++)
        {
            if (scanf("%d", sp->score + j) != 1)
                break;
        }
        // j가 col만큼 안햇거나 scanf name이 할당 안댓으면 할당 해제
        if (j != *col || scanf("%19s", sp->name) != 1)
        {
            free(sp->score);
            sp->score = NULL;
            break;
        }
        // 카운터 증가
        count++;
    }

    return count;
}
void print_data(Student *stu, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        Student *sp = stu + i;
        printf("%d", sp->id);
        for (int j = 0; j < col; j++)
            printf(" %d", sp->score[j]);
        printf(" %s\n", sp->name);
    }
}
int main(void)
{
    Student *stu = NULL;
    int count;
    int col;

    (void)freopen("cp/student.txt", "r", stdin);
    count = input_data(&stu, &col);
    print_data(stu, count, col);

    for (int i = 0; i < count; i++)
        free(stu[i].score);
    free(stu);
    return 0;
}
#endif
// 숙제
#if 0

typedef struct student
{
    int id;
    int *score;
    char name[20];
} Student;

int input_data(Student **stu, int *col)
{
    int row;       // 학생 수
    int count = 0; // 실제 입력에 성공한 학생 수

    if (scanf("%d %d", &row, col) != 2 || row <= 0 || *col <= 0)
        return 0;

    // Student 구조체 row개를 저장하기 위해 필요한 크기
    size_t student_size = sizeof(Student) * row;
    size_t score_size = sizeof(int) * row * (*col);

    *stu = (Student *)malloc(student_size + score_size);

    // 동적 메모리 할당 실패
    if (*stu == NULL)
        return 0;

    /*
        *stu + row

        *stu는 Student *
        따라서 row만큼 이동하면 Student 배열 바로 뒤를 가리킴.

        Student 영역이 끝난 위치를 int *로 캐스팅해서
        점수 배열의 시작 주소로 사용한다.
    */
    // stu+row만큼 이동해서 score 변수할당
    int *score = (int *)(*stu + row);

    // 학생 row명 입력
    for (int i = 0; i < row; i++)
    {
        // i번째 Student의 주소
        //
        // *stu + i
        // == &(*stu)[i]
        Student *sp = *stu + i;

        /*
       [Student0][Student1][Student2][점수0~14]
        */
        // 스코어는 시작주소를 저장 (score+1*col)
        // 학생 0은 학생0은 score[0]부터 시작.
        // 학생 1은 score[5]부터 시작
        sp->score = score + i * (*col);

        // 학생 번호 입력
        if (scanf("%d", &sp->id) != 1)
            break;

        int j;

        // 현재 학생의 과목별 점수 입력
        for (j = 0; j < *col; j++)
        {
            /*
                sp->score + j
                == &sp->score[j]

                scanf의 %d는 int *가 필요하므로
                점수를 저장할 주소를 전달
            */
            if (scanf("%d", sp->score + j) != 1)
                break;
        }

        /*
            j != *col
            → 필요한 점수 개수만큼 입력하지 못함

            scanf("%19s", sp->name) != 1
            → 이름 입력 실패

            둘 중 하나라도 실패하면 현재 학생 입력 중단
       
            참고:
            ||는 단락 평가(short-circuit)를 하기 때문에
            j != *col이 참이면 뒤의 scanf는 실행하지 않음.
        */
        if (j != *col || scanf("%19s", sp->name) != 1)
            break;

        // 이 학생의 모든 입력이 성공했으므로 학생 수 증가
        count++;
    }

    // 실제로 정상 입력된 학생 수 반환
    return count;
}

// 입력받은 학생 데이터를 출력하는 함수
void print_data(Student *stu, int row, int col)
{
    // 정상 입력된 학생 수만큼 반복
    for (int i = 0; i < row; i++)
    {
        // i번째 학생 주소
        Student *sp = stu + i;

        // 학생 번호 출력
        printf("%d", sp->id);

        // 해당 학생의 모든 점수 출력
        for (int j = 0; j < col; j++)
            printf(" %d", sp->score[j]);

        // 학생 이름 출력
        printf(" %s\n", sp->name);
    }
}

int main(void)
{
    // Student 배열의 시작 주소를 저장할 포인터
    // input_data에서 malloc한 주소를 받아옴
    Student *stu = NULL;

    // 실제 입력에 성공한 학생 수
    int count;

    // 학생 한 명당 과목 수
    int col;

    // 키보드(stdin) 대신 student.txt 파일에서 입력받도록 변경
    (void)freopen("./student.txt", "r", stdin);

    /*
        &stu를 넘기는 이유:

        stu의 타입    : Student *
        &stu의 타입   : Student **

        input_data 안에서

        *stu = malloc(...);

        을 통해 main의 stu 자체를 변경하기 위함.
    */
    count = input_data(&stu, &col);

    // 실제 입력에 성공한 학생들만 출력
    print_data(stu, count, col);

    /*
        malloc은 딱 한 번 했으므로 free도 한 번만 하면 됨.

        Student 배열과 모든 score 배열이
        하나의 메모리 블록 안에 들어있음.

        따라서 sp->score를 각각 free하면 안 됨.
    */
    free(stu);

    return 0;
}

#endif
#if 0
#include <stdlib.h>

#define SIZE(a) (sizeof(a) / sizeof((a)[0]))

typedef struct Color1
{

} Color1;
typedef struct Color2
{

} Color2;

int main(void)
{
    Color1 a = {0};
    Color2 a = {0};
    return 0;
}
#endif

#if 1

typedef struct IP
{
    unsigned int verion : 4;
    unsigned int hl : 4;
    uint8_t tos : 8;
    uint16_t total_length;
    uint16_t id;
    unsigned int x : 1;
    unsigned int d : 1;
    unsigned int m : 1;
    unsigned int fo : 13;
    uint8_t ttl;
    uint8_t protocal;
    uint16_t hc;
    uint32_t sa;
    uint32_t da;
    uint32_t IPO;
} IP;

typedef struct RGB
{
    unsigned short blue : 5;
    unsigned short green : 6;
    unsigned short red : 5;

} RGB;

typedef union pixelcolor
{
    RGB rgb;
    unsigned short color;
} Color;

/*
0x1234 = 00010/010001/10100

10100 -> 20
010001 -> 17
00010 -> 2

*/
/* data */

#endif

/*

struct bit{
unsigned a: 3;
unsigned b: 3;
unsigned c: 3;
}X

int main(void){
x.a = 2; ->2를 대입하는것이 아니라 x&~7|3 (3비트 clear후 2로 set)연산 수행
x.b = 1;
x.c = 1;

}
*/

#if 0
int main(void)
{
    int a;
    typedef int MYINT;
    MYINT b;

    unsigned int c;
    typedef unsigned int UINT;
    UINT d;

    int *p;
    typedef int *INTP;
    INTP p2;
    return 0;
}
#endif
#if 0

typedef char (*CARY)[10];
typedef int (*PRINT_FN)(CARY, int);

int printAry(CARY ary, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s ", ary[i]);
    }

    printf("\n");
    return 0;
}

int main(void)
{
    char fruit[][10] = {"apple", "melon", "cherry"};

    PRINT_FN fn;
    fn = printAry;
    fn(fruit, sizeof(fruit) / sizeof(fruit[0]));

    return 0;
}
#endif

#if 0
int func(int a, int b)
{
    return a + b;
}
int main(void)
{
    int a = (int)func;

    printf("%d\n", func(3, 4));
    int b = ((int (*)(int, int))a)(3, 4);
    printf("%d\n", b);
    return 0;
}
#endif

#if 0
typedef int (*FP)(int, int);

int func(int a, int b)
{
    return a + b;
}

int main(void)
{
    int a = (int)func;

    // printf("%d\n", func(3, 4));

    int b = ((FP)a)(3, 4);

    printf("%d\n", b);

    return 0;
}

#endif

#if 0
int main(void)
{
    uintptr_t a;
    int arr[5] = {1, 2, 3, 4, 5};

    // 8바이트 주소를 int에 넣어서 오류남
    // a = (int)arr; arr은 8바이트인데 int로 할려니까 에러가 남
    a = (uintptr_t)arr;
    printf("%d\n", ((int *)a)[2]);
    return 0;
}
#endif