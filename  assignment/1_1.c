#include <stdio.h>
/* 일부 컴파일러에서 void를 사용하면 경고메세지 출력될수가 있음  
main함수에서는 int형을 값을 반환하는것이 좋음
*/
//void main(){  
int main(){
    printf("hello~\n");
    return 0;  //main반환값이 int일경우 삽입 ,void->삽입 x
}

/*반환값:hello~*/