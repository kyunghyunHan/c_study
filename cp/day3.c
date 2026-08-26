#include <stdio.h>
// #if 1
// int main(){
//     int a[5]= {3,2,1,6,5};
//     int i , j  , temp;
//     int min;

//     for (i = 0; i<4;i++){
//         min = i;
//         for (j = i+1;j<5;j++){
//             if(a[min]>a[j]){ //가장 작은 값이 a[j]보다 크면
//                 min = j; //j가 가장 작은 값의 첨자
//             }
//         }
//         if (min !=i){
//             temp = a[i];
//             a[i] = a[min];
//             a[min]= temp;
//         }
//     }
//     for (i = 0;i<5;i++){
//         printf("%5d",a[i]);
//     }
// }
// #endif

#if 1
int main(){
double * (*a[5])(int *);
printf("%d", sizeof(a));

return 0;
}
#endif