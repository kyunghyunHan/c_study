#include <stdio.h>

int main(void)
{
    float f = 46.5f;
    printf("%f\n", f);
    //둘쨰짜리 까만 출력
    printf("%.2f\n", f);
    double d= 4.428;
    //둘째자리 까지만 출력
    printf("%.2lf\n", d);
    return 0;
    /*double float실수인데 float에만 f를붙이는 이유= flaot이라는 것을 알리기 위해*/
}