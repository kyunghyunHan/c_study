#include <stdio.h>

int main(){
    // int* ptr;

    // int * ptr = 0xFF000000;

    // int a = 123;
    // int* ptr = &a;

    int arr[5] = {0,1,2,3,4};

    int* ptr  = arr;

    printf("%s\n",ptr == arr? "true" : "false");

    return 0;
}