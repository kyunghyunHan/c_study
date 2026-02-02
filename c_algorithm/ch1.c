#include <stdio.h>
#include <stdlib.h>

struct Point 
    {
        int x;
        int y;
    };

typedef struct tagPoiny{
    int x;
    int y;
} Point;

typedef struct tagPoint2{
    int x;
    int y;
}Point2;


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
   
    Point2 *ptr2 = (Point2*)malloc(sizeof(Point2));


    {   
        //stack
        int a =10;
        int b = 10;
        int c = 30;

    }
     //heap
    typedef struct tpoint
    {
        int x;
        int y;
    } Point;
    
    Point *ptr = (Point*)malloc(sizeof(Point));
    //=>메모리 누수

    free(ptr); //free로 정리
    return 0;
}  
