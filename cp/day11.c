#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if 0

else if(numLog[i]-numLog[i-1]==10){
             answer[index] = 'd';
        }
#endif

#if 0
int main(void)
{
    int *arr = malloc(sizeof(int) * 12);
    // arr = (*int)calooc(12,sizeof(*arr))
    for (int i = 0; i < 12; i++)
    {
        *(arr + i) = i;
    }

    for (int i = 0; i < 12; i++)
    {
        printf("%d\n", *(arr + i));
    }
    free(arr);
    arr = NULL;
    return 0;
}
#endif

#if 0

int main(void)
{
    int **arr = malloc(sizeof(*arr) * 3);
    int index = 0;

    for (int i = 0; i < 3; i++)
    {
        arr[i] = malloc(sizeof(*arr[i]) * 4);

        for (int j = 0; j < 4; j++)
        {
            *(*(arr + i) + j) = index++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++)
    {
        free(arr[i]);
    }

    free(arr);
    arr = NULL;

    return 0;
}

#endif

#if 0
int main(void)
{
    char *str = (char *)malloc(sizeof(char) * 21);
    strcpy(str, "aa");
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%c", *(str + i));
    }
    free(str);
    str = NULL;
    return 0;
}
#endif

#if 0
int main(void)
{
    char *arr[5] = {0};
    char temp[80] = {0};

    for (int i = 0; i < SIZE(arr); i++)
    {
        gets(temp);
        arr[i] = (char *)calloc(strlen(temp) + 1, sizeof(char));
        if (arr[i] == 0)
        {
            exit(0);
        }
        strcpy(arr[i], temp);
    }
    for (int i = 0; i < SIZE(arr); i++)
    {
        printf("%s\n", arr[i]);
    }
    for (int i = 0; i < SIZE(arr); i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    return 0;
}
#endif
#if 0
int main(void)
{
    char *str = malloc(400);
    char temp[80];

    if (str == NULL)
    {
        return 1;
    }

    char *p = str;

    for (int i = 0; i < 5; i++)
    {
        gets(temp);
        size_t len = strlen(temp);
        strcpy(p, temp);
        p += len;
        *p++ = '\n';
    }

    *p = '\0';

    printf("%s", str);

    free(str);

    return 0;
}
#endif

#if 0
int main(void)
{
    enum
    {
        row_count = 5,
        input_size = 80
    };

    char *arr[row_count] = {NULL};
    size_t offset[row_count] = {0};
    char *buffer = malloc(row_count * input_size);
    char *current = buffer;

    if (buffer == NULL)
    {
        fprintf(stderr, "메모리 할당에 실패했습니다.\n");
        return 1;
    }

    for (int i = 0; i < row_count; i++)
    {
        offset[i] = (size_t)(current - buffer);
        arr[i] = current;

        if (fgets(arr[i], input_size, stdin) == NULL)
        {
            fprintf(stderr, "문자열 입력에 실패했습니다.\n");
            free(buffer);
            return 1;
        }

        arr[i][strcspn(arr[i], "\n")] = '\0';
        current += strlen(arr[i]) + 1;
    }

    size_t used_size = (size_t)(current - buffer);
    char *p = realloc(buffer, used_size);

    if (p == NULL)
    {
        fprintf(stderr, "메모리 재할당에 실패했습니다.\n");
        free(buffer);
        return 1;
    }

    buffer = p;

    // realloc으로 주소가 바뀌었을 수 있으므로 포인터를 다시 설정한다.
    for (int i = 0; i < row_count; i++)
    {
        arr[i] = buffer + offset[i];
    }

    for (int i = 0; i < row_count; i++)
    {
        printf("%s\n", arr[i]);
    }

    free(buffer);
    buffer = NULL;

    return 0;
}

#endif

#include "day09_lib.h"

// 10���� �Լ������� ����
#if 0

int get_menu(void) {
    int menu;
    printf("1. ����\n");
    printf("2. ����\n");
    printf("3. ����\n");
    printf("4. ������(��)\n");
    printf("5. ������(������)\n");
    printf("0. ����\n");

    printf("�޴� ���� : ");
    (void)scanf("%d", &menu);
    return menu;
}

int main(void) {
    int menu;
    int x, y;

    int (*func[6])(int, int) = { 0, add, sub, mul, divi, mod };

    while (menu = get_menu()) {
        printf("�� ���� �Է� : ");
        (void)scanf("%d %d", &x, &y);
        printf("��� : %d\n\n", func[menu](x, y));
    }

    return 0;
}

#endif

// 10���� 2���� �迭 ���� ���� - qsort Ȱ��
#if 0
int comp2D(const void* a, const void* b) {
    int *rowA = *(int(*)[3])a;
    int *rowB = *(int(*)[3])b;

    for (int i = 0; i < 3; ++i) {
        if (rowA[i] > rowB[i]) {
            return 1;
        }
        if (rowA[i] < rowB[i]) {
            return -1;
        }
    }
    return 0;
}
int compare2D(const void* a, const void* b) {
    int* x = (int*)a;
    int* y = (int*)b;
    for (int i = 0; i < 3; ++i) {
        if (*(x + i) > *(y + i)) return 1;
        if (*(x + i) < *(y + i)) return -1;
    }
    return 0;
}


//int (*)[3]�� 2�������� �� ���� ����Ű�� ������
//int** �� �� ���� ù��° ��Ұ��� �ּҰ����� �����ϴ� ������
//int* �� ���� ù��° ��Ҹ� ����Ű�� ������
int comparr01(const void* a, const void* b) {
    int ia = (*(int (*)[3])a)[0];
    int ib = (*(int (*)[3])b)[0];
    if (ia == ib) return 0;
    if (ia > ib) return 1;
    return -1;
}

// �� ������ �߻��ұ�
// int **�� a�� ����� a�� �ִ� ���� int *�� �����ϰ� �������Ϸ� �ϱ� ������ ������ �߻��Ѵ�.
int comparr02(const void* a, const void* b) {
    int ia = **(int **)a;
    int ib = **(int **)b;
    if (ia == ib) return 0;
    if (ia > ib) return 1;
    return -1;
}

int comparr03(const void* a, const void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia == ib) return 0;
    if (ia > ib) return 1;
    return -1;

}
void print_2Darray(int (*arr)[3], int r, int c) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main(void) {
    int arr[5][3] = {
        {3, 5, 1},
        {1, 4, 3},
        {7, 1, 5},
        {3, 2, 2},
        {5, 3, 4}
    };

    print_2Darray(arr, SIZE(arr), SIZE(arr[0]));
    qsort(arr, SIZE(arr), sizeof(*arr), comparr03);
    print_2Darray(arr, SIZE(arr), SIZE(arr[0]));

    return 0;
}

