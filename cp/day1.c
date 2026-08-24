#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#if 0 
int main(void){
    printf("he");
    return 0;
}
#endif 
#if 0
int main(void){
    printf("Be happy!");
    system("ls");//시스템 명령어
    return 0;
}
#endif 
#if  0
int main(void){
    printf ("Be happy\n");
    printf("1234\n");
    printf("My\tfriend\n");
    printf("Cow\rW\a\n");
    return 0;
}
#endif
#if 0
int main(void){
    printf("%.1lf\n",3.45);
    return 0;
}
#endif
#if 0
int main(void){
    printf("%d\n",1010);
}
#endif
#if 0
int main(){
    short sh = 32767;
    int in  = 2147483674;
    return 0;
}
#endif
#if 1
int main(){
    int a[10];
    int min, max;
    int sum = 0;

    for (int i = 0; i<10;i++){
        printf("%d번쨰 숫자를 입력하세요:",i+1);
        scanf("%d",&a[i]);
    }
    for (int i = 0;i<10;i++){
        printf("%6d",a[i]);
    }
    printf("\n");
    min = max = a[0];

    for(int i = 1;i<10;i++){
        sum+=a[i];
        if(a[i]<min)
            min = a[i];
        else if (a[i]>max){
            max = a[i];
        }
    }
    printf("min = %d,max = %d,average = %.2f\n",min,max,sum/10.0);
}

#endif
//2진수 풀력
#if 0 
int main(void)
{
     int n = 100;

    for (int i = 31; i >= 0; i--) {
        printf("%u", (n >> i) & 1);
    }

    printf("\n");
    return 0;
}
#endif