#include <stdio.h>

int main(void){
    int arr[3]={5,10,15};
    for (int i = 0; i<3;i++){
        printf("배열 arr[%d]의 값 : %d\b",i,arr[i]);
    }

    int *ptr= arr;
    for (int i =0;i<3;i++){
        printf("포인터 변수 ptr[%d]의 값 : %d\n",i,ptr[i]);
    }


    ptr[0]=100;
    ptr[1]=200;
    ptr[2]=300;
  //포인터 변수의 값을 바꾸면 포인터 변수가 가리키는 배열의 값도 바뀜
    return 0;
}