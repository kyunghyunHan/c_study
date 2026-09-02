#include <stdio.h>
#include "day08_lib.h"

#if 0


#endif


#if 0
int main(void){
    int a1[4];
    int* a2[4];
    int a3[3][4];
    int a4[2][3][4];
    int (*a5[3])[4];//int 4개짜리 배열을 가리키는 포인터 배열
  


    int *p1 =a1; // &a1[0]
    int **p2 = a2; //&a2[0] 값
    int (*p3)[4] = a3; //&a[0][4]
    int (*p4)[3][4] = a4;//&a4[0][3][3]
    int (**p5)[4] = a5;  //
    
    int a[2][3][4] = {0};//3차원 배열
    int (*b[3])[4] = {0};//4개짜리 int를 가리키는  포인터 배열
    int*(*c[2])(int*)  = {0};//int * 를 반환하고 int *를 매개변수로 갖는 함수를 가리키는 포인터의 배열
    int* d[3][4] = {0};//포인터를 저장하는 2차원 배열
    int(*(*e[5])(void))[4] ={0};
    //e는 "매개변수가 없고, int 4개짜리 배열을 가리키는 포인터를 반환하는 함수"를 가리키는 함수 포인터 5개짜리 배열

    int (*p1)[3][4] = a; //2차원 배열을 가리키는 포인터
    int (**p2)[4] = b; //int 4개짜리 배열을 가리키는 포인터를 가리키는 포인터
    int *(**p3)(int *) = c; //int*를 매개별변수로 갖고 int*를 반환하는 포인터를 가리키는 포인터
    int* (*p4)[4] = d;//int*를 4개저장하는 
    int(*(**p5)(void))[4]  = e;
    

 
}  
#endif

#if 1
/* 


 */

void input_strings(char (*animal)[10], int n)
{
    for (int i = 0; i < n; i++) {
        (void)scanf("%s", animal[i]);
    }
}
void print_strings(char(*animal)[10],int n){
      for (int i = 0; i < n; i++) {
        printf("%s", animal[i]);
    }
    printf("\n");
}
int main(void){
    char animal[5][10] = {0};
   
    (void)freopen("animal.txt","r",stdin);
    input_strings(animal, (int)SIZE(animal));
    for (size_t i = 0; i < SIZE(animal); ++i){
        printf("%s\n", animal[i]);
    }
    return 0;
}
#endif
