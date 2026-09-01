#include <stdio.h>
#include "day07_lib.h"
#if 0

int main(void) {
    int ans[11] = {0};
    int n;

    while (1) {
        scanf("%d", &n);

        if (n == 0) {
            break;
        }

        ans[n / 10]++;
    }

    for (int i = 10; i >= 0; i--) {
        if (ans[i] > 0) {
            printf("%d : %d person\n", i * 10, ans[i]);
        }
    }

    return 0;
}

#endif

#if 0
int main(void){
    char fruit[10]  = {0};
    char * dessert = "watermelon";
    memcpy(fruit,dessert,sizeof(dessert));
    printf("%s\n",fruit);
    return 0;
}
#endif

#if 0



int main(void)
{   
    // char to[20];
    char from[20] = "banana";
    // printf("%s\n", mystrcpy(to, from));
    printf("%d",mystrlen(from));
    return 0;
}
#endif
#if 0
int main(){
    int a = 10;
    int b = 10;
    printf("%d\n", intcmp(&a, &b));    
    
    return 0;
}
#endif
#if 0
#include <stdio.h>

int main(void)
{
    int arr[2][3] = {
        {10, 20, 30},
        {40, 50, 60}
    };

    (*(*(arr+1)+2))++;
    printf("%d",arr[1][2]);
    return 0;
}
#endif
#if 1
/* !! */
#define S (a)sizeof(a)
#include <stdio.h>

