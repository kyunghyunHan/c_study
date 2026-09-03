#include "day09_lib.h"
#include <stdio.h>
#if 0
int main(void){
    int iary[5]= {1,2,3,4,5};

    printf("%p %p %p\n",&iary,iary,&iary[0]);
    printf("%p %p %p\n",&iary,iary,&iary[0]);
    printf("%zu %p %p\n",&iary,iary,&iary[0]);
    

    char cary[10]= "rabbit";

    printf("%p %p %p\n",&iary,iary,&iary[0]);
    printf("%p %p %p\n",&iary,iary,&iary[0]);
    printf("%zu %p %p\n",&iary,iary,&iary[0]);
    
    const char (*p)[7] = &"rabbit";
    
    printf("%c",*(*p+4));
    return 0;

}
#endif

#if 0
int main(void)
{
    int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int b[2][3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int sum = 0;

    sum = sum_3d(b, 2, 3, 4);
   
    printf("%d\n", sum);

    sum = sum_2d(a, 3, 4);
    printf("%d\n", sum);

    sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += sum_1d(a[i], 4);
    }
    printf("%d\n", sum);
    return 0;
}
#endif

#if 0
int main(void)
{
    int a = 10, b = 0;
    int *ap = &a, *bp = &b;
    int **app = &ap, ** bpp = &bp;
    exchange0(&a, &b);
    printf("%d %d %p %p %p\n", a, b, ap, bp, app);
    exchange1(&ap, &bp);
    printf("%d %d %p %p %p\n", a, b, ap, bp, app);
    exchange2(&app, &bpp);
    printf("%d %d %p %p %p\n", a, b, ap, bp, app);
    return 0;
}

#endif

#if 0

int main(void)
{
    int ary1[] = {5, 1, 2, 3, 4};
    int ary2[] = {4, 1, 2, 3};
    int ary3[] = {6, 1, 2, 3, 4, 5, 6};
    int *pary[3] = {ary1, ary2, ary3};

    print_var_array(pary, (int)SIZE(pary));
    return 0;
}
#endif


#if 1
int main(void){
    return 0;
}
#endif