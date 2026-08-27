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

#if 0
int main(){
    int n = 65;
     printf("%d\n",(n%2==0)?2:(n%3==0)?3:(n%5==0)?5:0);
    return 0;
}
#endif

#if 0
int main(){
    int score;
    scanf("%d",&score);
    char *c[]= {"불합격입니다.","재시험입니다.","합격입니다."};
    printf("%s\n", c[(score >= 60) + (score >= 70)]);
    return 0;
}
#endif

#if 0
int main()
{
    int score;
    char ans;
    scanf("%d", &score);
    // if (score >= 90)ㅍ
    // {
    //     ans = 'A';
    // }
    // else if (score >= 89)
    // {
    //     ans = 'B';
    // }
    // else if (score >= 79)
    // {
    //     ans = 'C';
    // }
    // else if (score >= 69)
    // {
    //     ans = 'D';
    // }
    // else
    // {
    //     ans = 'F';
    // }
    
    switch (score / 10)
    {
    case (10):
    case (9):
        ans = 'A';
        break;
    case (8):
        ans = 'B';
        break;
    case (7):
        ans = 'C';
        break;
    case (6):
        ans = 'D';
        break;ㅈ
    default:
        ans = 'F';
        break;
    }
    printf("%c", ans);
}
#endif

#if 0
int main(){
    int a  = 65;
    char arr[] = "FFFFFFDCBAA";
    printf("%c", arr[a / 10]);
}
#endif

#if 0
int main(void) { //while

    int num;
    scanf("%d", &num);

    while (num > 10) {
        scanf("%d", &num);
    }

    printf("%d", num);
}
#endif

#if 0
int main(void) { // do-while

    int num;
    do {
        scanf("%d\n", &num);
    }while (num > 10);

    printf("%d\n", num);

    int num2;
    while (num2 > 10) {
        scanf("%d", &num2);
    }

    printf("%d\n", num2);
}
#endif

