#include <stdio.h>
#include <stdbool.h>
#define N 1000

int main(){
    bool a[N+1];
    int primes = 0;

    a[0] = a[1] = false;

    for(int i = 2;i<=N;i++){
        a[i] = true;
    }
    for(int i = 2;i<=N/2;i++){
        for(int j = 2; j<=N/i;j++){
            a[i*j]  =false;
        }
    }
    for (int i= 1; i<=N;i++){
        if (a[i]==true){
            primes++;
            printf("%4d%c",i,primes%15==0?'\n':' ');
        }
    }
    printf("\n2부터 1000사이 소수의 개수 : %d개",primes);
}