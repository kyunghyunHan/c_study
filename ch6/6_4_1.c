#include <stdio.h>
//문자배열은 항상 +1
int main(void){
    char c= 'A';

    //배열의 크기를 정하지 않으면 null포함
    char str[6]="coding";
    printf("%d\n",c);
    printf("%s\n",str);
for (int i =0;i<sizeof(str[i]);i++){
    printf("%c\n",str[i]);
}
    return 0;
}