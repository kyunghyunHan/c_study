#include<stdio.h>
void test(int i){
  if (i==10){
    return;
  }
  printf("홍길동\n");
  test(i+1);
}
int main(void){
    test(0);
    return 0;
}