#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#if 0
int main(void){
    int a = 10;
    int b = 12;
    //비트별 논리곱 연산자
    printf("a & b : %d\n",a & b);
    printf("a ^ b : %d\n",a ^ b);
    printf("a | b : %d\n",a | b);
    printf("~ a : %d\n",~a);
    printf("a << 1 : %d\n",a << 4);
    printf("a >> 2 : %d\n",a >> 2);


}
#endif
#if 0
int main(void){
    int i,j;

    for (i = 0; i<3;i++){
        for(j = 0; j<5;j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
#endif
#if 0
int main(void){
    int a = 10, b = 15, total;
    double avg;
    int *pa,*pb;
    int *pt  = &total;
    double *pg = &avg;

    pa = &a;
    pb = &b;

    *pt = *pa + *pb; 
    *pg  = *pt / 2.;

    printf ("두 정수의 값 : %d, %d\n",*pa , *pb);//10 15
    printf ("두 정수의 합 : %d\n",*pt);//25
    printf ("두 정수의 평균 : %.1lf\n",*pg);//0
    const int *pa = &a;
    return 0;
}
#endif

#if 0
int main(void){
    unsigned char a = -1;

    signed char b  = -1;

    printf("%d %d\n",a,b);

    if (a>b)printf("1. a>b");
    else if (a<b)printf("2. a<b");
    else printf("3. a==b");
    return 0;
}
#endif

#if 0
int main(void){

int ary[3];
int i ;
*(ary + 0) = 10;
*(ary+1) = 20;
*(ary+2) = *(ary+0) + *(ary+1);

for (int i  =0; i < 3;i++){
    printf("%d\n",ary[i]);
}
}
#endif

#if 1
int main(void){


}
#endif