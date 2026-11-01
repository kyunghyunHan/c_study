#include <stdio.h>

void swap(int x,int y){
    int tmp;
    tmp = x;
    x = y;
    y = tmp;
}
//call by referenct
void swap2(int* px,int *py){
    int tmp;
    tmp = *px;
    *px = *py;
    *py = tmp;
}

int main(){
    int x= 3;
    int y =4;

    swap(x,y);
    printf("swap()호출 후 : x = %d y = %d\n",x,y);

    swap2(&x,&y);
    printf("swap()2호출 후 : x = %d y = %d\n",x,y);
}
