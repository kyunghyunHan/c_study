#include <stdio.h>
#include "day06_lib.h"
void swap(int *pa, int *pb){

    int temp; 
    temp = *pa;
    *pa = *pb;
    *pb = temp;

}
int main(void) {
    int a = 10;
    int b = 20;
    swap(&a,&b);
    // printf("%d\n", m);

    printf("%d %d",a,b);
    return 0;
}
