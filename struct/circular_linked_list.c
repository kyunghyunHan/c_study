#include <stdlib.h>
#include <stdio.h>

typedef int element_type;

typedef struct node
{
    element_type data;

    // 이전 노드를 가리키는 포인터
    struct node *prev_node;

    // 다음 노드를 가리키는 포인터
    struct node *next_node;

} node;

/*
    새로운 노드 생성

    처음 생성된 노드는 아직 리스트에 연결되지 않았으므로
    prev_node와 next_node는 NULL로 초기화한다.
*/
node *cdll_create_node(element_type new_data)
{
    node *new_node = malloc(sizeof(node));

    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = new_data;
    new_node->prev_node = NULL;
    new_node->next_node = NULL;

    return new_node;
}

/*
    노드 메모리 해제
*/
void cdll_destroy_node(node *target)
{
    free(target);
}

/*
    리스트의 마지막에 새로운 노드를 추가한다.
*/
void cdll_append_node(node **head, node *new_node)
{
    // 리스트가 비어있는 경우
    if (*head == NULL)
    {
        // 새로운 노드가 head가 된다.
        *head = new_node;

        /*
            노드가 하나뿐이어도 환형이므로
            자기 자신의 앞/뒤가 자기 자신이다.

               ┌──────┐
               ↓      │
              [10] ───┘
        */
        new_node->next_node = new_node;
        new_node->prev_node = new_node;
    }
    else
    {
        /*
            환형 이중 연결 리스트에서는
            head의 prev_node가 항상 tail이다.

            따라서 처음부터 끝까지 탐색할 필요가 없다.

            head
             ↓
            [0] ⇄ [1] ⇄ [2]
             ↑             ↑
             └─────────────┘
                       tail

            head->prev_node == tail
        */
        node *tail = (*head)->prev_node;

        /*
            기존 구조:

            tail ⇄ head

            여기에 new_node를 사이에 넣어서:

            tail ⇄ new_node ⇄ head

            로 만든다.
        */

        // 기존 tail의 다음 노드를 new_node로
        tail->next_node = new_node;

        // new_node의 이전 노드는 기존 tail
        new_node->prev_node = tail;

        // new_node의 다음 노드는 head
        new_node->next_node = *head;

        // head의 이전 노드는 새로운 tail(new_node)
        (*head)->prev_node = new_node;
    }
}

/*
    head에서 location만큼 이동하여
    해당 위치의 노드를 반환한다.

    예:

    head
     ↓
    [0] ⇄ [1] ⇄ [2] ⇄ [3]
     0      1      2      3

    location == 2
    → [2] 반환
*/
node *cdll_get_node_at(node *head, int location)
{
    // 빈 리스트 또는 잘못된 위치
    if (head == NULL || location < 0)
    {
        return NULL;
    }

    node *current = head;

    /*
        location만큼 next_node를 따라 이동한다.

        환형 리스트라서 NULL을 만나는 것이 아니라
        마지막 노드 다음에는 다시 head가 나온다.
    */
    while (location > 0)
    {
        current = current->next_node;
        location--;
    }

    return current;
}

/*
    리스트에서 remove 노드를 제거한다.

    환형 이중 연결 리스트에서는
    remove의 이전 노드와 다음 노드를
    서로 직접 연결하면 된다.

    Before:

    A ⇄ remove ⇄ B

    After:

    A ⇄ B
*/
void cdll_remove_node(node **head, node *remove)
{
    if (*head == NULL || remove == NULL)
    {
        return;
    }

    /*
        노드가 하나밖에 없는 경우

        remove->next_node == remove

             ┌──────┐
             ↓      │
           [remove]─┘
    */
    if (remove->next_node == remove)
    {
        // 리스트가 완전히 비게 된다.
        *head = NULL;
    }
    else
    {
        /*
            remove가 head라면
            다음 노드가 새로운 head가 된다.
        */
        if (*head == remove)
        {
            *head = remove->next_node;
        }

        /*
            remove를 건너뛰도록 연결한다.

            remove의 이전 노드
                    ↓
                    A ⇄ remove ⇄ B
                                ↑
                         remove의 다음 노드

            A.next = B
            B.prev = A
        */
        remove->prev_node->next_node = remove->next_node;
        remove->next_node->prev_node = remove->prev_node;
    }

    /*
        리스트와의 연결을 완전히 끊는다.
        이후 destroy_node()로 free할 수 있다.
    */
    remove->prev_node = NULL;
    remove->next_node = NULL;
}

