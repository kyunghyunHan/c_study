#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//전역변수 선언
int level;
int arraFish[6];
int *cursor;




//함수선언
void initData();
void printfFishes();
void decreaseWater(long elapsedTime);
int checkFishAlive();

int main(void){
    long startTime=0;//게임 시작시간
    int num;//물을 줄 어항번호
    long totalElapsedTime=0;//총 경과시간
    long prevElapsedTime= 0;//직전에 물을 준 시간
    initData();//게임초기화 함수 호출
    startTime= clock();//프로그램 실행이후 현재까지 흐른 시간 저장
    cursor= arraFish;


    //어항에 물주기
    while(1){
        printfFishes();//어항 물 높이 출력 함수로출
        printf("몇번 어항에 물을 줄까요?(1~6)");
        scanf_s("%d",&num);//어항벊 입력
        if (num <1||num>6){
            printf("\n입력값이 잘못됐습니다.\n");
            continue;
        }
        //총 경과시간 초 단위로 표시
        totalElapsedTime= (clock()-startTime)/CLOCKS_PER_SEC;
        printf("총 경과 시간 :%ld초\n",totalElapsedTime);
        //물을 준 시간 간격

        prevElapsedTime= totalElapsedTime-prevElapsedTime;
        printf("최근 경과시간 : %ld초\n",prevElapsedTime);
        decreaseWater(prevElapsedTime);//어항의 물을 증발시카는 함수호출
        //사용자가 입력한 번호의 어항에 물주기
        //조건1.어항의 물 높이가 0이하면 물을 주지 않음
        if(cursor[num-1]<=0){
            printf("%d번 어항의 물고기는 이미 죽었으므로 물을 주지 않습니다.\n",num);

        }
        //조건2.어항의 물 높이가 0을 초과하면 100을 넘지 않는지 확이하고 물을 줌
        else if(cursor[num-1]+1<=100){
            printf("%d번 어항에 물을 줍니다\n\n",num);
            cursor[num-1]+=1;
        }
        if (totalElapsedTime/20 >level-1){
            level++;
            printf("****축하합니다 %d레벨에서 %d레벨로 올랐습니다\n\n",level-1,level);

            if(level==5){
                printf("\n\n축하합니다. 최고 레벨을 달성했습니다 게임을 종료합니다\n\n");
                exit(0);
            }
        }
        //모든 물고기가 죽었는지 확인
        if (checkFishAlive()==0){
            printf("모든 물고기가 죽었습니다");
            exit(0);
        }else{
            printf("물고기가 아직 살아있어요\n\n");
        }
        prevElapsedTime=totalElapsedTime;
    }
    return 0;
}

void initData(){
    level=1;
    for(int i=0;i<6;i++){
        arraFish[i]=100;
    }
}

void printfFishes(){
    printf("%3d번 %3d번 %3d번 %3d번 %3d번 %3d\n",1,2,3,4,5,6);
    for (int i =0;i<6;i++){
        printf("  %3d ",arraFish[i]);
    }
    printf("\n\n");
}

void decreaseWater(long elapsedTime){

    for (int i =0;i<6;i++){
        arraFish[i]-=(level *3 *(int)elapsedTime);
        if(arraFish[i]<0){
            arraFish[i]=0;
        }
    }

}

int checkFishAlive(){
    for (int i=0;i<6;i++){
        if(arraFish[i]>0){
            return 1;
        }
    }
    return 0;
}