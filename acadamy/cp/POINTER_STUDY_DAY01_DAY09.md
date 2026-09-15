# C 포인터 정리: Day 01 ~ Day 09

이 문서는 `cp/day1.c`부터 `cp/day09.c`와 각 `*_lib.c`, `*_lib.h`에 나온 포인터 내용을 공부하기 쉽게 정리한 자료다.

> 핵심 한 문장: 포인터는 **값이 저장된 메모리의 주소를 저장하는 변수**다.

---

## 0. 먼저 기억할 기호

```c
int n = 10;
int *p = &n;
```

| 표현 | 의미 | 타입/값 |
|---|---|---|
| `n` | 변수에 저장된 값 | `int`, 값은 `10` |
| `&n` | `n`의 주소 | `int *` |
| `p` | `p`에 저장된 주소 | `int *`, 값은 `&n` |
| `*p` | `p`가 가리키는 곳의 값 | `int`, 값은 `10` |
| `&p` | 포인터 변수 `p` 자신의 주소 | `int **` |

`*`는 위치에 따라 뜻이 다르다.

```c
int *p;   // 선언에서 *: p는 int를 가리키는 포인터
int x = *p; // 식에서 *: p가 가리키는 값을 읽음(역참조)
```

포인터의 타입은 중요하다. `int *`에 `1`을 더하면 주소가 1바이트가 아니라 `sizeof(int)`바이트만큼 이동한다.

```c
int arr[3] = {10, 20, 30};
int *p = arr;

// p + 1은 &arr[1]
printf("%d\n", *(p + 1)); // 20
```

---

## Day 01: 주소를 함수에 전달하기

`day1.c`에는 명시적인 포인터 변수보다 `scanf`에서 주소를 전달하는 모습이 먼저 나온다.

```c
int a[10];
scanf("%d", &a[i]);
```

`scanf`가 입력값으로 `a[i]`를 바꾸려면 현재 값이 아니라 저장 위치를 알아야 한다. 따라서 `&a[i]`를 전달한다.

```text
a[i]   : 현재 저장된 int 값
&a[i]  : 그 int 값이 저장된 주소(int *)
```

`scanf` 형식과 인자의 타입도 맞아야 한다.

```c
int i;
double d;
char ch;

scanf("%d", &i);   // int *
scanf("%lf", &d);  // double *
scanf(" %c", &ch); // char *
```

### Day 01 확인 문제

1. `scanf("%d", n)`이 아니라 `scanf("%d", &n)`인 이유는?
2. `a[i]`와 `&a[i]`의 타입은 각각 무엇인가?

---

## Day 02: 기본 포인터, 배열, 문자열, 이중 포인터

### 2.1 포인터로 값 읽고 쓰기

```c
int a = 10, b = 15, total;
double avg;

int *pa = &a;
int *pb = &b;
int *pt = &total;
double *pg = &avg;

*pt = *pa + *pb;
*pg = *pt / 2.0;
```

위 코드는 다음 순서로 읽는다.

1. `pa`가 가리키는 값 `10`을 읽는다.
2. `pb`가 가리키는 값 `15`를 읽는다.
3. 합계 `25`를 `pt`가 가리키는 `total`에 저장한다.
4. 평균을 `pg`가 가리키는 `avg`에 저장한다.

### 2.2 배열 첨자와 포인터 연산

배열 이름은 대부분의 식에서 첫 원소를 가리키는 포인터로 변환된다.

```c
int ary[3];

*(ary + 0) = 10;
*(ary + 1) = 20;
*(ary + 2) = *(ary + 0) + *(ary + 1);
```

다음 두 표현은 같다.

```c
ary[i] == *(ary + i)
&ary[i] == ary + i
```

배열을 함수에 전달하면 함수는 배열 전체 크기를 알 수 없다.

```c
void print_ary(int *pa, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        printf("%d\n", pa[i]);
    }
}
```

따라서 포인터와 함께 원소 개수 `len`도 전달하는 습관이 중요하다.

### 2.3 문자열 포인터 배열과 `char **`

```c
const char *words[] = {"eagle", "tiger", "lion", "squirrel"};
```

