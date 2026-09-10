#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int data_set[], int left, int right)
{
    int first = left;
    int piviot = data_set[first];

    ++left;

    while (left <= right)
    {
        while (data_set[left] <= piviot && left < right)
        {
            ++left;
        }
        while (data_set[right] >= piviot && left <= right)
        {
            --right;
        }
        if (left < right)
        {
            swap(&data_set[left], &data_set[right]);
        }
        else
        {
            break;
        }
    }
    swap(&data_set[first], &data_set[right]);

    return right;
}

void quick_sort(int data_set[], int left, int right)
{
    if (left < right)
    {
        int index = partition(data_set, left, right);

        quick_sort(data_set, left, index - 1);
        quick_sort(data_set, index + 1, right);
    }
}

int main(void)
{
    int data_set[] = {6, 4, 2, 3, 1, 5};
    int length = sizeof data_set / sizeof data_set[0];
    int i = 0;

    quick_sort(data_set, 0, length - 1);
    for (int i = 0; i < length; i++)
    {
        printf("%d ", data_set[i]);
    }
    printf("\n");
    return 0;
}