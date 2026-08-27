#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#if 0
#define SIZE(a) sizeof(a)/sizeof(a[0])
int main(void){
    int nums[3] ={2,3,5};
    int number = 15;

    for (int i = 0; i < SIZE(nums); ++i){
        if(number%nums[i]==0){
            printf("%d의 배수입니다.\n",nums[i]);
        }
    }
    return 0;
}
#endif
#if 0
int main(){
   
   for (int i = 1; i <10;i++){
    for (int j = 1; j<10;j++){
        printf("%d x %d = %d\n",i, j, i*j);
    }
   }
}
#endif 
#if 0
    int main(){
    char result[5000];
    int pos = 0;

    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            pos += sprintf(result + pos,
                           "%d x %d = %d\n",
                           i, j, i * j);
        }
    }

    printf("%s", result);

    return 0;
    }
#endif

#if 0
int main(){
    int ans = 0;

    while (1){
        int a ;
        scanf ("%d",&a);
        if (a==0){
            break;
        }
        if (!a%2==0){
            ans+=a;
        }
    }
    printf("%d",ans);
    return 0;
}
#endif

#if 1 
int main(){
    for (int i = 0;i<3;i++){
          int input;
          scanf("%d",&input);
          if(input ==1357){
            printf("로그인 성공!");
            return 0;
          }
    }
    printf("관리자에게 문의하세여!");
    return 0;
}
#endif