`words`는 문자열 배열이 아니라 **문자 포인터를 원소로 갖는 배열**이다.

```text
words
├─ words[0] ──> "eagle"
├─ words[1] ──> "tiger"
├─ words[2] ──> "lion"
└─ words[3] ──> "squirrel"
```

함수에 전달될 때 `words`는 첫 번째 포인터 원소의 주소로 변환되므로 타입은 `const char **`가 된다.

```c
void print_str(const char **words, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
}
```

문자열 리터럴을 수정하면 정의되지 않은 동작이므로 `char *`보다 `const char *`로 받는 것이 안전하다.

### 2.4 포인터 증감 연산자의 우선순위

```c
char arr[] = "Hello";
char *p = arr;
char ch;

ch = *p++;    // ch = *p; 그 다음 p++
ch = (*p)++;  // ch = *p; 그 다음 가리키는 문자 증가
ch = ++*p;    // 가리키는 문자 증가 후 ch에 저장
```

| 식 | 포인터 `p` 이동 | 가리키는 값 변경 |
|---|---:|---:|
| `*p++` | O | X |
| `(*p)++` | X | O |
| `++*p` | X | O |
| `*++p` | O | X |

`[]`, `()`, 후위 `++`가 단항 `*`보다 우선순위가 높다. 헷갈리면 괄호로 의도를 명확히 하자.

### 2.5 이중 포인터로 포인터 자체 바꾸기

```c
void swap_ptr(const char **ppa, const char **ppb)
{
    const char *temp = *ppa;
    *ppa = *ppb;
    *ppb = temp;
}
```

호출:

```c
const char *pa = "success";
const char *pb = "failure";
swap_ptr(&pa, &pb);
```

`pa`의 값을 바꾸려면 `pa`의 주소인 `&pa`를 전달해야 한다. `pa`가 `const char *`이므로 `&pa`는 `const char **`다.

원본 `day2.c`의 다음 선언은 타입이 잘못되어 있다.

```c
int *pi = &a;
int *ppi = &pi;  // 잘못됨: &pi의 타입은 int **
```

올바른 선언:

```c
int *pi = &a;
int **ppi = &pi;
```

### 2.6 포인터를 반환하는 함수

```c
int *sum(int a, int b)
{
    static int result;
    result = a + b;
    return &result;
}
```

지역 자동 변수의 주소를 반환하면 함수 종료와 함께 수명이 끝나므로 안 된다.

```c
int *wrong(void)
{
    int n = 10;
    return &n; // 금지: 함수 종료 후 유효하지 않은 주소
}
```

`static` 지역 변수는 프로그램이 끝날 때까지 살아 있으므로 주소 반환은 가능하다. 다만 호출할 때마다 같은 저장 공간을 공유한다.

### 2.7 함수 포인터

```c
int sum(int a, int b);
int (*fp)(int, int) = sum;
int result = fp(10, 20);
```

`fp`는 `int` 두 개를 받고 `int`를 반환하는 함수를 가리킨다.

선언은 이름에서 바깥쪽으로 읽는다.

```text
int (*fp)(int, int)
     └─ fp는 포인터
        └─ int, int를 받는 함수를 가리킴
           └─ 그 함수는 int를 반환
```

### 2.8 동적 메모리

```c
int *p = malloc(sizeof *p);
if (p == NULL) {
    // 할당 실패 처리
}

*p = 10;
free(p);
p = NULL;
```

- C에서는 `malloc` 반환값을 명시적으로 형 변환하지 않아도 된다.
- `malloc` 결과는 사용 전에 `NULL`인지 확인한다.
- `free` 후 같은 주소를 다시 역참조하면 안 된다.
- 해제 후 `NULL`을 넣으면 실수로 재사용할 가능성을 줄일 수 있다.

### Day 02에서 주의할 코드

```c
volatile const int a = 100;
int *p = (int *)&a;
*p = 300;
```

캐스팅으로 `const`를 제거한 뒤 원래 `const`였던 객체를 수정하는 것은 정의되지 않은 동작이다. 형 변환은 객체의 실제 수정 가능 여부를 바꾸지 않는다.

---

## Day 03: 포인터 배열과 복잡한 선언

