//포인터로 다른변수의 주소와 값 알아내기
#include <stdio.h>

int main(void){
    int a= 1;
    int b= 2;
    int c= 3;

    //변수의 주소 출력
     printf("철수네 주소:%p, 암호 :%d\n",&a,a);
      printf("영희네 주소:%p, 암호 :%d\n",&b,b);
       printf("민수네 주소:%p, 암호 :%d\n",&c,c);

       //포인터 변수 선언과 값 출력
       int * 미션맨;
       미션맨 = &a;
       printf("미션맨이 방문한 곳의 주소 :%p, 암호 :%d\n",&미션맨,*미션맨);

       미션맨 = &b;
       printf("미션맨이 방문한 곳의 주소 :%p, 암호 :%d\n",&미션맨,*미션맨);

              미션맨 = &c;
       printf("미션맨이 방문한 곳의 주소 :%p, 암호 :%d\n",&미션맨,*미션맨);

}