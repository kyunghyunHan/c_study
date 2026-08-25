#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#if 0
int main(void){
    int a = 10;
    int b = 12;
    //비트별 논리곱 연산자
    printf("a & b : %d\n",a & b);
    printf("a ^ b : %d\n",a ^ b);
    printf("a | b : %d\n",a | b);
    printf("~ a : %d\n",~a);
    printf("a << 1 : %d\n",a << 4);
    printf("a >> 2 : %d\n",a >> 2);


}
#endif
#if 0
int main(void){
    int i,j;

    for (i = 0; i<3;i++){
        for(j = 0; j<5;j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
#endif
#if 0
int main(void){
    int a = 10, b = 15, total;
    double avg;
    int *pa,*pb;
    int *pt  = &total;
    double *pg = &avg;

    pa = &a;
    pb = &b;

    *pt = *pa + *pb; 
    *pg  = *pt / 2.;

    printf ("두 정수의 값 : %d, %d\n",*pa , *pb);//10 15
    printf ("두 정수의 합 : %d\n",*pt);//25
    printf ("두 정수의 평균 : %.1lf\n",*pg);//0
    const int *pa = &a;
    return 0;
}
#endif

#if 0
int main(void){
    unsigned char a = -1;

    signed char b  = -1;

    printf("%d %d\n",a,b);

    if (a>b)printf("1. a>b");
    else if (a<b)printf("2. a<b");
    else printf("3. a==b");
    return 0;
}
#endif

#if 0
int main(void){

int ary[3];
int i ;
*(ary + 0) = 10;
*(ary+1) = 20;
*(ary+2) = *(ary+0) + *(ary+1);

for (int i  =0; i < 3;i++){
    printf("%d\n",ary[i]);
}
}
#endif

#if 0
void print_ary(int *pa);
int main(void){
  int ary[5] = {10,20,30,40,50};
  print_ary(ary);
  return 0;
}

void print_ary(int *pa){
    int i ;
    for (i = 0;i<5;i++){
        printf("%d",pa[i]);
    }

}


#endif

#if 0
int main(void){
    int num,grade;
    printf("학번 입력 : ");
    scanf("%d",&num);
    getchar();
    printf("학점 입력 : ");
    grade = getchar();
    printf("학번 : %d, 학점 : %C",num,grade);
    return 0;
}
#endif 

#if 0
void print_str(char ** pps,int cnt);

int main(void){
    char *ptr_ary[] = {"eagle","tiger","lion","squirrel"};
    int count ;

    count = sizeof(ptr_ary)/sizeof(ptr_ary[0]);
    print_str(ptr_ary,count);


    return 0;
}
void print_str(char **pps,int cnt){
    int i ;
    for (i = 0;i<cnt;i++){
        printf("%s\n",pps[i]);
    }
}

#endif

#if 0

int main(void){
  int a , b, c;
 bool seen[100][100] = {false};
  scanf("%d",&a);
  for (int  i = 0; i<a;i++){
    scanf("%d %d",&b,&c);
    
    for (int i = b; i<b+10;i++){
        for (int j = c; j<c+10;j++){
             seen[i][j] = true;
        }
    }
    
  }
  int sum  =0;
    for (int i = 0; i<100;i++){
        for (int j = 0; j<100;j++){

           if (seen[i][j]==true){
              sum++;
           }
        }
    }
  printf("%d",sum);
}

#endif 
#if 0

int main(void){
  volatile const int a = 100;

  int *b = (int*)&a;
  *b = 300;

  printf("%d \n", *b);
}
#endif
#if 0
char * mystrcpy(char* to , char* from){
    char* save = to;
    for (;*to = *from;);
    // while (*to++ = *from);
    // for (; (*to++ = *from++); )
    for (;;) {
    *to = *from;

    if (*from == '\0') {
        break;
    }

    to++;
    from++;
}
    ;
    return save;
}
int main(void){
    char a[10] = {0};
    char* b = "Hello";
    mystrcpy(a,b);
    printf("%s\n",a);
    return 0;
}
#endif

#if 0
int *sum(int a , int b);
int main(void){
    int *resp;//반환값 저장
    resp = sum(10,20);
    printf("두 정수의 합 : %d\n",*resp);
    return 0;
}
int *sum(int a,int b)
{
  static int res;
  res = a+b;
  return &res;
}
#endif 

// postfix ++/-- 이해
#if 0
int main(void) {
    char arr[10] = "Hello";
    char* p = arr;  // arr은 상수, p는 변수
    char ch = 0;

    printf("p = %p\n", p);
    ch = *p++;    //  ch = *p; p = p + 1;
    printf("p = %p, ch = %c, arr = %s\n", p, ch, arr);
    ch = (*p)++;  //  ch = *p; *p = *p + 1;
    printf("p = %p, ch = %c, arr = %s\n", p, ch, arr);
    ch = ++*p;  // *p = *p + 1; ch = *p;
    printf("p = %p, ch = %c, arr = %s\n", p, ch, arr);
    ch = ++(*p);  // *p = *p + 1; ch = *p;
    printf("p = %p, ch = %c, arr = %s\n", p, ch, arr);

    return 0;
}
#endif

#if 0
int main(){
    int a =10;
    int *pi ;
    int *ppi ;

    pi  = &a;
    ppi = &pi;

    printf("");
}
#endif

#if 0
int main(){
   int a = 5,b  =0;
   int pre=0,post=0;
   pre  = (++a) *3;
   post = (b++) *3;
   printf("%d %d\n",a,b);
   printf("$%d %d\n",pre,post);
   return 0;
}
#endif

#if 0

void swap_ptr(char **ppa, char **ptr);

int main(void){
    char *pa = "success";
    char *pb = "failure";

    printf("pa -> %s, pb -> %s\n",pa,pb);
    swap_ptr(&pa,&pb);
    printf("pa -> %s, pn ->%s\n",pa,pb);
    return 0;
}
void swap_ptr(char **ppa, char **ppb){
    char *pt;
    pt  = *ppa;
    *ppa = *ppb;
    *ppb = pt;
}
#endif

#if 0
#include <stdio.h>

int main(void) {
    int n, d, k, c;
    scanf("%d %d %d %d", &n, &d, &k, &c);

    static int arr[3000000];
    static int check[3001];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int kind = 0;

    for (int i = 0; i < k; i++) {
        int sushi = arr[i];

        if (check[sushi] == 0) {
            kind++;
        }

        check[sushi]++;
    }

    int max = kind;

    if (check[c] == 0) {
        max++;
    }

    for (int i = 1; i < n; i++) {

        int remove = arr[i - 1];

        check[remove]--;

        if (check[remove] == 0) {
            kind--;
        }

        int add = arr[(i + k - 1) % n];

        if (check[add] == 0) {
            kind++;
        }

        check[add]++;

        int current = kind;

        if (check[c] == 0) {
            current++;
        }

        if (current > max) {
            max = current;
        }
    }

    printf("%d\n", max);

    return 0;
}
#endif
#if 0
 void print_str(char **pps,int cnt);
 int main(void){
    char *ptr_ary[] ={"engle","tiger","lion","squirrel"};
    int count;

    count = sizeof(ptr_ary)/sizeof(ptr_ary[0]);
    print_str(ptr_ary,count);
    
    return 0;
 }
 void print_str(char **pps,int cnt){
    int i;
    for(int i= 0;i<cnt;i++){
        printf("%s\n",pps[i]);
    }
 }

#endif 
int set_bit(int num,int bit_position);
int clear_bit(int num,int bit_position);
int toggle_bit(int num,int bit_position);
int is_bit_set(int num,int bit_position);
#if 0
int main(void){
    int num = 0b1010;
    num = set_bit(num,2);//2번 비트 1로
    printf("%X\n",num);
    num = clear_bit(num,1);//1번비트 1로
    printf("%X\n",num);
    num = toggle_bit(num,3);//3번 비트 1로
    printf("%X\n",num);
    num = is_bit_set(num,3);

    return 0;
}
int set_bit(int num,int bit_position){
    /*
    1010
    0100
    1110
     */
    return num | (1 << bit_position);
}
int clear_bit(int num,int bit_position){
    /*
    1110
    0010 -> 1101
    1100 => 12 
     */
    return num & ~(1 << bit_position);
}
int toggle_bit(int num,int bit_position){
    /*
    1100
    1000
    0100
     */
    return num ^ (1 << bit_position);

}
int is_bit_set(int num,int bit_position){
    /*
    1100
    0100
    */
    return (num & (1 << bit_position)) != 0;

}

#endif

#if 0
int sum(int,int);
int main(void){
    int (*fp)(int,int);//함수포인트 선언
    int res;//반환값

    fp = sum;
    res = fp(10,20);
    printf("result : %d\n",res);
    return 0;
}
int sum(int a,int b){
    return (a+b);
}
#endif

#if 0

int main(void){
    int *pi;
    double *pd;

    pi = (int * )malloc(sizeof(int));
    if (pi ==NULL){
        printf("# 메모리 부족\n");
        exit(1);
    }
    pd = (double *)malloc(sizeof(double));
    *pi = 10;
    *pd = 3.4;

    free(pi);
    free(pd);

    return 0;
}
#endif 

// int main(){
//     char x = 127;
//     char y = x+1;
//     printf("%d, %d %d",x,x+1,y);

//     x = -128;
//     y = x-1;
//     printf("%d, %d %d",x,x-1,y);
//     return 0;
// }


#if 1
#include <stdio.h>

int main(void) {
    int cnt, a, b;
    int arr[102][102] = {0};

    scanf("%d", &cnt);

    for (int k = 0; k < cnt; k++) {
        scanf("%d %d", &a, &b);

        for (int i = a + 1; i < a + 11; i++) {
            for (int j = b + 1; j < b + 11; j++) {
                arr[i][j] = 1;
            }
        }
    }

    int ans = 0;

    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {

            if (arr[i][j] == 1) {
                if (arr[i - 1][j] == 0)
                    ans++;

                if (arr[i + 1][j] == 0)
                    ans++;

                if (arr[i][j - 1] == 0)
                    ans++;

                if (arr[i][j + 1] == 0)
                    ans++;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}

#endif 

/* */