#include "../struct/linked_list.h"
/*
gcc -Wall -Wextra \
  ./search/sequential_search.c \
  ./struct/linked_list.c \
  -o test && ./test
*/

#include <stdio.h>

Node *sll_sequential_search(Node *head, int target)
{
    Node *current = head;
    Node *match = NULL;
    while (current != NULL)
    {
        if (current->data == target) // 찾고자 하는 해당 값의 노드가 가지고 잇으면 노드의주소를 MAtch에저장
        {
            match = current;
            break;
        }
        else
        {
            current = current->next_node; // 현재 노등에 찾는 값이 없으면 다음 노드 조사
        }
    }

    return match; // 찾고있는 값을 가진 노드의 주소반환
}
// 전진 이동법
Node *sll_move_to_front(Node **head, int target)
{
    Node *current = *head;
    Node *previous = NULL;

    while (current != NULL)
    {
        if (current->data == target) // 순차탐색으토해 검색ㄹ
        {
            if (previous != NULL)
            {
                // 자신의 이전 노드와 다음 노드를 연결
                previous->next_node = current->next_node;
                // 자신을 가장 앞으로 이동
                current->next_node = *head;
                *head = current;
            }
            return current;
        }

        previous = current;
        current = current->next_node;
    }

    return NULL;
}
// 전위법 위치를 번경 : 자주탐색된 항목을 조금씩 앞으로 옮김
Node *sll_transpose(Node **head, int target)
{
    Node *current = *head;
    Node *previous_previous = NULL;
    Node *previous = NULL;

    while (current != NULL)
    {
        if (current->data == target)
        {
            if (previous != NULL)
            {
                if (previous_previous != NULL)
                    previous_previous->next_node = current;
                else
                    *head = current;

                previous->next_node = current->next_node;
                current->next_node = previous;
            }
            return current;
        }

        previous_previous = previous;
        previous = current;
        current = current->next_node;
    }

    return NULL;
}
/*계수법
데이터가 각 요소가 탐색된 횟수를 별도의 공간에 저장
탐색된 횟수가 높은 순으로 데이터를 재ㅜ구성
SLL_FrequencyCount
*/
int main(void)
{
    int i;
    int init_value[10] = {1, 2, 6, 10, 4, 9, 5, 3, 8, 7};
    Node *list = NULL;
    Node *current;
    Node *new_node;
    Node *match;

    for (i = 0; i < 10; i++)
    {
        new_node = sll_create_node(init_value[i]);
        sll_append_node(&list, new_node);
    }

    printf("Simple Sequential Search...\n");
    match = sll_sequential_search(list, 9);
    if (match != NULL)
        printf("Found : %d\n", match->data);
    else
        printf("Not Found : 9\n");

    printf("Move To Front...\n");
    match = sll_move_to_front(&list, 4);
    if (match != NULL)
        printf("Found : %d\n", match->data);
    else
        printf("Not Found : 4\n");

    printf("Transpose...\n");
    match = sll_transpose(&list, 7);
    if (match != NULL)
        printf("Found : %d\n", match->data);
    else
        printf("Not Found : 7\n");

    printf("Destroying List...\n");
    while (list != NULL)
    {
        current = list;
        sll_remove_node(&list, current);
        sll_destroy_node(current);
    }

    return 0;
}