### 3.1 문자열 선택용 포인터 배열

```c
const char *message[2] = {"짝수", "홀수"};
printf("%s\n", message[n % 2]);
```

`message`는 포인터 2개를 저장하는 배열이다. 조건 결과를 인덱스로 사용해 문자열을 선택한다.

### 3.2 함수 포인터 배열 읽기

`day3.c`에는 다음 선언이 있다.

```c
double *(*a[5])(int *);
```

읽는 순서:

1. `a[5]`: `a`는 원소 5개짜리 배열이다.
2. `*a[5]`: 각 원소는 포인터다.
3. `(*a[5])(int *)`: 각 포인터는 `int *`를 매개변수로 받는 함수를 가리킨다.
4. `double *`: 그 함수는 `double *`를 반환한다.

즉, `a`는 **`int *`를 받고 `double *`를 반환하는 함수 포인터 5개짜리 배열**이다.

복잡한 타입은 `typedef`로 단순화할 수 있다.

```c
typedef double *(*Handler)(int *);
Handler a[5];
```

---

## Day 04: 라이브러리 함수가 포인터를 받는 이유

### 4.1 `scanf`

```c
int input;
scanf("%d", &input);
```

함수가 호출자의 변수를 변경해야 하므로 주소를 전달한다.

### 4.2 버퍼의 특정 위치 전달

```c
char result[5000];
int pos = 0;

pos += sprintf(result + pos, "%d x %d = %d\n", i, j, i * j);
```

`result + pos`는 `&result[pos]`와 같다. 따라서 이미 기록한 문자열 뒤쪽 주소를 `sprintf`에 넘긴다.

다만 실제 코드에서는 버퍼 범위를 넘지 않도록 `snprintf`와 남은 크기를 사용하는 편이 안전하다.

```c
size_t remain = sizeof result - (size_t)pos;
int written = snprintf(result + pos, remain, "...");
```

---

## Day 05: 배열과 포인터의 차이, `const`

### 5.1 문자열 리터럴과 문자 배열

```c
const char *a = "1234";
char b[] = "1234";
```

| 항목 | `a` | `b` |
|---|---|---|
| 정체 | 포인터 변수 | 문자 배열 |
| 문자열 저장 위치 | 문자열 리터럴 영역 | 배열 `b` 내부 |
| `a = 다른주소` | 가능 | 해당 없음 (`b = ...` 불가) |
| 문자 수정 | 금지 | 가능 |

```c
a = b;      // 가능: a가 b의 첫 문자를 가리킴
// *a = 'A'; // a가 리터럴을 가리킬 때는 금지

a = b;
*a = 'A';   // 가능: 현재 a는 수정 가능한 배열 b를 가리킴
```

### 5.2 배열 이름과 배열 주소

```c
char b[5] = "1234";
```

`b`와 `&b`는 출력되는 주소 숫자가 같을 수 있지만 타입과 포인터 연산 단위가 다르다.

| 식 | 타입 | `+ 1` 이동량 |
|---|---|---:|
| `b` | 대부분의 식에서 `char *` | `sizeof(char)` |
| `&b[0]` | `char *` | `sizeof(char)` |
| `&b` | `char (*)[5]` | `sizeof b` |

```c
b + 1;   // 다음 문자 주소
&b + 1;  // 배열 전체 바로 뒤 주소
```

### 5.3 포인터 뺄셈

```c
char *first = &b[0];
char *last = &b[4];
ptrdiff_t distance = last - first; // 4
```

같은 배열 안을 가리키는 두 포인터끼리 빼면 바이트 수가 아니라 **원소 거리**가 나온다. 결과 타입은 `ptrdiff_t`이고 출력 형식은 `%td`다.

### 5.4 `const` 포인터 매개변수

```c
int total_data(const int *arr, size_t len)
{
    int total = 0;
    for (size_t i = 0; i < len; i++) {
        total += arr[i];
    }
    return total;
}
```

`const int *arr`는 `arr`를 통해 원소를 수정하지 않겠다는 뜻이다. 읽기만 하는 함수에 사용하면 실수를 컴파일러가 잡아준다.

