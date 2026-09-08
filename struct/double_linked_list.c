/*
더블 링크드 리스트
탐색 기능을 개선

*/

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
// prev_node에 NULL 만 대입
Node *dll_create_node(ElementType new_data)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->data = new_data;
    new_node->prev_node = NULL;
    new_node->next_node = NULL;

    return new_node;
}
// 삭제 동일
void dll_destory_node(Node *node)
{
    free(node);
}
// 새로운 테일의 prev포인터도 기존 테일의 주소를 가리키도록
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
// 노드찾기
Node *dll_get_node_at(Node *head, int location)
{
    Node *currrent = head;
    while (currrent != NULL && (--location) >= 0)
    {
        currrent = currrent->next_node;
    }
    return currrent;
}

/*복잡
삭제할 노드의 next_node포인터가 가리키던 노드를 이전노드의 Next포인터가 가리키게함
삭제할 노드의 prev_node가가리키던 노드를 다음 노드의 prev_포인터가 가리키게함
그다음 삭제할 노드의 Next_node와 prev_node는 NULL로 초기화f

*/
void dll_remove_node(Node **head, Node *remove)
{
    if (head == NULL || *head == NULL || remove == NULL)
    {
        return;
    }
    // 삭제할 노드가 첫 번째 노드(head)인 경우
    if (*head == remove)
    {
        // head를 삭제할 노드의 다음 노드로 이동
        *head = remove->next_node;

        // 다음 노드가 존재한다면
        // 새로운 head는 이전 노드가 없으므로 prev를 NULL로 설정
        if (*head != NULL)
        {
            (*head)->prev_node = NULL;
        }

        // 삭제할 노드의 연결을 모두 끊음
        remove->prev_node = NULL;
        remove->next_node = NULL;
    }
    else
    {
        Node *temp = remove;

        // 이전 노드가 존재하면
        // 이전 노드의 next가 삭제할 노드의 다음 노드를 가리키게 함
        if (remove->prev_node != NULL)
        {
            remove->prev_node->next_node = temp->next_node;
        }

        // 다음 노드가 존재하면
        // 다음 노드의 prev가 삭제할 노드의 이전 노드를 가리키게 함
        if (remove->next_node != NULL)
        {
            remove->next_node->prev_node = temp->prev_node;
        }

        // 삭제할 노드를 리스트에서 완전히 분리
        remove->prev_node = NULL;
        remove->next_node = NULL;
    }
}
/*
prevv포인터는 이전노드를 nextnode포인터로는 다음 노드를
이전노드의 next포인터와 다음노드의 prev포인터는 새노드를 가리키게함
*/
void dll_insert_after(Node *current, Node *new_node)
{
    if (current == NULL || new_node == NULL)
    {
        return;
    }

    (*new_node).next_node = current->next_node;
    (*new_node).prev_node = current;
    if (current->next_node != NULL)
    {
        current->next_node->prev_node = new_node;
    }
    current->next_node = new_node;
}
void dll_insert_new_head(Node **head, Node *new_head)
{
    if (head == NULL || new_head == NULL)
    {
        return;
    }

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
