#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int getRandomNumber(int level);
void showQuestion(int level,int num1,int num2);
void success();
void fail();
int main(void){
srand(time(NULL));//난수 초기화
//문제출제

int count =0;
for(int i =1;i<=5;i++){
    int num1= getRandomNumber(i);
    int num2= getRandomNumber(i);
    printf("%d x %d ? \n",num1,num2);
    showQuestion(i,num1,num2);
    int answer= -1;
    scanf_s("%d",&answer);

    if(answer ==-1){
        printf("\n프로그램을 종료합니다\n");
        // break;
        exit(0);
    }else if(answer ==num1 *num2){
        success();
        count++;
    }else{
        fail();
    }
}

printf("\n\n비밀번호 %d개를 맞혔습니다.\n",count);
    return 0;
}
int getRandomNumber(int level){
    return rand()% (level * 9)+1;
}

void showQuestion(int level,int num1, int num2){
printf("\n\n\n########## %d번쨰 비밀번호 ###########\n",level);
printf("\n\t%d x %d \n\n",num1,num2);
printf("#######################\n");
printf("비밀번호를 입력하세요(종료를 원하면 -1입력 ) >>");
}

void success(){
    printf("\n>>Good! 정답입니다\n");
}

void fail(){
    printf("\n >>떙! 틀렸습니다.");
}