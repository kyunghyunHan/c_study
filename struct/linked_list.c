/*
Node : 리스트의 목록을 이루는 개별요소
Head : 첫번째 노드
Tail : 마지막 노드

배열은 생성하는 시점에 반드시 크기를 지정

링크드 리스트 : 노드 연결해서 만든 리스트

사라져버린노드의 주소를 가지고 있기떄문에 힙이적합
*/

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

    new_node->data = new_data;  // 데이터를 저장
    new_node->next_node = NULL; // 다음 노드에 대한 포인터는 NULL로 초기화

    return new_node; // Node 의 주소를 반환
}
// 노드 소멸
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
        // tail의 next_node가 NUll댈떄까지 찾기
        while (tail->next_node != NULL)
        {

            tail = tail->next_node;
        }
        // tail을 찾아서 새로운 노드에 연결
        tail->next_node = new_node;
    }
}
// 비효율
Node *sll_get_node_at(Node *head, int location)
{
    // head부투 시작
    Node *currrent = head;
    // 반복문 돌면서 NULL이고 localtion이 0이면 찾음
    while (currrent != NULL && (--location) >= 0)
    {
        currrent = currrent->next_node;
    }
    return currrent;
}
//
void sll_remove_node(Node **head, Node *remove)
{
    // head 가 삭제할 노드랑 같다면
    if ((*head) == remove)
    {
        // head는 nextnode를 받음
        *head = remove->next_node;
    }
    else
    {
        // 첫번쨰 노드
        Node *current = *head;
        // 삭제하려는 노드 찾아서 해당 노드의 다음 노드를 이전노드의 Nextnode로 연결
        // remove의 "이전 노드"를 찾는다.

        while (current != NULL && current->next_node != remove)
        {
            current = current->next_node;
        }
        // 이전 노드를 찾았다면
        if (current != NULL)
        {
            // 이전노드의 next_node에 삭제할 노드의 next_node를 삽입
            current->next_node = remove->next_node;
        }
    }
}
// 새로운 노드삽입f
void sll_insert_after(Node *current, Node *new_node)
{
    // 새로운 노드의 nextnode는 현재 노드의 nextnode
    (*new_node).next_node = current->next_node;
    // 새로운 노드의 next노드는 new_node
    current->next_node = new_node;
}
// 새로운 노드를 리스트의 맨압에
void sll_insert_new_head(Node **head, Node *new_head)
{
    if (head == NULL || new_head == NULL)
    {
        return;
    }

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
// 노드 개수 새기
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
    Node *list = NULL;     // 첫번쨰 노드를 가리킬 포인터
    Node *current = NULL;  // 현재 노드를 가리킬 포인턴
    Node *new_node = NULL; // 새로운 노드를 가리킬 포인터

    for (i = 0; i < 5; i++)
    {
        new_node = sll_create_node(i);
        sll_append_node(&list, new_node); // 생성한 노드를 LIST 에 추가
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
