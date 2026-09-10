#include <setjmp.h>
#include <stdio.h>
jmp_buf buf;
// 나중에 돌아올 실행 상태를 저장
#include <setjmp.h>
void banana()
{
    printf("in banana()\n");
    longjmp(buf, 1); // buf에 저장해둔 setjmp위치로 돌아가기
    /*닿지 않음 */

    printf("you'll never see this, because i long jmp d");
}

int main()
{ // 실행살태를  buf에 저장하고 0을반환
    // setjump 가 1로변경
    if (setjmp(buf))
        printf("back in main\n");
    else
    {
        printf("first thie throuht\n");
        banana();
    }
    return 0;
}
