#include <stdio.h>
#include <time.h> //헤더파일 추가
#include <stdlib.h>

//전역변수 선언ㄴ
int arrayAnumal[4][5];//카드 지도 배열(카드20장)
char * strAnimal[10];//동물 이름 배열
int checkAnimal[4][5];//카드 뒷면

//함수 선언
void initAmimalArray();
void initAnimalName();
void shuffleAnimal();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
void printAminals();
void printQuestion();
int foundAllAnimals();

int main(void){
    srand(time(NULL));//난수 초기화
    initAmimalArray();//카드지도 배열 초기화
    initAnimalName();//동물이름배열초기화
    shuffleAnimal();//카드 섞기
    int failCount=0;//총 실패 횟수

    while(1){


        int select1=0;//사용자가 선택한 첫번쨰 번호저장
        int select2=0;
        printAminals();
        printQuestion();
        printf("\n뒤집을 카드2장을 고르세요 (예:12 4)->");
        scanf_s("%d %d",&select1,&select2);//입력받기]
        if(select1 ==select2){
            continue;
        }

        //입력받은 카드 번호를 x,y좌표로 변환
        int firstSelect_x= conv_pos_x(select1);
        int firstSelect_y=conv_pos_y(select1);
        int secondSelect_x= conv_pos_x(select2);
        int secondSelect_y= conv_pos_y(select2);
        //두카드가 같은 동물이고 뒷면인 경우
        if((checkAnimal[firstSelect_x][firstSelect_y]==0 && checkAnimal[secondSelect_x][secondSelect_y])&&(arrayAnumal[firstSelect_x][firstSelect_y]==arrayAnumal[secondSelect_x][secondSelect_y])){
            printf("\n\n빙고! %s 발견\n\n",strAnimal[arrayAnumal[firstSelect_x][firstSelect_y]]);
        } else{
            //두카드가 다른 동물이거나 앞면인 경우
            printf("\n\n떙! 서로 다른 동물 카드이거나 이미 뒤집힌 카드입니다.\n");
            printf("%d : %s\n",select1,strAnimal[arrayAnumal[firstSelect_x][firstSelect_y]]);
            printf("%d : %s\n",select2,strAnimal[arrayAnumal[secondSelect_x][secondSelect_y]]);
            printf("\n");
            failCount++;//실패 횟수 1증가
        }
        if(foundAllAnimals()==1){
            printf("\n\n축하합니다 모든 동물을 찾았습니다\n");
            printf("총 %d번 실패했습니다\n",failCount);
            break;
        }
    }
    return 0;
}

void initAmimalArray(){
    //카드 지도 배열 초기화 함수
    for (int i = 0;i<4;i++){
        for (int j = 0;j<5;j++){
            arrayAnumal[i][j]= -1;
        }
    }
}

void initAnimalName(){
    strAnimal[0]= "원숭이";
        strAnimal[1]= "하마";
            strAnimal[2]= "강아지";
                strAnimal[3]= "고양이";
                    strAnimal[4]= "돼지";
                        strAnimal[5]= "코끼리 ";
                            strAnimal[6]= "기린";
                                strAnimal[7]= "낙타";
                                    strAnimal[8]= "타조";
                                        strAnimal[9]= "호랑이";
}


void shuffleAnimal(){
    for (int i =0;i<10;i++){
        for(int j =0;j<2;j++){
            int pos= getEmptyPosition();//카드 지도에서 빈 공간 찾기
            int x= conv_pos_x(pos);//카드 번호를 x좌표로 변환
            int y= conv_pos_y(pos);//카드 번호를 y좌표로 변환
            arrayAnumal[x][y]= i;
        }
    }
}
int getEmptyPosition(){
    //카드 지도에서 빈공간 찾기 함수
    while (1){
        int randPos= rand()%20;//
        int x= conv_pos_x(randPos);
        int y= conv_pos_y(randPos);
        if (arrayAnumal[x][y]==-1){
            return randPos;
        }
    }
    return 0;
}
int conv_pos_x(int x){
    return x/5;
}

int conv_pos_y(int y){
    return y %5;
}

void printAminals(){
    printf("\n=========동물 위치를 보여줍니다. =======\n\n");
    for(int i = 0;i<4;i++){
        for(int j =0;j<5;j++){
            printf("%8s",strAnimal[arrayAnumal[i][j]]);
        }
        printf("\n");
    }
    printf("\n============================\n");
}

void printQuestion(){
    printf("\n(문제)\n\n");
    int seq= 0;
    for (int i =0;i<4;i++){
        for(int j = 0;j<5;j++){
            if (checkAnimal[i][j]!=0){
                printf("%8s",strAnimal[arrayAnumal[i][j]]);
            }else{
                printf("%8d",seq);
            }
            seq++;
        }
        printf("\n");
    }
}

int foundAllAnimals(){
    for(int i =0;i<4;i++){
        for(int j=0;j<5;j++){
            if(checkAnimal[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
}