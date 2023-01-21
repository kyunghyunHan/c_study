//전달값이 없는 함수
#include <stdio.h>

void function_without_params();

int main(void){
    function_without_params();//전달값이 없는 함수 호출
    return 0;
}

void function_without_params(){
    printf("반환값이 없는 함수입니다\n");
}