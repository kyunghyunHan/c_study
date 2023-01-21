#include <stdio.h>

int main(){

  //배열을 선언하면 항상 초기화
    int arr[10]= {1,2,3,4,5,6,7,8,9,10};
    for (int i=0;i<10;i++){
        printf("%d\n",arr[i]);
    }
    return 0;
}