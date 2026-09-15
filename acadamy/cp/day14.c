#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

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

#if 0
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

#if 0
int *func(void)
{
    static int a[] = {100, 200, 300};
    return &a;
}
typedef char *(*(*FP)())[10];
void main(void)
{
    int *(*fp)(void) = func;
    // int *를 반환하는 함수의 포인터
    int *(**fpp)(void) = &fp;
    // int * 를 반환하는 함수의 포인터를 가리키는 포인터
    printf("%d\n", fp()[0]);
    // fp 에서 반환한 int 포인터의 첫번쨰 원소
    printf("%d\n", (*fpp)()[0]);
    // fp 에서 반환한 int 포인터의 첫번쨰 원소
    char i = 0;
    // char *(*(*var)())[10];

    FP var = (FP)func;
    // war은 char*[10]를 가리키는 포인터를 반환하는 함수포인터
}

int arr[] = {100};
extern arr2[] = {100};
#endif
jmp_buf buf;

#if 1
void func03(int l)
{
    if (l > 5)
    {
        longjmp(buf, 1);
    }
    printf("%d\n", l);
    func03(l + 1);
}

void func02(int l)
{
    if (l > 5)
        return;

    int arr[10] = {0};
    arr[0] = l;
    printf("%d\n", arr[0]);
    func02(l + 1);
}
void func(int l)
{
    if (l > 5)
        return;

    func(l + 1);
}
// N이 5인경우 func04(1)을 사용해서 5 4 3  2 1푸렭
int N = 5;

void func05(int l)
{
    if (l > N)
        return;
    printf("%d ", l);
    func05(l + 1);
    printf("%d ", l);
}
void func06(int l)
{
    if (l > N)
        return;
    printf("%d", l);
    func06(l + 1);
    if (l < N)
        printf("%d", l);
}
void func07(int l)
{
    if (l > N)
        return;
    printf("%d", l);
    func07(l + 1);
    printf("%d", N - l + 1);
}
void func08(int l)
{
    if (l > N)
        return;
    printf("%d", l);
    func08(l + 1);
    printf("%d", l);
}

void func09(int l)
{
    if (l > N)
        return;

    for (int i = 0; i < l; i++)
    {
        printf("*");
    }
    printf("\n");
    func09(l + 1);
}

static int row = 1;
static int col = 0;

void func091(int l)
{
    if (row > N)
        return;

    if (col < row)
    {
        printf("*");
        col++;
        func091(l + 1);
    }
    else
    {
        printf("\n");
        row++;
        col = 0;
        func091(l + 1);
    }
}

void binary(int n, int bit)
{
    if (bit < 0)
        return;

    binary(n, bit - 1);

    printf("%d ", (n >> bit) & 1);
}

void func10(int n)
{
    if (n < 0)
        return;

    func10(n - 1);

    printf("%d : ", n);
    binary(n, 2); // 2,1,0 → 총 3비트
    printf("\n");
}
int arr[3];

void func11(int L)
{
    if (L == 3)
    {
        printf("%d %d %d\n", arr[0], arr[1], arr[2]);
        return;
    }

    arr[L] = 1; // row
    func11(L + 1);

    arr[L] = 2;
    func11(L + 1);

    arr[L] = 3;
    func11(L + 1);
    arr[L] = 4;
    func11(L + 1);
}

void func12(int L)
{
    if (L == 3)
    {
        printf("%d %d %d\n", arr[0], arr[1], arr[2]);
        return;
    }
    for (int i = 1; i <= 3; i++)
    {
        printf("%d %d %d\n", arr[0], arr[1], arr[2]);

        if ((L < 1 || arr[0] != i) &&
            (L < 2 || arr[1] != i))
        {
            arr[L] = i;
            func12(L + 1);
        }
    }
}
int vec[2];
void func13(int L)
{
    if (L == 2)
    {
        printf("%d %d\n", vec[0], vec[1]);
        return;
    }
    for (int i = 1; i <= 6; i++)
    {
        vec[L] = i; // row
        func13(L + 1);
    }
}
enum
{
    PICK_COUNT = 3,
    NUMBER_MAX = 6,
    TARGET_SUM = 10
};

