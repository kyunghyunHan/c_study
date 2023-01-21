#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    srand(time(NULL));
    int i = rand()%3;
    switch (i)
    {
    case 0:
    printf("가위\n");
    break;
       
    case 1:
    printf("가위\n");
      break;
       case 2:
    printf("가위\n");
      break;
       
    default:
       printf("몰라요\n");
    }
    return 0;
}