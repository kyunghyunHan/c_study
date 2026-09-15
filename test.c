#include <stdio.h>
#include <stdlib.h>

char text[100001] = {0};

typedef struct Node
{
    char data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef enum
{
    ADD = 0,
    SUB = 1,
} Type;

Node *create_node(char data)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
        return NULL;

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

/* 더미 head 생성 */
void init_head(Node **head)
{
    *head = create_node('\0');

    if (*head == NULL)
        return;

    (*head)->next = *head;
    (*head)->prev = *head;
}

/* current 뒤에 삽입 */
void insert(Node *current, Node *new_node)
{
    if (current == NULL || new_node == NULL)
        return;

    new_node->prev = current;
    new_node->next = current->next;

    current->next->prev = new_node;
    current->next = new_node;
}

/* 초기 문자열 연결 */
void init(Node *head, Node **current, char s[])
{
    *current = head;

    for (int i = 0; s[i] != '\0'; i++)
    {
        Node *new_node = create_node(s[i]);

        if (new_node == NULL)
            return;

        insert(*current, new_node);

        *current = new_node;
    }
}

/* 커서 이동 */
Node *move(Node *current, Type type)
{
    if (type == ADD)
        return current->prev;
    else
        return current->next;
}

/* current 삭제 */
void remove_node(Node *head, Node **current)
{
    if (*current == head)
        return;

    Node *remove = *current;

    remove->prev->next = remove->next;
    remove->next->prev = remove->prev;

    *current = remove->prev;

    free(remove);
}

/* 출력 */
void print_node(Node *head)
{
    Node *current = head->next;

    while (current != head)
    {
        putchar(current->data);
        current = current->next;
    }

    putchar('\n');
}

/* 전체 삭제 */
void destroy_list(Node **head)
{
    if (head == NULL || *head == NULL)
        return;

    Node *current = (*head)->next;

    while (current != *head)
    {
        Node *next = current->next;

        free(current);

        current = next;
    }

    free(*head);
    *head = NULL;
}

int main(void)
{
    Node *head = NULL;
    Node *current = NULL;

    char cmd, ch;
    int n;

    scanf("%100000s", text);

    /* 환형 리스트 head 생성 */
    init_head(&head);

    /* 초기 문자열 연결 */
    init(head, &current, text);

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &cmd);

        if (cmd == 'P')
        {
            scanf(" %c", &ch);

            Node *new_node = create_node(ch);

            if (new_node != NULL)
            {
                insert(current, new_node);
                current = new_node;
            }
        }

        else if (cmd == 'L')
        {
            /* head는 더미이므로 head보다 왼쪽으로 가지 않음 */
            if (current != head)
                current = move(current, ADD);
        }

        else if (cmd == 'D')
        {
            /* current->next가 head면 맨 오른쪽 */
            if (current->next != head)
                current = move(current, SUB);
        }

        else if (cmd == 'B')
        {
            remove_node(head, &current);
        }
    }

    print_node(head);

    destroy_list(&head);

    return 0;
}