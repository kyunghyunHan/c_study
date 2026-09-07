#include <stdlib.h>
#include <stdio.h>
typedef int ElementType;
typedef struct tagNode
{
    ElementType data;
    struct tagNode *prev_node;
    struct tagNode *next_node;
} Node;

// node 생성
Node *dll_create_node(ElementType new_data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->prev_node = NULL;
    new_node->next_node = NULL;

    return new_node;
}

void dll_destory_node(Node *node)
{
    free(node);
}

void dll_append_node(Node **head, Node *new_node)
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
        new_node->prev_node = tail; // 기존 테일을 새로운 테일의 prevnode가 가리킴
    }
}
Node *dll_get_node_at(Node *head, int location)
{
    Node *currrent = head;
    while (currrent != NULL && (--location) >= 0)
    {
        currrent = currrent->next_node;
    }
    return currrent;
}

/*복잡 */
void dll_remove_node(Node **head, Node *remove)
{
    if ((*head) == remove)
    {
        *head = remove->next_node;
        if (*head != NULL)
        {
            (*head)->prev_node = NULL;
        }
        remove->prev_node = NULL;
        remove->next_node = NULL;
    }
    else
    {
        Node *temp = remove;
        if (remove->prev_node != NULL)
        {
            remove->prev_node->next_node = temp->next_node;
        }
        if (remove->next_node != NULL)
        {
            remove->next_node->prev_node = temp->prev_node;
        }
        remove->prev_node = NULL;
        remove->next_node = NULL;
    }
}

void dll_insert_after(Node *current, Node *new_node)
{

    (*new_node).next_node = current->next_node;
    (*new_node).prev_node = current;
    if (current->next_node != NULL)
    {
        current->next_node->prev_node = new_node;
        current->next_node = new_node;
    }
}
void dll_insert_new_head(Node **head, Node *new_head)
{
    if (*head == NULL)
    {
        *head = new_head;
    }
    else
    {
        new_head->next_node = *head;
        (*head)->prev_node = new_head;
        *head = new_head;
    }
}
int dll_get_node_count(Node *head)
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
    // 5개 노드 추가
    for (i = 0; i < 5; i++)
    {
        new_node = dll_create_node(i);
        dll_append_node(&list, new_node);
    }
    cnt = dll_get_node_count(list);
    for (i = 0; i < cnt; i++)
    {
        current = dll_get_node_at(list, i);
        printf("List[%d] : %d\n", i, current->data);
    }

    // 리스트의 세번째 노드뒤에 새 노드 삽입
    printf("\nInserting 3000 After [2]...\n\n");

    current = dll_get_node_at(list, 2);
    new_node = dll_create_node(3000);

    dll_insert_after(current, new_node);

    cnt = dll_get_node_count(list);
    for (i = 0; i < cnt; i++)
    {
        current = dll_get_node_at(list, i);
        printf("List[%d] : %d\n", i, (*current).data);
    }

    // 모든 노드를 메모리에서 제거

    printf("\nDestorying List..\n");
    for (int i = 0; i < cnt; i++)
    {
        current = dll_get_node_at(list, 0);
        if (current != NULL)
        {
            dll_remove_node(&list, current);
            dll_destory_node(current);
        }
    }
    return 0;
}
