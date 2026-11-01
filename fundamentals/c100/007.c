#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool is_power_of_ten(int x){
    for(int i = 1;i<10;i++){
        if(x==pow(10,i))return true;

    }
    return false;
}

int main(){
    int x,y;
    int i_cnt = 0;
    int o_cnt = 0;
    int radius = 50;
    double pi;

    for  (int i = 1;i<=1000000000;i++){
        x = rand()%100;
        y = rand()%100;
        if ((x-radius)*(x-radius)+(y-radius)*(y-radius)<=radius*radius)
         i_cnt++;
        else
         o_cnt++;
        pi = (double)i_cnt/(i_cnt+o_cnt)*4;
        if(is_power_of_ten(i))
        printf("i = %d, pi = %f\n",i,pi);
    }
    printf("icnt = %d, ocnt = %d, pi = %f\n",i_cnt,o_cnt,pi);
}