int used[10] = {0};
int data[PICK_COUNT] = {0};
void func14(int L)
{
    if (L == 3)
    {
        printf("%d %d %d\n", data[0], data[1], data[2]);
        return;
    }
    for (int i = 0; i < 5; i++)
    {
        if (used[i] == 0)
        {
            used[i] = 1;
            data[L] = i + 1;
            func14(L + 1);
            used[i] = 0;
        }
    }
}

typedef struct Node
{
    struct Node *left;
    struct Node *middle;
    struct Node *right;
    int data;
} Node;

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));

    new_node->data = data;
    new_node->left = NULL;
    new_node->middle = NULL;
    new_node->right = NULL;

    return new_node;
}

void func15(Node *root, int L)
{
    if (L == 3)
    {
        // printf("%d %d %d\n", data[0], data[1], data[2]);
        return;
    }

    // 1 선택
    root->left = create_node(1);
    printf("%d ", root->left->data);
    data[L] = 1;
    func15(root->left, L + 1);
    printf("\n");

    // 2 선택
    root->middle = create_node(2);
    printf("%d ", root->middle->data);
    data[L] = 2;
    func15(root->middle, L + 1);

    // 3 선택
    root->right = create_node(3);
    printf("%d ", root->right->data);
    data[L] = 3;
    func15(root->right, L + 1);
}
void test04(void)
{
    int local_used[10] = {0};

    for (int i = 1; i <= 3; i++)
    {
        if (local_used[i] == 1)
        {
            continue;
        }
        local_used[i] = 1;
        for (int j = 1; j <= 3; j++)
        {
            if (local_used[j] == 1)
            {
                continue;
            }
            local_used[j] = 1;
            for (int k = 1; k <= 3; k++)
            {
                if (local_used[k] == 1)
                {
                    continue;
                }
                local_used[k] = 1;
                printf("%d %d %d\n", i, j, k);
                local_used[k] = 0;
            }
            local_used[j] = 0;
        }
        local_used[i] = 0;
    }
}
/* 1~6 중 세 숫자를 선택해 합이 10인 경우를 출력한다. */
void print_data(void)
{
    for (int i = 0; i < PICK_COUNT; i++)
    {
        printf("%d%c", data[i], i == PICK_COUNT - 1 ? '\n' : ' ');
    }
}

/* 중복 선택 허용 */
void test05(int depth, int sum)
{
    if (depth == PICK_COUNT)
    {
        if (sum == TARGET_SUM)
        {
            print_data();
        }
        return;
    }

    for (int number = 1; number <= NUMBER_MAX; number++)
    {
        data[depth] = number;
        test05(depth + 1, sum + number);
    }
}

/* 같은 숫자의 중복 선택 금지 */
void test06(int depth)
{
    if (depth == PICK_COUNT)
    {
        int sum = data[0] + data[1] + data[2];

        if (sum == TARGET_SUM)
        {
            print_data();
        }
        return;
    }

    for (int number = 1; number <= NUMBER_MAX; number++)
    {
        int index = number - 1;

        if (used[index] == 1)
        {
            continue;
        }

        used[index] = 1;
        data[depth] = number;
        test06(depth + 1);
        used[index] = 0;
    }
}

int count = 0;

/* test06처럼 중복을 막고, 현재 합과 함수 호출 횟수도 함께 관리한다. */
void test07(int depth, int sum)
{
    count++;

    if (depth == PICK_COUNT)
    {
        if (sum == TARGET_SUM)
        {
            print_data();
        }
        return;
    }

    for (int number = 1; number <= NUMBER_MAX; number++)
    {
        int index = number - 1;

        if (used[index] == 1)
        {
            continue;
        }

        used[index] = 1;
        data[depth] = number;
        test07(depth + 1, sum + number);
        used[index] = 0;
    }
}

/* 중복 선택을 허용하며, 현재 합을 재귀 호출로 전달한다. */
void func21(int depth, int sum)
{
    if (depth == PICK_COUNT)
    {
        if (sum == TARGET_SUM)
        {
            print_data();
        }
        return;
    }

    for (int number = 1; number <= NUMBER_MAX; number++)
    {
        data[depth] = number;
        func21(depth + 1, sum + number);
    }
}

int main(void)
{
    func21(0, 0);

    return 0;
}
#endif
