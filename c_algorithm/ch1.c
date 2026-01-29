#include <stdio.h>
struct Point 
    {
        int x;
        int y;
    };

typedef struct tagPoiny{
    int x;
    int y;
} Point;
int main(){
    // int* ptr;

    // int * ptr = 0xFF000000;

    // int a = 123;
    // int* ptr = &a;

    int arr[5] = {0,1,2,3,4};

    int* ptr  = arr;

    printf("%s\n",ptr == arr? "true" : "false");
   
    struct Point MyPoint = {30,40};

    printf("x : %d,y : %d\n",MyPoint.x,MyPoint.y);
  
    return 0;
}  
