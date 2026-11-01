#include <assert.h>
#include <stdio.h>
#include <string.h>
#if 0

int main(){
    char ch  ='X';
    char * a= "1234";
    char b[] = "1234";

    ch= *a; // ch = a의값 a = 1 b = 1
    printf("%c %c %c\n",ch, *a,b[0]);
    a = b; //   ch b의    a는b를 가리킴 
    printf("%c %c %c\n",ch, *a,b[0]);
    ch = *a; // 
     printf("%c %c %c\n",ch, *a,b[0]);
    *a = 'A';
    printf("%c %c %c\n",ch, *a,b[0]);
    // return 0;

    char *p = &b[4];
    printf("%ld\n",p - a);

    printf("%p %c\n",b,*b);
    printf("%p %ld\n",b + 1,p - b);
    //b = p; 배얄의 이름은 포인터 상수 이기떄문에 사용안댐 
    //& , sizof연산자와 함께 사용할떄 배열로 동작
    printf("%p %p %p\n",b, &b, &b+2);

    return 0;
}



#endif

#if 0 

int main(){
    int a = 1;
    int b =2;

    assert(a!=b);
    return 0;
}
#endif
#define  SIZE(arr) (sizeof(arr)/sizeof(arr[0]))


#if 0

#include <stdio.h>

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void inputData(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }
}

int totalData(const int *arr, size_t len)
{
    int total = 0;

    for (size_t i = 0; i < len; i++) {
        total += arr[i];
    }

    return total;
}

void printData(int total, size_t len)
{
    printf("%.2f\n", (double)total / len);
}

int main(void)
{
    int score[5] = {0};
    size_t len = SIZE(score);

    inputData(score, len);

    int total = totalData(score, len);

    printData(total, len);

    return 0;
}

#endif

#if 1
int main(void){
 char str1[80] = "applejam";
 char str2[80] ;
 strcpy(str2,str1);
 
 printf("%s %s\n",str1,str2); 
//  printf("%p\n", (void *)s);
 return 0;
}
#endif 