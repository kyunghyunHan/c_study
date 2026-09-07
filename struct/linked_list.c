#include <stdlib.h>
#include <stdio.h>
typedef int ElementType;

typedef struct tagNode
{
    ElementType data;
    struct tagNode *next_node;
} Node;

// node 생성
Node *sll_create_node(ElementType new_data)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = new_data;
    new_node->next_node = NULL;

    return new_node;
}

void sll_destory_node(Node *node)
{
    free(node);
}

void sll_append_node(Node **head, Node *new_node)
{
    // 헤드 노드가 null 노드 아리면 새로운 노드가 head가된다
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        // tali을 찾아 new node를 연결한다
        Node *tail = *head;
        while (tail->next_node != NULL)
        {
            tail = tail->next_node;
        }
        tail->next_node = new_node;
    }
}
Node *sll_get_node_at(Node *head, int location)
{
    Node *currrent = head;
    while (currrent != NULL && (--location) >= 0)
    {
        currrent = currrent->next_node;
    }
    return currrent;
}
void sll_remove_node(Node **head, Node *remove)
{
    if ((*head) == remove)
    {
        *head = remove->next_node;
    }
    else
    {
        Node *current = *head;
        while (current != NULL && current->next_node != remove)
        {
            current = current->next_node;
        }
        if (current != NULL)
        {
            current->next_node = remove->next_node;
        }
    }
}

void sll_insert_after(Node *current, Node *new_node)
{
    (*new_node).next_node = current->next_node;
    current->next_node = new_node;
}
void sll_insert_new_head(Node **head, Node *new_head)
{
    if ((*head) == NULL)
    {
        (*head) = new_head;
    }
    else
    {
        (*new_head).next_node = (*head);
        (*head) = new_head;
    }
}
int sll_get_node_count(Node *head)
{
    int cnt = 0;
    Node *current = head;

    while (current != NULL)
    {
        current = (*current).next_node;
        cnt++;
    }
    return cnt;
}

int main(void)
{

    int i = 0;
    int cnt = 0;
    Node *list = NULL;
    Node *current = NULL;
    Node *new_node = NULL;

    for (i = 0; i < 5; i++)
    {
        new_node = sll_create_node(i);
        sll_append_node(&list, new_node);
    }

    new_node = sll_create_node(-1);
    sll_insert_new_head(&list, new_node);

    new_node = sll_create_node(-2);
    sll_insert_new_head(&list, new_node);

    // 리스트 출력
    cnt = sll_get_node_count(list);
    for (i = 0; i < cnt; i++)
    {
        current = sll_get_node_at(list, i);
        printf("List[%d] : %d\n", i, current->data);
    }

    // 리스트의 세번째 노드뒤에 새 노드 삽입
    printf("\nInserting 3000 After [2]...\n\n");

    current = sll_get_node_at(list, 2);
    new_node = sll_create_node(3000);

    sll_insert_after(current, new_node);

    cnt = sll_get_node_count(list);
    for (i = 0; i < cnt; i++)
    {
        current = sll_get_node_at(list, i);
        printf("List[%d] : %d\n", i, (*current).data);
    }

    // 모든 노드를 메모리에서 제거

    printf("\nDestorying List..\n");
    for (int i = 0; i < cnt; i++)
    {
        current = sll_get_node_at(list, 0);
        if (current != NULL)
        {
            sll_remove_node(&list, current);
            sll_destory_node(current);
        }
    }
    return 0;
}
