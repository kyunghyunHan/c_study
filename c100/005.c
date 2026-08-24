#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define CLOVER 0
#define HEART 1
#define SPADE 2
#define DIAMONDS 3

int main(void){
        printf("1");

    int check[CARDS]= {0};
    int caeds_order[CARDS]= {0};
    int rand_max = 52;//bood miss
    char suit;


    srand(time(0));
    printf("1");

    for(int i = 0; i<CARDS;i++){
        int x;
        do{
            x = (int)((double)rand()/RAND_MAX*rand_max);
        }while (check[x]!=0);
        check[x]= 1;
        caeds_order[i]= x;
    }

    printf("cads_order[]:\n");
    for(int i  = 0;i<CARDS;i++){
         printf("%-5d%c",caeds_order[i],(i+1)%13==0?'\n':' ');
    }
    printf("\n");

    printf("cads:\n");
    for(int i = 0;i<CARDS;i++){
        int denom = caeds_order[i]%13+1;//카드 숫자
        switch (caeds_order[i]/13)
        {
        case CLOVER:
            suit = 'C';
            break;
        
        case HEART:
            suit = 'H';
            break;
        
        case SPADE:
            suit = 'S';
            break;
        
        case DIAMONDS:
            suit = 'D';
            break;
        }
            printf("%c %2d %s",suit,denom,(i+1)%13==0?"\n":".");

    }
    return 0;
}