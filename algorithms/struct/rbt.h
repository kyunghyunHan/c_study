#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef int ElementType;

/*
모든 노드는 빨간색 이거나 검은색
뿌리노드는 검은색
잎노는 검은색
빨간색 노드의 자식은 모두 검은색(검은색 노드는 빨간색 과 검은색 모두 자식으로 가질수있다)
뿌리 노드와 모든 잎 노드 사이의 검은색 노드수는 동일

NIL 검은 노드 = > 더미 노드

*/
typedef struct RbtNode
{
    struct RbtNode *parent;
    struct RbtNode *left;
    struct RbtNode *right;

    enum
    {
        RED,
        BLACK
    } Color;
    ElementType data;
} RbtNode;
#endif