#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    srand(itme(NULL)); //난수초기화
    int num= rand() %100 +1;//난수 생성
    printf("정답 : %d\n",num);//정답출력
    int answer= 0;
    int chance=5;

    while (1){
        printf("남은 기회 %d번\n",chance--);
        printf("숫자를 맞혀보세요(1~100) : ");
        scanf_s("%d",&answer);
        if (answer >num){
            printf("DOWN \n\n");

        }else if(answer <num){
            printf("UP \n\n");
        }else if(answer==num){
            printf("정답입니다 \n\n");
            break;
        }else{
            printf("알수없는 오류가 발생했어요 \n\n");
        }
        if (chance==0){
            printf("모든 기회를 사용했어요 아쉽게도 실패\n");
            printf("정답 : %d\n",num);
            break;
        }
    }
    return 0;
}