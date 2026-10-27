int main(void)
{
    char *cp;
    const char *ccp = 'a';
    char c;

    c = 'c';
    *cp = c;/*가능 */
    cp = ccp;/*컴파일 경고발생 
    
    const 보호를 버리는 대입 → 컴파일 진단
    반대는가능
    const char *ccp는 주소 변경은 가능
    */
    *cp = c;/*세그멘테이션 볼트발생 */
    return 0;
}

/*왼쪽 피연산자는 const로 한정된 char에 대한 포인터
오른쪽 피연산자는 한정되지 않은 char에 대한 포인터
*/

