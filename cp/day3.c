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

#if 0
int main(){
double * (*a[5])(int *);
printf("%d", sizeof(a));

return 0;
}
#endif

#if 0

int main(){
    int a = 10;
int b = 20;

    printf("%d", (a > b) ? a : b);
}

#endif

#if 0
int main(){
    int n = 64;
    if (n%2==0){
        printf("짝수\n");
    }else{
        printf("홀수\n");
    }

    (n%2==0)?printf("짝수\n"):printf("홀수\n");


    printf("%d\n",(n%2==0)?2:(n%3==0)?3:(n%5==0)?5:0);

    char * msg[2] = {"짝수","홀수"};
    printf("%s",msg[n%2]);

}



#endif

#if 1
// int main(){
//     int n = 65;
//      printf("%d\n",(n%2==0)?2:(n%3==0)?3:(n%5==0)?5:0);
//     return 0;
// }
#endif 

#if 1
int main(){

    int score;
    scanf("%d",&score);
    
    if (score>=70){
        printf("합격입니다.\n");
    }else if(score>=60 && score<70){
        printf("재시험보세요.\n");
    }else{
         printf("불합격입니다.\n");
    }
    
    
    return 0;
}
#endif