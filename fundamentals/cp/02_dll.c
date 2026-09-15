#include "02_dll.h"

/*
head와 tail 더미 노드를 생성하고 연결한다.

초기 상태:

HEAD <-> TAIL

head의 next_node는 tail
tail의 prev_node는 head
*/
void init_HT(Node **head, Node **tail)
{
    *head = (Node *)calloc(1, sizeof(Node));
    if (*head == NULL)
    {
        return;
    }
    *tail = (Node *)calloc(1, sizeof(Node));
    if (*tail == NULL)
    {
        free(*head);
        *head = NULL;

        return;
    }
    (**head).next_node = *tail;
    (**tail).prev_node = *head;
}

/*
data를 저장하는 새로운 노드를 동적 할당해서 생성한다.

생성 직후:

new_node
prev_node = NULL
next_node = NULL

성공하면 새 노드의 주소 반환
실패하면 NULL 반환
*/
Node *create_node(data_t *data)
{
    Node *new_node = NULL;
    new_node = (Node *)malloc(1 * sizeof(Node));
    if (new_node == NULL)
    {
        return;
    }
    else
    {
        new_node->data = *data;
        new_node->prev_node = NULL;
        new_node->next_node = NULL;
    }
    return new_node;
}

/*
tail 더미 노드 바로 앞에 new_node를 삽입한다.

삽입 전:

A <-> TAIL

삽입 후:

A <-> NEW <-> TAIL
*/
void append_node2(Node *tail, Node *new_node)
{
    new_node->next_node = tail;
    new_node->prev_node = tail->prev_node;
    tail->prev_node->next_node = new_node;
    tail->prev_node = new_node;
}

/*
head부터 시작해서 tail 위치를 직접 찾아간 뒤
tail 바로 앞에 new_node를 삽입한다.

삽입 전:

HEAD <-> A <-> B <-> TAIL

삽입 후:

HEAD <-> A <-> B <-> NEW <-> TAIL
*/
void append_node(Node **head, Node *new_node)
{
    if (head == NULL || *head == NULL || new_node == NULL)
    {
        return;
    }

    Node *tail = *head;

    while (tail->next_node != NULL)
    {
        tail = tail->next_node;
    }

    new_node->next_node = tail;
    new_node->prev_node = tail->prev_node;

    tail->prev_node->next_node = new_node;
    tail->prev_node = new_node;
}

/*
tail 포인터를 이미 알고 있다고 가정한다.

tail 바로 앞에 new_node를 삽입한다.

삽입 전:

A <-> TAIL

삽입 후:

A <-> NEW <-> TAIL
*/
void append_node3(Node *tail, Node *new_node)
{
}

/*
current를 기준으로 새로운 노드를 연결한다.

주의:
현재 네 코드의 함수 이름은 insert_after지만,
기존 구현이 실제로 의도한 연결 위치가 맞는지
직접 생각하면서 구현할 것.

목표를 정말 current 뒤 삽입으로 잡는다면:

CURRENT <-> B

↓

CURRENT <-> NEW <-> B
*/
void insert_after(Node *current, Node *new_node)
{
    new_node->prev_node = current;
    new_node->next_node = current->next_node;
    current->next_node->prev_node = new_node;
    current->next_node = new_node;
}

/*
서로 연결되어 있는 a와 b 사이에 new_node를 삽입한다.

삽입 전:

A <-> B

삽입 후:

A <-> NEW <-> B
*/
void insert_between(Node *a, Node *b, Node *new_node)
{
    new_node->prev_node = a;
    new_node->next_node = b;
    a->next_node = new_node;
    b->prev_node = new_node;
}

/*
head 더미 노드는 출력하지 않는다.
tail 더미 노드도 출력하지 않는다.

실제 데이터 노드만 처음부터 끝까지 순회하면서

id
score

를 출력한다.

구조:

HEAD <-> DATA <-> DATA <-> ... <-> TAIL
          ↑ 실제 데이터만 출력
*/
void print_node(Node *head)
{
    Node *current = head->next_node;

    while (current != NULL && current->next_node != NULL)
    {
        printf("%d %d\n",
               current->data.id,
               current->data.score);

        current = current->next_node;
    }
}
void destroy_dll(Node **head, Node **tail)
{
    Node *current;

    if (head == NULL)
    {
        return;
    }

    current = *head;

    while (current != NULL)
    {
        Node *next = current->next_node;
        free(current);
        current = next;
    }

    *head = NULL;

    if (tail != NULL)
    {
        *tail = NULL;
    }
}