#include <stdio.h>
#include <stdbool.h>

int main(){
    bool sign  = false;
    double pi  = 0;

    for (int i  =1; i<=1000000000;i+=2){
        if(sign ==false){
            pi+1./i;
            sign = true;
        }else {
            pi -=1./i;
            sign = false;
        }
        if(i<20||i>99999990)
        printf("i = %10d, pi = %.18f\n,",i,4*pi);

    }

}