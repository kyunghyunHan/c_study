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
    Student arr[3] = {{20, 175.5, "홍실이", "010-1234-5678"}, 1, 4.3};
    arr[1] = arr[2] = arr[0];
    for (int i = 0; i < 3; i++)
    {
        printf("%d %.1f %s %s %d %.1f\n",
               (*(arr + i)).pf.age,
               (*(arr + i)).pf.height,
               (*(arr + i)).pf.name,
               (*(arr + i)).pf.phone,
               (*(arr + i)).num,
               (*(arr + i)).grade);
    }
    Student *parr = arr;
    for (int i = 0; i < 3; i++)
    {
        printf("%d %.1f %s %s %d %.1f\n",
               (*(parr + i)).pf.age,
               (*(parr + i)).pf.height,
               (*(parr + i)).pf.name,
               (*(parr + i)).pf.phone,
               (*(parr + i)).num,
               (*(parr + i)).grade);
    }
    // printf("%d %.1f %s %s %d %.1f\n",
    //        s1.pf.age,
    //        s1.pf.height,
    //        s1.pf.name,
    //        s1.pf.phone,
    //        s1.num,
    //        s1.grade);
    // printf("%d %.1f %s %s %d %.1f\n",
    //        (*p).pf.age,
    //        (*p).pf.height,
    //        (*p).pf.name,
    //        (*p).pf.phone,
    //        (*p).num,
    //        (*p).grade);
    return 0;
}
#endif