```c
const int *p;       // 가리키는 int를 p를 통해 수정할 수 없음
int *const p2 = ...; // p2가 다른 주소를 가리키게 할 수 없음
const int *const p3 = ...; // 둘 다 금지
```

### 5.5 `SIZE` 매크로의 한계

```c
#define SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

이 매크로는 실제 배열이 보이는 범위에서만 올바르다.

```c
int a[5];
SIZE(a); // 5
```

함수 매개변수의 `int arr[]`는 실제로 `int *arr`이므로 함수 안에서 `SIZE(arr)`를 사용하면 배열 길이가 나오지 않는다.

---

## Day 06: 포인터를 사용한 함수와 배열 처리

### 6.1 호출자의 두 값 교환하기

```c
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int x = 10;
int y = 20;
swap(&x, &y);
```

C는 인자를 값으로 복사해 전달한다. 주소값을 복사해서 전달하면 함수는 그 주소를 역참조해 호출자의 원본을 바꿀 수 있다.

### 6.2 배열을 받는 함수

`day06_lib.c`의 함수들은 공통적으로 시작 주소와 길이를 받는다.

```c
void print_ary(const int *ary, size_t len);
int sum_ary(const int *ary, size_t len);
void simple_sort(int *ary, size_t len);
```

- 읽기만 하면 `const int *`가 적합하다.
- 정렬처럼 원소를 바꾸면 `int *`가 필요하다.
- 빈 배열일 수 있다면 `len == 0`을 먼저 처리해야 `*ary`가 안전하다.

### 6.3 포인터 이동으로 입력받기

```c
void scanf_ary(int *ary, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        scanf("%d", ary++);
    }
}
```

매 반복마다 현재 원소의 주소가 `scanf`에 전달되고, `ary++`로 다음 원소로 이동한다. 함수가 받은 포인터는 복사본이므로 함수 밖의 배열 시작 주소는 바뀌지 않는다.

같은 동작을 첨자로 쓰면 다음과 같다.

```c
scanf("%d", &ary[i]);
```

### 6.4 문자열을 포인터로 순회하기

```c
char *to_upper(char *str)
{
    char *start = str;

    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str -= 'a' - 'A';
        }
        str++;
    }
    return start;
}
```

- `str`은 순회하면서 이동한다.
- 반환해야 할 시작 주소는 `start`에 따로 보관한다.
- `*str`은 현재 문자다.
- 문자열 끝은 널 문자 `\0`로 판단한다.

---

## Day 07: 문자열 함수와 다차원 배열 포인터

### 7.1 포인터로 문자열 복사하기

```c
char *mystrcpy(char *to, const char *from)
{
    char *result = to;

    while (*from != '\0') {
        *to++ = *from++;
    }
    *to = '\0';
    return result;
}
```

`*to++ = *from++`은 다음과 같다.

```c
*to = *from;
to++;
from++;
```

원본은 읽기만 하므로 `const char *`, 목적지는 수정하므로 `char *`다. 마지막에 반드시 `\0`을 복사하거나 직접 기록해야 한다.

### 7.2 문자열 길이와 비교

```c
while (*str != '\0') {
    count++;
    str++;
}
```

```c
while (*s1 == *s2) {
    if (*s1 == '\0') {
        return 0;
    }
    s1++;
    s2++;
}
return (unsigned char)*s1 - (unsigned char)*s2;
```

문자열 비교는 주소를 비교하는 것이 아니라, 각 주소가 가리키는 문자를 차례로 비교한다.

### 7.3 2차원 배열의 타입

```c
int a[3][8];
int (*p)[8] = a;
```

`a`는 대부분의 식에서 첫 행 `a[0]`의 주소로 변환된다. 한 행의 타입이 `int[8]`이므로 포인터 타입은 `int (*)[8]`이다.

```text
a              == &a[0]
a + 1          == &a[1]
*(a + 1)       == a[1]
*(a + 1) + 2   == &a[1][2]
*(*(a + 1) + 2) == a[1][2]
```

`a[i][j]`의 포인터 표현:

```c
a[i][j] == *(*(a + i) + j)
```

### 7.4 같은 주소처럼 보여도 타입은 다르다

`int a[3][8]`일 때:

| 식 | 타입 | 가리키는 대상 |
|---|---|---|
| `&a` | `int (*)[3][8]` | 전체 배열 |
| `a`, `&a[0]` | `int (*)[8]` | 첫 번째 행 |
| `a[0]`, `&a[0][0]` | `int *` | 첫 번째 정수 |

주소 출력값은 같을 수 있지만 `+ 1` 했을 때 이동하는 크기가 다르다.

```c
&a + 1;      // int 3 * 8개를 건너뜀
a + 1;       // int 8개짜리 한 행을 건너뜀
a[0] + 1;    // int 한 개를 건너뜀
```

### 7.5 3차원 배열 포인터

```c
int arr[2][3][4];

