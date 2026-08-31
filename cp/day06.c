#include <stdio.h>
#include "day06_lib.h"
// void swap(int *pa, int *pb){

//     int temp; 
//     temp = *pa;
//     *pa = *pb;
//     *pb = temp;

// }
#if 0
int main(void) {
    int a = 20, b= 10;
    swap(&a,&b);
    printf("%d %d",a,b);
    return 0;
}
#endif 

#if 1
int main(void) {
    int ary[5];
    size_t len = sizeof(ary) / sizeof(ary[0]);
    scanf_ary(ary, len);
    print_ary(ary, len);
    printf("find max = %d\n", findmax_ary(ary, len));
    printf("find max index = %zu\n", findmax_idx(ary, len));
    printf("find min = %d\n", findmin_ary(ary, len));
    printf("find min index = %zu\n", findmin_idx(ary, len));
    printf("sum = %d\n", sum_ary(ary, len));
    printf("avg = %d\n", avg_ary(ary, len));
    find_min_max(ary,len);

    printf("variance = %f\n", var_ary(ary, len));
    simple_sort(ary,len);
    print_ary(ary,len);
    return 0;
}
#endif 
