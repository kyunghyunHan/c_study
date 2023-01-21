#include <stdio.h>

void function_with_params(int num1,int num2, int num3);//함수선언

int main(void){
    function_with_params(1,2,3);
    return 0;
}
void function_with_params(int num1,int num2 ,int num3){
    printf("전달값이 있는 함수이고,전달값은 %d,%d,%d 입니다\n",num1,num2,num3);
}