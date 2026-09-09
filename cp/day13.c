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

    if (scanf("%d %d", &row, col) != 2 || row <= 0 || *col <= 0)
        return 0;

    *stu = (Student *)calloc(row, sizeof(Student));
    if (*stu == NULL)
        return 0;

    for (int i = 0; i < row; i++)
    {
        Student *sp = *stu + i;
        sp->score = (int *)malloc(sizeof(int) * (*col));
        if (sp->score == NULL || scanf("%d", &sp->id) != 1)
        {
            free(sp->score);
            sp->score = NULL;
            break;
        }

        int j;
        for (j = 0; j < *col; j++)
        {
            if (scanf("%d", sp->score + j) != 1)
                break;
        }

        if (j != *col || scanf("%19s", sp->name) != 1)
        {
            free(sp->score);
            sp->score = NULL;
            break;
        }

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
    int row;
    int count = 0;

    if (scanf("%d %d", &row, col) != 2 || row <= 0 || *col <= 0)
        return 0;

    size_t student_size = sizeof(Student) * row;
    size_t score_size = sizeof(int) * row * (*col);

    *stu = (Student *)malloc(student_size + score_size);
    if (*stu == NULL)
        return 0;

    int *score = (int *)(*stu + row);

    for (int i = 0; i < row; i++)
    {
        Student *sp = *stu + i;
        sp->score = score + i * (*col);

        if (scanf("%d", &sp->id) != 1)
            break;

        int j;
        for (j = 0; j < *col; j++)
        {
            if (scanf("%d", sp->score + j) != 1)
                break;
        }

        if (j != *col || scanf("%19s", sp->name) != 1)
            break;

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

#if 1
int main(void)
{
    uintptr_t a;
    int arr[5] = {1, 2, 3, 4, 5};

    // 8바이트 주소를 int에 넣어서 오류남
    // a = (int)arr;
    a = (uintptr_t)arr;
    printf("%d\n", ((int *)a)[2]);
    return 0;
}
#endif