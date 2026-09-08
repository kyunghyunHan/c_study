#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#if 1
typedef struct
{
    int age;
    double height;
    char *name;
    char phone[14];
} Profile;

typedef struct
{
    Profile pf;
    int num;
    double grade;

} Student;

int main(void)
{
    Student s1 = {{20, 175.5, "홍실이", "010-1234-5678"}, 1, 4.3};
    Student *p = &s1;
    printf("%d %.1f %s %s %d %.1f\n",
           s1.pf.age,
           s1.pf.height,
           s1.pf.name,
           s1.pf.phone,
           s1.num,
           s1.grade);
    printf("%d %.1f %s %s %d %.1f\n",
           (*p).pf.age,
           (*p).pf.height,
           (*p).pf.name,
           (*p).pf.phone,
           (*p).num,
           (*p).grade);
    return 0;
}
#endif
