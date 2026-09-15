#ifndef __02_CLL_H__
#define __02_CLL_H__
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "02_cll.h"

#define SIZE(a) (sizeof(a) / sizeof((a)[0]))
typedef struct data
{
    int id;
    int score;
} data_t;
typedef struct Node
{
    data_t data;
    struct Node *next;
    struct Node *prev;
} Node;

/*
삽입 , 삭제 , 탐색 세가지 연산에 대해 링크드리스트와  배열의 성능비교


환형 링크드 리스트의장점 - 헤드 노드를 이용히여 테일 노드의 위치를 파악 링크드나 더블링크드에서도 테일 노드의 위치를 바로 알아내는법

구현한 프로그램들은 노드 개수를 알아내는데 비효율적 노드의 개수가 N개라면 N개의 루프를 수행해야 비로서 N 을 알수잇음 노드의 개수를 바로 알아내는법


탐색	인덱스 접근이면 O(1)	처음부터 따라가야 해서 O(N)
값으로 탐색	O(N)	O(N)
삽입	중간 삽입 시 뒤 원소 이동 → O(N)	삽입 위치 노드를 이미 알고 있으면 포인터만 변경 → O(1)
삭제	중간 삭제 시 뒤 원소 이동 → O(N)	삭제할 노드를 이미 알고 있으면 포인터만 변경 → O(1)

typedef struct tagLinkedList
{
    Node *head;     // 첫 번째 노드
    Node *tail;     // 마지막 노드
    size_t count;   // 현재 노드 개수
} LinkedList;
*/

#include <stdlib.h>
#include <stdio.h>

/*
    새로운 노드 생성

    처음 생성된 노드는 아직 리스트에 연결되지 않았으므로
    prev_node와 next_node는 NULL로 초기화한다.
*/
Node *create_node(data_t new_data);
void destroy_node(Node *target);
void append_node(Node **head, Node *new_node);
Node *get_node_at(Node *head, int location);
void remove_node(Node **head, Node *remove);
void insert_after(Node *current, Node *new_node);
void insert_new_head(Node **head, Node *new_head);
int get_node_count(Node *head);

#endif