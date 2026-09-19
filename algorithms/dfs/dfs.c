#include "graph.h"
/*
방문한 정점에 방문햇음 이라고 표시

현재 정점의 모든 인접 정점에 대해 DFS를 재귀호출

인접 정점을 시작으로 다시 깊이 우선 탐색 수행

*/
void dfs(Vertex *v)
{
    Edge *e = NULL;
    printf("%d ,", v->data);
    v->visited = Visited;
    e = v->adjacenc_list;

    while (e != NULL)
    {
        if (e->target != NULL && e->target->visited == NotVisted)
        {
            dfs(e->target);
        }
        e = e->next;
    }
}