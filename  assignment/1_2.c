/*
예제 :1-2 두수를 입력받아 곱의 결과를 출력
*/

#include <stdio.h>
//표준 입출력과 관련된 함수들을 정의하는 헤더 파일
//include ->다른언어의 import같은  불러오기
#pragma warning(disable:4996)
//#pragma warning : 경고 메시지를 제어하기 위해 사용 -> **일반적으로 권장되지 않음**
//disable : 특정 경고를 비활성화하도록 지시
//4996 :  경고 메시지 번호
//unsafe 함수 사용에 대한 경고를 비활성화


int a,b,c; //변수 선언
int product(int x,int y);//함수 프로토 타입 : 컴파일러에게 함수를 미리 알리는 역활
// void main(){
int main(){
//Enter a number between 1 and 100 출력
 printf("Enter a number between 1 and 100 : ");
  //첫번쨰 값 입력 
 scanf("%d",&a);

//Enter another number between 1 and 100출력
 printf("Enter another number between 1 and 100 : ");
 //두번쨰 값 입력
 scanf("%d",&b);
 
//변수에 product의 리턴값을 할당
 c= product(a,b);
 //차례대로 출력
 //%d : 정수형 변수를 출력할 때 사용하는 서식 지정자
 printf("%d * %d = %d \n",a,b,c); 
 /*
 출력
Enter a number between 1 and 100 : 3
Enter another number between 1 and 100 : 3
3 * 3 = 9 
 */
 return 0;
}

/* 두 int타입 수를 인자로 받아 곱하고 곱한값을 리턴하는 함수  */
int product(int x,int y){
    //return
    return (x*y);
}