/*
    current 바로 뒤에 new_node를 삽입한다.

    Before:

    current ⇄ next

    After:

    current ⇄ new_node ⇄ next
*/
void cdll_insert_after(node *current, node *new_node)
{
    if (current == NULL || new_node == NULL)
    {
        return;
    }

    /*
        current의 원래 다음 노드를
        new_node의 다음 노드로 저장
    */
    new_node->next_node = current->next_node;

    // new_node의 이전 노드는 current
    new_node->prev_node = current;

    /*
        기존 다음 노드의 prev를
        new_node로 변경
    */
    current->next_node->prev_node = new_node;

    /*
        current의 다음 노드를
        new_node로 변경
    */
    current->next_node = new_node;
}

/*
    새로운 노드를 새로운 head로 삽입한다.

    Before:

          head
           ↓
    tail ⇄ [0] ⇄ [1]

    After:

                head
                 ↓
    tail ⇄ new_head ⇄ [0] ⇄ [1]
*/
void cdll_insert_new_head(node **head, node *new_head)
{
    if (new_head == NULL)
    {
        return;
    }

    // 리스트가 비어있는 경우
    if (*head == NULL)
    {
        // new_head 하나로 환형 리스트 생성
        *head = new_head;

        new_head->next_node = new_head;
        new_head->prev_node = new_head;
    }
    else
    {
        /*
            기존 tail은
            head의 prev_node로 바로 찾을 수 있다.
        */
        node *tail = (*head)->prev_node;

        /*
            new_head를 기존 tail과 기존 head 사이에 삽입

            tail ⇄ new_head ⇄ old_head
        */

        // 새 head의 다음 노드는 기존 head
        new_head->next_node = *head;

        // 새 head의 이전 노드는 기존 tail
        new_head->prev_node = tail;

        // 기존 tail의 다음 노드는 새 head
        tail->next_node = new_head;

        // 기존 head의 이전 노드는 새 head
        (*head)->prev_node = new_head;

        // head 포인터가 새 노드를 가리키도록 변경
        *head = new_head;
    }
}

/*
    리스트에 존재하는 노드 개수를 반환한다.

    환형 리스트에서는 NULL이 나오지 않는다.

    따라서 다시 head로 돌아오면
    한 바퀴를 전부 돈 것이다.
*/
int cdll_get_node_count(node *head)
{
    // 빈 리스트
    if (head == NULL)
    {
        return 0;
    }

    int cnt = 0;
    node *current = head;

    do
    {
        cnt++;

        // 다음 노드로 이동
        current = current->next_node;

    } while (current != head);
    // 다시 head로 돌아오면 종료

    return cnt;
}

int main(void)
{
    int i = 0;
    int count = 0;
    node *list = NULL;
    node *new_node = NULL;
    node *current = NULL;

    //  노드 5개 추가
    for (i = 0; i < 5; i++)
    {
        new_node = cdll_create_node(i);
        cdll_append_node(&list, new_node);
    }

    //  리스트 출력
    count = cdll_get_node_count(list);
    for (i = 0; i < count; i++)
    {
        current = cdll_get_node_at(list, i);
        printf("list[%d] : %d\n", i, current->data);
    }

    //  리스트의 세번째 칸 뒤에 노드 삽입
    printf("\ninserting 3000 after [2]...\n\n");

    current = cdll_get_node_at(list, 2);
    new_node = cdll_create_node(3000);
    cdll_insert_after(current, new_node);

    printf("\nremoving node at 2...\n");
    current = cdll_get_node_at(list, 2);
    cdll_remove_node(&list, current);
    cdll_destroy_node(current);

    //  리스트 출력
    //  (노드 수의 2배만큼 루프를 돌며 환형임을 확인한다.)
    count = cdll_get_node_count(list);
    for (i = 0; i < count * 2; i++)
    {
        if (i == 0)
            current = list;
        else
            current = current->next_node;

        printf("list[%d] : %d\n", i, current->data);
    }

    //  모든 노드를 메모리에서 제거
    printf("\ndestroying list...\n");

    count = cdll_get_node_count(list);

    for (i = 0; i < count; i++)
    {
        current = cdll_get_node_at(list, 0);

        if (current != NULL)
        {
            cdll_remove_node(&list, current);
            cdll_destroy_node(current);
        }
    }

    return 0;
}
