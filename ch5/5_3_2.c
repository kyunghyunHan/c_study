#include <stdio.h>

int function_with_return();//함수선언
void p(int num);//함수선언
int main(void){

    int ret;
    ret= function_with_return();

    printf("%d",ret);
    p(ret);
    return 0;
}

int function_with_return(){
    printf("반환값이 있는 함수입니다.\n");
    return 10;
}
void p(int num){
    printf("num은 %d입니다.\n",num);
}