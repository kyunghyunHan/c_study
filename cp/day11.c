#include <stdlib.h>
#include <stdio.h>
#if 0

else if(numLog[i]-numLog[i-1]==10){
             answer[index] = 'd';
        }
#endif

#if 0
int main(void)
{
    int *arr = malloc(sizeof(int) * 12);
    // arr = (*int)calooc(12,sizeof(*arr))
    for (int i = 0; i < 12; i++)
    {
        *(arr + i) = i;
    }

    for (int i = 0; i < 12; i++)
    {
        printf("%d\n", *(arr + i));
    }
    free(arr);
    arr = NULL;
    return 0;
}
#endif

#if 1

int main(void)
{
    int **arr = malloc(sizeof(*arr) * 3);
    int index = 0;

    for (int i = 0; i < 3; i++)
    {
        arr[i] = malloc(sizeof(*arr[i]) * 4);

        for (int j = 0; j < 4; j++)
        {
            *(*(arr + i) + j) = index++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++)
    {
        free(arr[i]);
    }

    free(arr);
    arr = NULL;

    return 0;
}

#endif