#include <stdio.h>

int main(){
    int index;
    int primes = 0;

    for (int i = 2; i<1000;i++){
        for (index = 2; index<i;index++){
            if (i%index==0){
                break;
            }
        }
         if (index  == i ){
        primes++;
        printf("%4d%c",i,primes % 15==0?'\n':' ');
        
    }
    }
    printf("\n2부터 1000사이 소수의 개수: %d",primes);
}