#endif

//  ����ü �迭 ���
#if 0

typedef struct {
    char* name;
    char* sign;
    int(*func)(int, int);
}op_t;

void print_arr(op_t* p, int menu_size) {
    for (int i = 1; i < menu_size; ++i) {
        printf("%d. %s\n", i, p[i].name);
    }
    printf("0. %s\n", p[0].name);
    printf("\n");
}
int get_menu(op_t *menu, int n) {
    int id = 0;
    print_arr(menu, n);
    (void)scanf("%d", &id);
    return id;
}
int main(void) {
    int a, b, id = 0;
    op_t menu[6] = {
        {"����"},
        {"����","+",add},
        {"����","-",sub},
        {"����","*",mul},
        {"������(��)","/",divi},
        {"������(������)","%",mod},
    };
    op_t* op_ptr = NULL;
    while(id = get_menu(menu, SIZE(menu))){
        op_ptr = &menu[id];
        printf("�� ���� �Է� : ");
        (void)scanf("%d %d", &a, &b);
        printf("����� %d %s %d = %d�Դϴ�.\n\n", a, op_ptr->sign, b, op_ptr->func(a, b));
    };

    printf("���α׷��� �����մϴ�.\n");
    return 0;
}
#endif

// �޸� ���� �Ҵ� - ū ũ���� �޸� �ʿ�� ���
#if 0
int arr[10000][10000] = { 0 };  // ������ ���������� �Ѱ谡 ����

int main(void) {
    //int arr[1000][1000] = { 0 };  // �Ұ���
    printf("%.3fM\n", sizeof(arr)/1024/(double)1024);
    return 0;
}
#endif

