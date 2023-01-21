#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){

    srand(time(NULL));
    int treatment= rand() %4;

    printf("\n\n === 자라나라 머리카락 게임 == \n\n");
    
    int cntShowBottle=0;
    int prevCntShowBottle=0;

    for (int i =1;i <=3 ;i++){




        int bottle[4]={0,0,0,0};
        do{
            cntShowBottle= rand() %2 +2;

        }while(cntShowBottle == prevCntShowBottle);
        prevCntShowBottle=cntShowBottle;
        printf(">%d번째 테스트 : ",i);
        int isIncluded= 0;
        for(int j = 0; j<cntShowBottle;j++){
            int randBottle= rand()%4;
            if (bottle[randBottle]==0){
                bottle[randBottle]=1;
                if(randBottle ==treatment){
                    isIncluded=1;
                }
            }else{
                j--;
            }
        }
        for(int k= 0;k<4;k++){
            if (bottle[k]==1){
                printf("%d ",k+1);
            }

        }
        printf("번 물약을 머리에 바릅니다.\n\n");

        if(isIncluded ==1){
            printf(">>성공 머리카락이 낫어요");

        }else{
            printf(">>실패 머리카락이 나지 않았어요\n");
        }
        printf("\n 계속하려면 enter을 누르셍ㅅ\n");
        //입력받은 값에 따라 다른 동작을 수행할수 있게한다
        getchar();
    }
printf("\n\n발모제는 몇번 일까요?");
int answer;
scanf_s("%d",&answer);
if(answer == tempnam +1){
    printf("\n>>정답입니다\n");
}else{
    printf("\n>>떙 틀렷어요 정답은 %d번입니다\n",treatment+1);
}


    return 0;
    }