#include <stdio.h>

int main(void){
    for (int i =1;i<=3;i++){
        printf("첫번쨰 반복문 :%d\n",i);

        for (int j= 1;j<=5;j++){
            printf("____두번쨰 반복문 : %d\n",j);
        }
    }
    return 0;
}