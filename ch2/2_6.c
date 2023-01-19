#include <stdio.h>

int main(void){
    char name[256];
    printf("이름이 뭐야?");
    scanf_s("%s",name,sizeof(name));


    //나이
    int age;
       printf("몇살이니?");
       scanf_s("%s",&age);


       //몸무게
       float weight;
       printf("몇kg나가니>");
       scanf_s("%f",&weight);

       double height;
       printf("키는몇이니?");
       scanf_s("%lf",&height);

       //범죄명
      char what[256];
      printf("니먼죄니?");
      scanf_s("%s",what,size_of(what));
    return 0;


}