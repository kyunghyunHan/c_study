# c_study

---

# 1. 포인터 (Pointer)

- 변수의 **주소(Address)** 를 저장하는 변수
- `*` : 포인터 선언 / 역참조(Dereference)
- `&` : 변수의 주소를 가져옴

```c
int a = 10;

int *p = &a;

printf("%d\n", *p); // 10
```

---

# 2. 배열 (Array)

- 같은 자료형을 연속된 메모리에 저장
- 배열 이름은 첫 번째 요소의 주소

```c
int arr[3] = {1,2,3};

arr == &arr[0]
```

---

# 3. 문자열 (String)

- 문자열은 `char` 배열
- 마지막에는 반드시 `'\0'`(Null 문자)가 존재

```c
char str[] = "Hello";
```

메모리

```
H e l l o \0
```

---

# 4. 구조체 (Struct)

- 서로 다른 자료형을 하나로 묶는 사용자 정의 자료형

```c
struct Person
{
    char name[20];
    int age;
};
```

---

# 5. enum

- 관련된 상수들을 하나로 묶는 자료형
- 상태(State)를 표현할 때 많이 사용

```c
enum State
{
    STOP,
    RUN,
    ERROR
};
```

---

# 6. typedef

- 기존 자료형에 **별명(Alias)** 을 붙이는 키워드

```c
typedef unsigned int uint;

uint number = 10;
```

구조체에서 가장 많이 사용

```c
typedef struct
{
    char name[20];
    int age;
} Person;
```

---

# 7. 함수 포인터 (Function Pointer)

- 함수의 주소를 저장하는 포인터

```c
void hello()
{
    printf("Hello\n");
}

void (*fp)(void);

fp = hello;

fp();
```

주요 사용처

- Callback
- Linux Driver
- file_operations

---

# 8. 비트 연산 (Bit Operation)

```c
&
```

AND

```c
|
```

OR

```c
^
```

XOR

```c
~
```

NOT

```c
<<
```

Left Shift

```c
>>
```

Right Shift

주요 사용

- GPIO
- Register
- Embedded Programming

---

# 9. static

특징

- 프로그램 종료까지 메모리 유지
- 함수 내부에서도 값 유지
- 전역 변수의 접근 범위를 파일 내부로 제한 가능

```c
void func()
{
    static int count = 0;

    count++;

    printf("%d\n", count);
}
```

출력

```
1
2
3
```

---

# 10. const

- 값을 변경할 수 없는 상수

```c
const int num = 10;
```

---

# 11. volatile

의미

> 이 변수는 프로그램 외부(인터럽트, 하드웨어 등)에서 값이 변경될 수 있으므로 컴파일러가 최적화하지 말고 항상 메모리에서 다시 읽어라.

대표 사용

- Interrupt
- GPIO Register
- Hardware Register
- DMA

```c
volatile int button_pressed = 0;
```

---

# 메모리 구조

```
높은 주소

+----------------------+
|        Stack         |
+----------------------+
|                      |
|        Heap          |
+----------------------+
|         BSS          |
+----------------------+
|        Data          |
+----------------------+
|        Text          |
+----------------------+

낮은 주소
```

---

## 1. Stack

- 함수 호출
- 지역 변수(Local Variable)
- 매개변수(Parameter)
- 자동 생성 / 자동 삭제
- LIFO(Last In First Out)

```c
void func()
{
    int a = 10;
}
```

---

## 2. Heap

- 동적 메모리 영역
- malloc()
- calloc()
- realloc()
- free()
- 개발자가 직접 관리

```c
int *p = malloc(sizeof(int));
```

---

## 3. Data

- 초기화된 전역 변수
- 초기화된 static 변수

```c
int num = 10;
```

---

## 4. BSS

- 초기화하지 않은 전역 변수
- 초기화하지 않은 static 변수
- 자동으로 0 초기화

```c
int count;

static int value;
```

---

## 5. Text

- 프로그램 코드 저장
- 함수 코드 저장
- Read Only

```c
main()

printf()

hello()
```

---

# 동적 메모리

## malloc()

Heap에 원하는 크기의 메모리를 할당

```c
int *p = malloc(sizeof(int));
```

---

## calloc()

Heap 메모리를 생성하고 **0으로 초기화**

```c
int *p = calloc(10, sizeof(int));
```

---

## realloc()

이미 할당된 Heap 메모리의 크기를 변경

```c
p = realloc(p, 20 * sizeof(int));
```

---

## free()

Heap 메모리를 운영체제에 반납

```c
free(p);
```

---

# Stack vs Heap

| Stack | Heap |
|--------|------|
| 자동 관리 | 개발자가 직접 관리 |
| 함수 종료 시 자동 삭제 | free() 필요 |
| 빠름 | Stack보다 느림 |
| 지역 변수 저장 | 동적 메모리 저장 |

---

# 면접 핵심 키워드

- Pointer
- Struct
- typedef
- Function Pointer
- static
- const
- volatile
- malloc / calloc / realloc / free
- Stack vs Heap
- Data / BSS / Text