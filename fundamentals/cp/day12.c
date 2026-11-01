#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#if 0
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

#if 1
typedef struct Student
{
    int id;
    int scores[3];
    char name[20];
} Student;

#define size_ary(x) (sizeof(x) / sizeof((x)[0]))

void input_data(Student *stu, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        scanf("%d %d %d %d %s",
              &(stu + i)->id,
              &(stu + i)->scores[0],
              &(stu + i)->scores[1],
              &(stu + i)->scores[2],
              (stu + i)->name);
    }
}

void print_data(const Student *stu, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%d %d %d %d %s\n",
               (stu + i)->id,
               (stu + i)->scores[0],
               (stu + i)->scores[1],
               (stu + i)->scores[2],
               (stu + i)->name);
    }
}

int main(void)
{
    Student stu[5] = {0};

    /*
    1 90 86 78  TOM
    2 76 89 92 Jerry

    */
    (void)freopen("student.txt", "r", stdin);
    input_data(stu, size_ary(stu));
    print_data(stu, size_ary(stu));
    return 0;
}
#endif
