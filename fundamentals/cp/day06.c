#include <ctype.h>
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

#if 0
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
#if 0
int main(void) {
    char arr[10];
    size_t len = sizeof(arr) / sizeof(arr[0]);

    for (size_t i = 0; i < len; i++) {
        if (scanf(" %c", &arr[i]) != 1) {
            return 1;
        }
    }

    for (size_t i = 0; i < len; i++) {

        if (arr[i] >= 'a' && arr[i] <= 'z') {
            arr[i] = arr[i] - ('a' - 'A');
        }
        else if (arr[i] >= 'A' && arr[i] <= 'Z') {
            arr[i] = arr[i] + ('a' - 'A');
        }

        printf("%c%s", arr[i], i + 1 == len ? "\n" : " ");
    }

    return 0;
}
#endif

#if 0
int main(void){
    //6명의 몸무게를 입력받아 몸무게의 평균을 출력하는 프로그램  반올림 첫쨰자리
    //23.2 39.6 66.4 50.0 45.6 48.0
    double arr[6];
    double sum = 0.;
    for (int i = 0; i<6;i++){
       scanf("%lf",&arr[i]);
       sum+=arr[i];
    }
    printf("%.1f",sum/6.);
    return 0;
}

#endif

#if 0
// int compare(const int *a,const int *b){
//     return *(const int *)b-*(const int *)a;
// }
// int main(void){
//     int input ;
   
//     scanf("%d",&input);
//     int arr[input];
//     for (int i = 0; i<input;i++){
//         scanf("%d",&arr[i]);
//     }
//     qsort(arr,input,sizeof(int),compare);
//     for (int i = 0 ;i<input;i++){
//        printf("%d\n",arr[i]);
//     }
//     return 0;
// }
#endif 
#if 1 
int main(){
    int arr[7] = {0};

    for (int i = 1; i <=10;i++){
        int n ;
        scanf("%d",&n);
        arr[n]+=1;
    }

    for (int j = 1; j<=6;j++){
        printf("%d : %d\n",j , arr[j]);
    }
    return 0;
}
#endif