int (*p1)[3][4] = arr;   // arr[0] 같은 2차원 덩어리를 가리킴
int (*p2)[4] = arr[0];   // arr[0][0] 같은 한 행을 가리킴
int *p3 = arr[0][0];     // 첫 int를 가리킴
```

괄호가 매우 중요하다.

```c
int *p[5];    // 포인터 5개짜리 배열
int (*p)[5];  // int 5개짜리 배열을 가리키는 포인터
```

`[]`가 `*`보다 우선순위가 높기 때문에 배열 포인터에는 `(*p)` 괄호가 필요하다.

---

## Day 08: 배열 포인터, 포인터 배열, 함수 포인터 조합

### 8.1 선언 비교

| 선언 | 뜻 |
|---|---|
| `int *a[4]` | `int *` 4개짜리 배열 |
| `int (*a)[4]` | `int[4]`를 가리키는 포인터 |
| `int (**a)[4]` | `int[4]`를 가리키는 포인터의 주소 |
| `int *a[3][4]` | `int *`를 저장하는 3×4 배열 |
| `int (*a[3])[4]` | `int[4]`를 가리키는 포인터 3개짜리 배열 |

함수 포인터까지 섞인 선언:

```c
int *(*handlers[2])(int *);
```

`handlers`는 `int *`를 받아 `int *`를 반환하는 함수 포인터 2개짜리 배열이다.

### 8.2 2차원 배열을 함수에 넘기는 두 방법

행과 열이 연속된 2차원 배열을 1차원처럼 접근할 수 있다.

```c
void input_flat(int row, int col, int *array)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", array + i * col + j);
        }
    }
}
```

배열 포인터로 행의 구조를 보존할 수도 있다. VLA를 사용하므로 `col`이 먼저 선언되어야 한다.

```c
void input_2d(int row, int col, int (*array)[col])
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &array[i][j]);
        }
    }
}
```

### 8.3 2차원 문자 배열과 문자열 포인터 배열

아래 둘은 구조와 함수 매개변수 타입이 다르다.

```c
char animal[5][10];
const char *animal2[5];
```

| 선언 | 메모리 구조 | 함수 매개변수 예시 |
|---|---|---|
| `char animal[5][10]` | 길이 10인 문자 배열 5개가 연속 | `char (*p)[10]` |
| `const char *animal2[5]` | 문자 포인터 5개가 연속 | `const char **p` |

배열 전체를 가리키는 포인터도 만들 수 있다.

```c
const char *animal2[5] = {"cat", "dog", "lion", "tiger", "rabbit"};
const char *(*p)[5] = &animal2;

