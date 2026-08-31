#include "day06_lib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int m = 10;

void swap(int * ap , int *bp){
    int temp;
    temp = *ap;
    *ap = *bp;
    *bp = temp;
}

void scanf_ary(int *ary,size_t len){

  for (size_t i = 0; i < len; i++){
      scanf("%d",ary++);
  }
}

void print_ary(int *ary,size_t len){
    for(size_t i = 0; i<len;i++){
        printf("%d%s", ary[i], i + 1 == len ? "" : " ");
    }
    printf("\n");
}
int findmax_ary(int *ary,size_t len){
    int ans = *ary;
     for(size_t i = 0; i<len;i++){
        if (ans<ary[i]){
            ans = ary[i];
        }
    }
    return ans;
}
size_t findmax_idx(int *ary,size_t len){
    int ans = *ary;
    size_t idx = 0;
     for(size_t i = 1; i<len;i++){
        if (ans<ary[i]){
            ans = ary[i];
            idx = i;
        }
    }
    return idx;
}
int findmin_ary(int *ary,size_t len){
    int ans = *ary;
     for(size_t i = 0; i<len;i++){
        if (ans > ary[i]){
            ans = ary[i];
        }
    }
    return ans;
}
size_t findmin_idx(int *ary,size_t len){
    int ans = *ary;
    size_t idx = 0;
     for(size_t i = 1; i<len;i++){
        if (ans > ary[i]){
            ans = ary[i];
            idx = i;
        }
    }
    return idx;
}
int sum_ary(int *ary,size_t len){
    int sum = 0;
     for(size_t i = 0; i<len;i++){
       sum+=ary[i];
    }
    return sum;
}
int avg_ary(int *ary,size_t len){
    if (len == 0) {
        return 0;
    }

    int sum = 0;
     for(size_t i = 0; i<len;i++){
       sum+=ary[i];
    }
    return sum / (int)len;
}
// int compare(const int *a,const int *b){
//     return *(int *)a-*(int * )b;
// }
void find_min_max(int * ary , size_t n){
    int min,max;
    min = *ary;
    max= *ary;
    for (size_t i = 1; i<n;i++){
        if (max<ary[i]){
           max = ary[i];
        }
        if (min>ary[i]){
            min = ary[i];
        }
    }
    // qsort(ary,5,sizeof(int),compare);
    // min = ary[0];
    // max = ary[n-1];
    printf("max = %d , min = %d\n",max,min);
}

double d_avg_ary(int *ary, size_t len){
    if (len == 0) {
        return 0;
    }

    double sum = 0;
     for(size_t i = 0; i<len;i++){
       sum+=ary[i];
    }
    return sum / (double)len;
}
double var_ary(int *ary, size_t len){
    if (len == 0) {
        return 0;
    }

    double avg = d_avg_ary(ary, len);
    double sum = 0;
    for (size_t i = 0; i < len; i++) {
        sum += pow(ary[i] - avg, 2.0);
    }

    return sum / (double)len;
}

//표준편차 = 분산의 양의 제곱근 
double std_ary(int * ary , size_t len){

}
void simple_sort(int *ary, size_t len ){
    for (size_t i = 0; i<len-1;i++){
        for (size_t j = i+1;j< len;j++){
             if (ary[i] > ary[j]){
               int temp = ary[i];
                ary[i] = ary[j];
                ary[j] = temp;  
             }
        }
    }
}