// �����޸� �Ҵ� - malloc, calloc, realloc
#if 00
// void print_1Darray(int* arr, int n) {
//     for (int i = 0; i < n; ++i) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
// }
int main(void)
{
    int *a = 0;
    int *b = 0;
    int *c = 0;
    a = (int *)malloc(80 * sizeof(*a));
    if (a == NULL)
    {
        return -1;
    }
    b = (int *)calloc(80, sizeof(*a));
    if (b == NULL)
    {
        return -1;
    }
    c = (int *)realloc(NULL, 80);
    if (c == NULL)
    {
        return -1;
    }
    printf("%p %p %p\n", a, b, c);
    print_1Darray(a, 10);
    print_1Darray(b, 10);
    print_1Darray(c, 10);
    free(a);
    free(b);
    free(c);
    a = NULL;
    free(a);
    return 0;
}
#endif

// 12�� int�� ��ҷ� �ϴ� int �迭 �����
#if 0
#define MAX (12)
int main(void) {
    int * arr = NULL;

    arr = (int *)calloc(MAX, sizeof(*arr));
    if (arr == NULL) {
        // ���ҽ� ���� ��ġ
        exit(0);
    }
    for (int i = 0; i < MAX; ++i) {
        arr[i] = i + 1;
    }
    print_1Darray(arr, MAX);
    free(arr);
    arr = NULL;
    return 0;
}
#endif

// 2�����迭 �����
#if 0
#define R (3)
#define C (4)

void print_2Darray(int (*arr)[C], int r, int c) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main(void) {
    int(*arr)[C] = NULL;
    printf("%d\n", sizeof(*arr));
    arr = (int(*)[C])calloc(R, sizeof(*arr));
    if (arr == NULL) {
        // ���ҽ� ���� ��ġ
        exit(0);
    }
    //for (int i = 0; i < R*C; ++i) {
    //    ((int*)arr)[i] = i + 1;
    //}
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            arr[i][j] = i*C + j + 1;
        }
    }
    print_2Darray(arr, R, C);
    free(arr);
    arr = NULL;
    return 0;
}
#endif

// char �迭 �����
// 1�� ���ڿ� ����
#if 0
#define MAX (20)
int main(void) {
    char* str = NULL;

    str = (char*)malloc(20 * sizeof(*str));
    if (str == NULL) {
        exit(0);
    }
    (void)scanf("%s", str);
    printf("%s\n", str);
    printf("%d %d\n", strlen(str), sizeof("water"));
    free(str); str = NULL;
    return 0;
}
#endif

//  ���� �迭
#if 0

int main(void) {
    char* arr[5] = { 0 };
    char temp[80] = { 0 };

    for (int i = 0; i < SIZE(arr); ++i) {
        gets(temp);
        arr[i] = (char*)calloc(strlen(temp) + 1, sizeof(char));
        if (arr[i] == 0) {
            exit(0);
        }
        strcpy(arr[i], temp);
    }
    for (int i = 0; i < SIZE(arr); ++i) {
        printf("%s\n", arr[i]);
    }
    for (int i = 0; i < SIZE(arr); ++i) {
        free(arr[i]);
        arr[i] = NULL;
    }
    return 0;
}
#endif

#if 1
int main(void)
{
    char *arr[5] = {0};
    // 각 문자열의 시작 주소가 arr[0]에서 몇 바이트 떨어져 있는지
    size_t size_arr[5] = {0};

    arr[0] = (char *)malloc(5 * 80);
    if (arr[0] == NULL)
    {
        exit(0);
    }
    // 5개를 한번에 받고
    for (int i = 0; i < 5; ++i)
    {
        if (i > 0)
        {
            arr[i] = arr[i - 1] + strlen(arr[i - 1]) + 1;
        }

        gets(arr[i]);

        // arr[i]가 arr[0]에서 몇 바이트 떨어져 있는지 저장
        size_arr[i] = arr[i] - arr[0];
    }

    // 실제 사용한 크기
    // 마지막 주소 에서 - 처음주소
    size_t used =
        (arr[4] + strlen(arr[4]) + 1) - arr[0];
    // 그만큼할당
    char *p = realloc(arr[0], used);

    if (p == NULL)
    {
        free(arr[0]);
        return 1;
    }
    // arr 이 P 의주소를 바라보게
    arr[0] = p;
    // 값 재할당 문자열의 주소를 다시 잡아줘야
    for (int i = 1; i < 5; ++i)
    {
        arr[i] = arr[0] + size_arr[i];
    }
    // 재할당
    for (int i = 0; i < 5; ++i)
    {
        printf("%s\n", arr[i]);
    }

    free(arr[0]);
    arr[0] = NULL;

    return 0;
}
#endif