int main(void)
{
    /* =========================================================
       1. 2차원 배열
       ========================================================= */

    int a[3][8] = {0};

    // a는 표현식에서 대부분 &a[0]으로 변환됨.
    // &a[0]의 타입은 int (*)[8]
    //
    // 즉 ap는
    // "int 8개짜리 배열을 가리키는 포인터"
    int (*ap)[8] = a;


    /* ---------------------------------------------------------
       주소 비교
       --------------------------------------------------------- */

    printf("%p %p %p %p %p\n",
           (void *)&a,          // int (*)[3][8] : 전체 배열 a의 주소
           (void *)a,           // int (*)[8]    : a[0]의 주소
           (void *)&a[0],       // int (*)[8]    : a[0]의 주소
           (void *)a[0],        // int *         : a[0][0]의 주소
           (void *)&a[0][0]);   // int *         : a[0][0]의 주소


    printf("%p %p %p %p %p\n",
           (void *)(&a + 1),          // 전체 a[3][8] 뒤 주소
                                       // sizeof(a) 만큼 이동

           (void *)(a + 1),           // a[1]의 주소
                                       // int[8] 만큼 이동

           (void *)(&a[0] + 1),       // a[1]의 주소
                                       // int[8] 만큼 이동

           (void *)(a[0] + 1),        // a[0][1]의 주소
                                       // int 1개 만큼 이동

           (void *)(&a[0][0] + 1));   // a[0][1]의 주소
                                       // int 1개 만큼 이동


    /* ---------------------------------------------------------
       sizeof
       --------------------------------------------------------- */

    printf("%zu %zu %zu %zu %zu\n",
           sizeof(&a),       // 포인터 크기
           sizeof(a),        // 3 * 8 * sizeof(int)
           sizeof(&a[0]),    // 포인터 크기
           sizeof(a[0]),     // 8 * sizeof(int)
           sizeof(&a[0][0]));// 포인터 크기


    printf("%p %p\n",
           (void *)ap,       // &a[0]
           (void *)(ap + 1));// &a[1]


    printf("%zu %zu %zu\n",
           sizeof(ap),       // 포인터 크기
           sizeof(*ap),      // int[8] → 8 * sizeof(int)
           sizeof(**ap));    // int → sizeof(int)


    /* ---------------------------------------------------------
       a + 1을 따라가 보기
       ---------------------------------------------------------

       a
       ↓
       &a[0]

       a + 1
       ↓
       &a[1]

       *(a + 1)
       ↓
       a[1]
       ↓ 배열이 표현식에서 int *로 변환
       &a[1][0]

       *(a + 1) + 2
       ↓
       &a[1][2]

       *(*(a + 1) + 2)
       ↓
       a[1][2]
    */

    printf("%p %p %p %d\n",
           (void *)a,                   // &a[0]
           (void *)(a + 1),             // &a[1]
           (void *)(*(a + 1) + 2),      // &a[1][2]
           *(*(a + 1) + 2));            // a[1][2] 값


    /* ---------------------------------------------------------
       포인터 선언 연습
       --------------------------------------------------------- */

    int (*a_p1)[8] = a;
    // int 8개짜리 배열을 가리키는 포인터
    // a_p1 == &a[0]


    int (*a_p2)[8] = a + 1;
    // int 8개짜리 배열을 가리키는 포인터
    // a_p2 == &a[1]


    int *a_p3 = *(a + 1);
    // *(a + 1) == a[1]
    // a[1]은 표현식에서 &a[1][0]으로 변환
    //
    // 따라서:
    // a_p3 == &a[1][0]


    int *a_p4 = *(a + 1) + 2;
    // &a[1][0] + 2
    //
    // 따라서:
    // a_p4 == &a[1][2]


    int a_p5 = *(*(a + 1) + 2);
    // a[1][2]의 값


    printf("%d %p %p %p %d\n",
           **a_p1,             // a[0][0]
           (void *)a_p2,       // &a[1]
           (void *)a_p3,       // &a[1][0]
           (void *)a_p4,       // &a[1][2]
           a_p5);              // a[1][2]


    /* =========================================================
       2. 다른 2차원 배열 b
       ========================================================= */

    int b[3][8] = {0};


    int (*b_p0)[3][8] = &b;
    // 전체 배열 b를 가리키는 포인터
    //
    // b의 타입:
    // int [3][8]
    //
    // &b의 타입:
    // int (*)[3][8]


    int (*b_p1)[8] = b;
    // b → &b[0]
    //
    // int [8]을 가리키는 포인터
    //
    // b_p1 == &b[0]


    int (*b_p2)[8] = b + 1;
    // ★ 원래 코드의 int (*p2)[4] = b + 1; 은 틀림.
    //
    // b + 1의 타입은 int (*)[8]
    //
    // 따라서 [8]이어야 함.
    //
    // b_p2 == &b[1]


    int *b_p3 = b[1];
    // b[1]은 int[8]
    // 표현식에서 &b[1][0]으로 변환
    //
    // b_p3 == &b[1][0]


    int *b_p4 = *(b + 1) + 2;
    // *(b + 1)
    // = b[1]
    // = &b[1][0]
    //
    // + 2
    // = &b[1][2]


    int b_p5 = b[1][2];
    // b[1][2]의 실제 int 값


    /*
       여기서 변수 이름을 b로 또 만들 수 없음.

       원래 코드:

       int *b[5];

       위에서 이미

       int b[3][8];

       이 선언되어 있으므로 이름 충돌 발생.
    */

    int *pointer_array[5];
    // int * 5개를 저장하는 배열
    //
    // 타입:
    // int *[5]
    //
    // 구조:
    //
    // pointer_array[0] → int *
    // pointer_array[1] → int *
    // ...
    // pointer_array[4] → int *


    int **p = pointer_array;
    // 배열 pointer_array는 표현식에서
    // &pointer_array[0]으로 변환됨.
    //
    // pointer_array[0] 타입 = int *
    //
    // &pointer_array[0] 타입 = int **
    //
    // 따라서 int **p 가능.


    /* =========================================================
       3. 3차원 배열
       ========================================================= */

    int arr[2][3][4] = {0};


    /*
        arr 구조:

        arr
        ├─ arr[0]
        │   ├─ arr[0][0] → int[4]
        │   ├─ arr[0][1] → int[4]
        │   └─ arr[0][2] → int[4]
        │
        └─ arr[1]
            ├─ arr[1][0] → int[4]
            ├─ arr[1][1] → int[4]
            └─ arr[1][2] → int[4]
    */


    int (*ptr)[3][4] = arr;
    // arr은 표현식에서 &arr[0]으로 변환
    //
    // arr[0]의 타입:
    // int [3][4]
    //
    // 따라서:
    // ptr 타입 = int (*)[3][4]
    //
    // ptr == &arr[0]


    int (*pptr)[4] = arr[0];
    // arr[0]의 타입:
    // int [3][4]
    //
    // 표현식에서 &arr[0][0]으로 변환
    //
    // arr[0][0]의 타입:
    // int [4]
    //
    // 따라서:
    // pptr 타입 = int (*)[4]
    //
    // pptr == &arr[0][0]


    int *ppptr = arr[0][0];
    // arr[0][0]의 타입:
    // int [4]
    //
    // 표현식에서 &arr[0][0][0]으로 변환
    //
    // 따라서:
    // ppptr == &arr[0][0][0]


    int value = *arr[0][0];
    // arr[0][0]
    // → &arr[0][0][0]
    //
    // *arr[0][0]
    // → arr[0][0][0]
    //
    // 즉 실제 int 값


    return 0;
}
#endif
