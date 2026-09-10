#include <stdio.h>
void bubble_sort(int data_set[], int length)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - (i + 1); j++)
        {

            if (data_set[j] > data_set[j + 1])
            {
                temp = data_set[j + 1];
                data_set[j + 1] = data_set[j];
                data_set[j] = temp;
            }
        }
    }
}
int main()
{
    int data_set[] = {6, 4, 2, 3, 1, 5};
    int length = sizeof data_set / sizeof data_set[0];
    int i = 0;
    bubble_sort(data_set, length);
    for (i = 0; i < length; i++)
    {
        printf("%d ", data_set[i]);
    }
    printf("\n");
    return 0;
}