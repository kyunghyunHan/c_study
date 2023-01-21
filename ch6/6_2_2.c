#include <stdio.h>

int main(void){
    int subway_array[3];

    subway_array[0]= 30;
    subway_array[1]=40;
    subway_array[2]=50;

    for (int i=0 ;i<3;i++){
        printf("지하철 %d 호차에 %명이 타고 있습니다.",i+1,subway_array[i]);
    }
    return 0;
}