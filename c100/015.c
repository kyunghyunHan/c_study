#include <stdio.h>

int main(){
    int x = 10, y  = 20;
    int z[3] = {1,2,3};
    int* p;

    p = &x;
    y = *p;
    *p = *p+y;
    p = &z[0];
    *p = 30;

    printf("[%p]: %d\n",p,*p);
    printf("[%p]: %d\n",p,*p+1);
    printf("[%p]: %d\n",p + 1,*(p+1));

    int a[3] = {10,20,30};
    int* q= a;
    printf("\n[%p]: %d\n",q,*q);
    q= q=1;
    printf("[%p]: %d\n",q,*q);

    int* ip;
    char*cp;
    double*dp;

    printf("sizeof(int*) = %d, sizeof(char*) = %d, sizeof(double*) = %d\n",sizeof(ip),sizeof(cp),sizeof(dp));
}