#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

#if 0

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

#if 0
int main(void)
{
    char *str = (char *)malloc(sizeof(char) * 21);
    strcpy(str, "aa");
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%c", *(str + i));
    }
    free(str);
    str = NULL;
    return 0;
}
#endif

#if 0
int main(void)
{
    char *arr[5] = {0};
    char temp[80] = {0};

    for (int i = 0; i < SIZE(arr); i++)
    {
        gets(temp);
        arr[i] = (char *)calloc(strlen(temp) + 1, sizeof(char));
        if (arr[i] == 0)
        {
            exit(0);
        }
        strcpy(arr[i], temp);
    }
    for (int i = 0; i < SIZE(arr); i++)
    {
        printf("%s\n", arr[i]);
    }
    for (int i = 0; i < SIZE(arr); i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    return 0;
}
#endif
#if 0
int main(void)
{
    char *str = malloc(400);
    char temp[80];

    if (str == NULL)
    {
        return 1;
    }

    char *p = str;

    for (int i = 0; i < 5; i++)
    {
        gets(temp);
        size_t len = strlen(temp);
        strcpy(p, temp);
        p += len;
        *p++ = '\n';
    }

    *p = '\0';

    printf("%s", str);

    free(str);

    return 0;
}
#endif

#if 0
int main(void)
{
    enum
    {
        row_count = 5,
        input_size = 80
    };

    char *arr[row_count] = {NULL};
    size_t offset[row_count] = {0};
    char *buffer = malloc(row_count * input_size);
    char *current = buffer;

    if (buffer == NULL)
    {
        fprintf(stderr, "메모리 할당에 실패했습니다.\n");
        return 1;
    }

    for (int i = 0; i < row_count; i++)
    {
        offset[i] = (size_t)(current - buffer);
        arr[i] = current;

        if (fgets(arr[i], input_size, stdin) == NULL)
        {
            fprintf(stderr, "문자열 입력에 실패했습니다.\n");
            free(buffer);
            return 1;
        }

        size_t length = strlen(arr[i]);
        if (length > 0 && arr[i][length - 1] == '\n')
        {
            arr[i][length - 1] = '\0';
        }
        current += strlen(arr[i]) + 1;
    }

    size_t used_size = (size_t)(current - buffer);
    char *p = realloc(buffer, used_size);

    if (p == NULL)
    {
        fprintf(stderr, "메모리 재할당에 실패했습니다.\n");
        free(buffer);
        return 1;
    }

    buffer = p;

    // realloc으로 주소가 바뀌었을 수 있으므로 포인터를 다시 설정한다.
    for (int i = 0; i < row_count; i++)
    {
        arr[i] = buffer + offset[i];
    }

    for (int i = 0; i < row_count; i++)
    {
        printf("%s\n", arr[i]);
    }

    free(buffer);
    buffer = NULL;

    return 0;
}

#endif

#if 0
int main(void)
{
    char *arr[5] = {0};
    // 각 문자열의 시작 주소가 arr[0]에서 몇 바이트 떨어져 있는지
    size_t size_arr[5] = {0};

    arr[0] = (char *)malloc(5 * 80);
    if (arr[0] == NULL)
    {
        exit(0);
    }
    // 5개를 한번에 받고
    for (int i = 0; i < 5; ++i)
    {
        if (i > 0)
        {
            arr[i] = arr[i - 1] + strlen(arr[i - 1]) + 1;
        }

        gets(arr[i]);

        // arr[i]가 arr[0]에서 몇 바이트 떨어져 있는지 저장
        size_arr[i] = arr[i] - arr[0];
    }

    // 실제 사용한 크기
    // 마지막 주소 에서 - 처음주소
    size_t used =
        (arr[4] + strlen(arr[4]) + 1) - arr[0];
    // 그만큼할당
    char *p = realloc(arr[0], used);
    // 피가 NULL 이면 종료
    if (p == NULL)
    {
        free(arr[0]);
        return 1;
    }
    // arr 이 P 의주소를 바라보게
    arr[0] = p;
    // 값 재할당 문자열의 주소를 다시 잡아줘야
    for (int i = 1; i < 5; ++i)
    {
        arr[i] = arr[0] + size_arr[i];
    }
    // 출력
    for (int i = 0; i < 5; ++i)
    {
        printf("%s\n", arr[i]);
    }

    free(arr[0]);
    arr[0] = NULL;

    return 0;
}
#endif
/*
char * s. = cat\0lion\n;
char **arr = 주소만저장

*/
#if 0
int main(void)
{
    char **arr = malloc(5 * sizeof(*arr));
    char *s = (char *)malloc(5 * 80);
    size_t offset[5] = {0};

    if (arr == NULL || s == NULL)
    {
        free(arr);
        free(s);
        return 1;
    }
    for (int i = 0; i < 5; ++i)
    {
        arr[i] = s;
        gets(s);
        s += strlen(s) + 1;
        offset[i] = arr[i] - arr[0];
    }

    size_t used = (size_t)(s - arr[0]);
    char *p = realloc(arr[0], used);
    if (p == NULL)
    {
        free(arr[0]);
        free(arr);
        return 1;
    }

    /* realloc으로 주소가 바뀔 수 있으므로 offset으로 주소를 다시 저장 */
    for (int i = 0; i < 5; ++i)
    {
        arr[i] = p + offset[i];
    }
    s = p + used;

    printf("this:%c\n", *(s - 2));
    free(arr[0]);
    arr[0] = NULL;
    free(arr);

    s = NULL;
    arr = NULL;

    return 0;
}

#endif

int add(int a, int b)
{
    return (a + b);
}
int add2(int a, int b)
{
    return (a + b);
}
int main(void)
{

    int (*fp[5])(int, int) = {add, add2};
    int (**fpp)(int, int) = (int (*)(int, int))malloc(5 * sizeof(*fpp));
    int (**fpp)(int, int) = fp;
    return 0;
}