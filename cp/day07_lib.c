#include "day07_lib.h"

char *mystrcpy(char *to, const char *from)
{
    char *result = to;

    while (*from != '\0') {
        *to++ = *from++;
    }
    *to = '\0';
    
    return result;
}
// char *mystrcpy(char *to, const char *from)
// {
//     char *result = to;

//     for (; *from != '\0'; from++, to++) {
//         *to = *from;
//     }

//     *to = '\0';

//     return result;
// }
int mystrlen(const char*str){
   int i = 0;
    while (*str != '\0') {    
        i++;
        str++;  
   }
   return i;
}
int strcmp(const char *s1 , const char *s2){
    while (*s1 == *s2){
        if (*s1 == '\0'){
            return 0;
        }
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}
int intcmp(const int *a, const int *b){
    return *a - *b;
}
// char * strcpy(){
//     return 'a';
// }
