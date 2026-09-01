#include <stdio.h>
#include "day07_lib.h"
#if 0

int main(void) {
    int ans[11] = {0};
    int n;

    while (1) {
        scanf("%d", &n);

        if (n == 0) {
            break;
        }

        ans[n / 10]++;
    }

    for (int i = 10; i >= 0; i--) {
        if (ans[i] > 0) {
            printf("%d : %d person\n", i * 10, ans[i]);
        }
    }

    return 0;
}

#endif

#if 0
int main(void){
    char fruit[10]  = {0};
    char * dessert = "watermelon";
    memcpy(fruit,dessert,sizeof(dessert));
    printf("%s\n",fruit);
    return 0;
} 
#endif

#if 0



int main(void)
{   
    // char to[20];
    char from[20] = "banana";
    // printf("%s\n", mystrcpy(to, from));
    printf("%d",mystrlen(from));
    return 0;
}
#endif
#if 1
int main(){
    int a = 10;
    int b = 10;
    printf("%d\n", intcmp(&a, &b));    
    
    return 0;
}
#endif
