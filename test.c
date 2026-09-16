#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node
{
    char val;
    struct _node *next;
    struct _node *prev;
} node;

typedef enum COMMEND
{
    L = 'L',
    D = 'D',
    B = 'B',
    P = 'P'
} COMMEND;

/*
init 더미생성
append 값생성및 추가
comment  커맨드받아서 연산
destroy 메모리 해제
print_str  프린트
insert 추가
*/
void init_node(node **head)
{
    *head = (node *)calloc(1, sizeof(node));
    if (*head == NULL)
        exit(0);
    (*head)->val = 0;
    (*head)->next = *head;
    (*head)->prev = *head;
}

node *insert(node *pos, char ch)
{
    node *newnode = calloc(1, sizeof(node));
    if (newnode == NULL)
        exit(0);

    newnode->val = ch;
    newnode->prev = pos;
    newnode->next = pos->next;
    pos->next->prev = newnode;
    pos->next = newnode;

    return newnode;
}

void append(node *head, const char *arr, int i)
{
    insert(head->prev, arr[i]);
}
node *commend(node *curr, node *head, char cmd)
{
    if (cmd == L)
    {
        if (curr != head)
            curr = curr->prev;
    }
    else if (cmd == D)
    {
        if (curr->next != head)
            curr = curr->next;
    }
    else if (cmd == B)
    {
        if (curr != head)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            node *tmp = curr;
            curr = curr->prev;
            free(tmp);
        }
    }
    else if (cmd == P)
    {
        char ch;
        (void)scanf(" %c", &ch);
        curr = insert(curr, ch);
    }
    return curr;
}
void destroy(node *head)
{
    node *curr = head->next;

    while (curr != head)
    {
        node *next = curr->next;
        free(curr);
        curr = next;
    }
}
void print_str(node *head)
{
    node *curr = head->next;
    while (curr != head)
    {
        printf("%c", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

int main(void)
{
    char arr[100001] = {0};
    (void)scanf("%s", arr);
    int l = strlen(arr);
    node *head = NULL;
    init_node(&head);
    for (int i = 0; i < l; i++)
    {
        append(head, arr, i);
    }
    node *curr = head->prev;
    char cmd;
    int n;
    (void)scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        (void)scanf(" %c", &cmd);
        curr = commend(curr, head, cmd);
    }
    print_str(head);
    destroy(head);
    free(head);
    head = curr = NULL;

    return 0;
}
