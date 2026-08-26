#include <stdio.h>
/*피라미드 */
int main(){
    for (int i  = 1; i<=5;i++){
        for (int j  =1;j<=i;j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 1;i<=5;i++){
        for(int j = 1; j<=2*i-1;j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    for (int i =5;i >=1;i--){
        for(int j = 1;j<=i;j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 1;i<=5;i++){
        for(int j = 1;j<=5 -i ; j++){
            printf(" ");
        }
        for(int j = 1; j<=i;j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    for(int i = 1; i<=5;i++){
        for (int j = 1; j<=5 -i;j++){
            printf(" ");
        }
        for (int j = 1;j<=2*i-1;j++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 5;i>=1;i--){
        for (int j = 1; j<=5-i;j++){
            printf(" ");
        }
        for (int j = 1;j<=2*i-1;j++){
            printf("*");
        }
        printf("\n");
    }
     printf("\n");
}