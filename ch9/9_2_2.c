#include <stdio.h>

struct GameInfo
{
    char *name;
    int year;
    int price;
    char * company;
    /* data */
};

int main(void){
    struct GameInfo gameInfo1;

    gameInfo1.name= "나도게임";
    gameInfo1.year= 2022;
    gameInfo1.price= 50;
    gameInfo1.company= "나도회사";

    printf("발매연도 : %d\n",gameInfo1.year);
    
}
