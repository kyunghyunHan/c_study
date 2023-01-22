#include <stdio.h>

int main(void){
    int 철수 =1;
    int 영희 =2;
    int 민호 = 3;
    //
int *미션맨;
미션맨 = &철수;
    //포인터 변수를 추가해 값 바꾸기
    int *스파이 = 미션맨;
    *스파이 = *스파이 = 미션맨;
    *스파이= *스파이 -1;
    미션맨= &영희;
    
    return 0;
}