// *p는 animal2 배열이며, 인자로 넘길 때 첫 원소 주소로 변환
print_strings02(*p, 5);
```

---

## Day 09: 포인터 단계, 가변 길이 배열, `void *`

### 9.1 1·2·3차원 배열 합계 함수

```c
int sum_1d(int *a, int length);
int sum_2d(int (*a)[4], int rows, int cols);
int sum_3d(int (*a)[3][4], int depth, int rows, int cols);
```

접근식은 차원마다 `*`가 하나씩 늘어난다.

```c
*(a + i)                    // 1차원: a[i]
*(*(a + i) + j)             // 2차원: a[i][j]
*(*(*(a + i) + j) + k)      // 3차원: a[i][j][k]
```

실무에서는 같은 의미의 첨자 표현 `a[i][j][k]`가 더 읽기 쉽다. 포인터 표현은 배열의 동작 원리를 이해하는 데 활용하자.

### 9.2 포인터 단계 이해하기

```c
int value = 10;
int *p = &value;
int **pp = &p;
int ***ppp = &pp;
```

```text
ppp ──> pp ──> p ──> value
***ppp                  10
```

| 식 | 의미 | 타입 |
|---|---|---|
| `p` | `value`의 주소 | `int *` |
| `*p` | `value` | `int` |
| `pp` | `p`의 주소 | `int **` |
| `**pp` | `value` | `int` |
| `ppp` | `pp`의 주소 | `int ***` |
| `***ppp` | `value` | `int` |

`day09_lib.c`의 `exchange0`, `exchange1`, `exchange2`는 포인터 단계는 다르지만 모두 마지막의 `int` 값 두 개를 바꾼다.

```c
void exchange0(int *a, int *b);       // *a, *b 교환
void exchange1(int **a, int **b);     // **a, **b 교환
void exchange2(int ***a, int ***b);   // ***a, ***b 교환
```

포인터 자체를 교환하려면 최종 역참조가 아니라 한 단계 앞의 값을 교환해야 한다.

```c
void swap_int_pointers(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}
```

### 9.3 길이가 서로 다른 배열 묶기

```c
int ary1[] = {5, 1, 2, 3, 4};
int ary2[] = {4, 1, 2, 3};
int ary3[] = {6, 1, 2, 3, 4, 5, 6};
int *arrays[3] = {ary1, ary2, ary3};
```

각 배열의 첫 원소가 길이를 나타내고, `arrays`는 각 배열의 시작 주소를 저장한다.

```c
void print_var_array(int **arrays, int count)
{
    for (int i = 0; i < count; i++) {
        int *current = arrays[i];
        print_1d_array(current, current[0]);
    }
}
```

이런 구조를 흔히 재그드 배열(jagged array)처럼 사용한다. 각 행의 길이가 달라도 된다.

### 9.4 `void *`와 `qsort` 비교 함수

`void *`는 특정 자료형이 정해지지 않은 범용 주소다. 직접 역참조할 수 없으므로 실제 타입의 포인터로 변환한 뒤 사용한다.

```c
int compare_int(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;

    return (*ia > *ib) - (*ia < *ib);
}
```

```c
qsort(array, count, sizeof array[0], compare_int);
```

비교 함수의 반환 규칙:

- 음수: `a`가 `b`보다 앞
- `0`: 두 값의 정렬 순서가 같음
- 양수: `a`가 `b`보다 뒤

단순히 `return *ia - *ib;`라고 쓰면 큰 정수에서 오버플로가 발생할 수 있으므로 비교식이 더 안전하다.

`day09_lib.c`에는 `compint01`과 `compint`가 각각 두 번 정의되어 있다. 해당 파일을 단독 컴파일하려면 중복 정의 한 쌍을 제거해야 한다.

---

## 포인터 선언 빠르게 읽는 법

변수 이름부터 시작해 가까운 연산자를 우선순위에 따라 바깥쪽으로 읽는다.

```c
int *p;
```

`p`는 포인터이고, 가리키는 것은 `int`다.

```c
int *p[5];
```

`p`는 배열이고, 원소는 `int *`다.

```c
int (*p)[5];
```

괄호 때문에 `p`가 먼저 포인터가 되고, `int[5]`를 가리킨다.

```c
int (*fp)(double);
```

`fp`는 `double`을 받고 `int`를 반환하는 함수를 가리킨다.

```c
int *(*fp[3])(double *);
```

`fp`는 `double *`를 받고 `int *`를 반환하는 함수 포인터 3개짜리 배열이다.

---

## 자주 발생하는 실수

### 1. 초기화하지 않은 포인터 역참조

```c
int *p;
*p = 10; // 잘못됨: p가 어디를 가리키는지 모름
```

```c
int value;
int *p = &value;
*p = 10; // 정상
```

### 2. `NULL` 역참조

```c
if (p != NULL) {
    printf("%d\n", *p);
}
```

### 3. 지역 변수 주소 반환

함수가 끝나면 지역 자동 변수의 수명도 끝난다. 그 주소를 반환하지 않는다.

### 4. 문자열 리터럴 수정

```c
const char *s = "hello";
// s[0] = 'H'; // 금지
```

수정이 필요하면 배열을 사용한다.

```c
char s[] = "hello";
s[0] = 'H';
```

### 5. 배열 범위 초과

포인터 연산이 가능하다고 해서 배열 밖의 메모리를 읽거나 쓸 수 있는 것은 아니다. 배열의 마지막 다음 주소는 비교에는 쓸 수 있지만 역참조하면 안 된다.

```c
int a[3];
int *end = a + 3; // 주소 계산은 가능
// *end = 10;     // 금지
```

### 6. `%p`에 잘못된 타입 전달

주소를 출력할 때는 `(void *)`로 변환하고 `%p`를 쓴다.

```c
printf("%p\n", (void *)p);
```

### 7. `sizeof(pointer)`를 배열 크기로 착각

```c
void f(int *a)
{
    // sizeof(a)는 배열 크기가 아니라 포인터 크기
}
```

함수에는 길이를 별도 인자로 전달한다.

---

## 최종 암기표

| 목적 | 코드 |
|---|---|
| 변수 주소 얻기 | `&value` |
| 포인터 선언 | `int *p` |
| 가리키는 값 읽기/쓰기 | `*p` |
| 배열 i번째 원소 | `p[i]` 또는 `*(p + i)` |
| 포인터 자신의 주소 | `&p` |
| 이중 포인터 | `int **pp` |
| 포인터 배열 | `int *p[5]` |
| 배열 포인터 | `int (*p)[5]` |
| 함수 포인터 | `int (*fp)(int, int)` |
| 수정하지 않는 대상 | `const int *p` |
| 동적 할당 | `p = malloc(sizeof *p)` |
| 동적 메모리 해제 | `free(p)` |
| 범용 포인터 | `void *p` |

---

## 복습 문제

### 문제 1

다음 코드의 출력값을 예상하라.

```c
int a[] = {10, 20, 30};
int *p = a;

