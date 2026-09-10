#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(){
    int i, a,b,c;
    int day,month,year;
    char s[100];

    int x  =  scanf("%d %c %d",&a,&i,&b);
    printf("scanf의 리턴 값 = %d\n",x);
    printf("(1) %d %c %d\n",a,i,b);
    c = getchar();//\n을 읽는다
    scanf("%[0-9]",s);
    printf("(2) %s\n",s);
    
    scanf("%[^\n]",s);//\n앞까지 읽는다 ^up-to의 의미
    printf("(3)%s\n",s);
    return 0;
}