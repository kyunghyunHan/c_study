#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    int id;
    int score[3];
    char name[20];
} Student;
int input_data(Student **stu)
{
    int row, col;
    int count = 0;

    if (scanf("%d %d", &row, &col) != 2)
        return 0;

    *stu = (Student *)malloc(sizeof(Student) * row);
    if (*stu == NULL)
        return 0;

    int *ip;
    for (int i = 0; i < row; i++)
    {
        Student *sp = *stu + i;
        ip = sp->score;
        if (scanf("%d %d %d %d %19s", &(sp->id), ip, ip + 1, ip + 2, sp->name) != 5)
            break;
        count++;
    }

    return count;
}
void print_data(Student *stu, int n)
{
    Student *sp;
    int *ip;
    for (int i = 0; i < n; i++)
    {
        sp = stu + i;
        ip = sp->score;
        printf("%d %d %d %d %s\n", sp->id, ip[0], ip[1], ip[2], sp->name);
    }
}
int main(void)
{
    Student *stu = NULL;
    int count;

    (void)freopen("cp/student.txt", "r", stdin);
    count = input_data(&stu);
    print_data(stu, count);
    free(stu);
    return 0;
}
