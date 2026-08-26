#include <stdio.h>

enum Size {Short  ,Tall , Crande , Venti};

char size_name [][7] ={"Short","Tall","Grande","Venti"};
int price_americano[] = {3800,4100,4600,5100};
int price_cappuccino[] = {4600,5900,6400,6900};

int main(){
    printf("커피 가격표(아메리카노)\n");
    for(int i = Short;i<=Venti;i++){
        printf("%10s : %5d\n",size_name[i],price_americano[i]);

    }
    printf("커피 가격포(카푸치노)\n");
    for (int i = Short;i<=Venti;i++){
        printf("%10s : %5d\n",size_name[i],price_cappuccino[i]);
    }
}
