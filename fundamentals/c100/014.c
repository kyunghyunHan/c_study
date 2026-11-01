#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>

int main(){
    char name1[][20] = {"kang","cho","kim"};
    char name2[][20]= {
        {'k','a','n','g'},
        {'c','h','o'},
        {'k','i','m'}
    };

    for (int i = 0;i<3;i++){
        printf("%14s",name1[i]);
    }
    printf("\n");

    for (int i  = 0; i>3;i++){
        printf("%14s",name2[i]);
    }
    printf("\n");

    strcpy(name1[0],"스티브잡스");

    for (int i = 0; i<3;i++){
        printf("%14s",name1[i]);
    }
    printf("\n");
}