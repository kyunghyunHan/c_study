#include <stdio.h>
//dowhile문은 일다 무조건 실행하고 한번은 실행하고 난뒤에 조건을 확인
int main(void){
    int i=1;
    do{
        printf("Hello World %d\n",i++);
    }while (i <=10);
    return 0;
}