printf("%d\n", *p);
printf("%d\n", *(p + 2));
printf("%d\n", p[1]);
```

### 문제 2

다음 두 선언의 차이를 설명하라.

```c
int *a[5];
int (*b)[5];
```

### 문제 3

다음 코드에서 `p`, `*p`, `pp`, `**pp`의 타입과 값을 적어라.

```c
int n = 7;
int *p = &n;
int **pp = &p;
```

### 문제 4

`a[2][3]`을 포인터 연산만 사용해 표현하라.

### 문제 5

다음 함수가 위험한 이유를 설명하라.

```c
int *make_number(void)
{
    int n = 100;
    return &n;
}
```

### 문제 6

`int` 두 개를 받으며 `int`를 반환하는 함수 포인터 `fp`를 선언하라.

### 정답

1. `10`, `30`, `20`
2. `a`는 `int *` 5개짜리 배열, `b`는 `int` 5개짜리 배열을 가리키는 포인터다.
3. `p`: `int *`, 값은 `&n`; `*p`: `int`, 값은 `7`; `pp`: `int **`, 값은 `&p`; `**pp`: `int`, 값은 `7`.
4. `*(*(a + 2) + 3)`
5. 함수가 끝나면 지역 변수 `n`의 수명이 끝나 반환된 주소가 유효하지 않다.
6. `int (*fp)(int, int);`

---

## 추천 복습 순서

1. Day 01~02의 `&`, `*`, `p + i`, `p[i]`를 손으로 추적한다.
2. Day 05의 배열과 포인터 차이를 `sizeof`와 `+ 1`로 비교한다.
3. Day 06~07의 문자열 및 배열 함수를 직접 다시 작성한다.
4. Day 07~08의 `int (*)[N]` 선언을 반복해서 읽는다.
5. Day 09의 `int **`, `int ***`, `void *`를 그림으로 추적한다.

포인터 코드는 항상 **포인터에 저장된 주소**, **그 주소가 가리키는 대상의 타입**, **그 대상의 수명과 유효 범위** 세 가지를 함께 확인하면 이해하기 쉽다.
