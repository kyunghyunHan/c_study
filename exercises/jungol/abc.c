#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE(a) (sizeof(a)/sizeof((a)[0]))

// ¿Œ¡¢ ∏ÆΩ∫∆Æ - πŸ¿Ã∑ØΩ∫ (BFS/DFS)
#if 01
#define MAX (101)
int arr[MAX][MAX] = { 0 };  // ¿Œ¡¢«‡∑ƒ
int V;

void print_arr(int (*arr)[MAX], int v) {
	printf("arr\n");
	for (int i = 1; i <= v; ++i) {
		for (int j = 0; j <= arr[i][0]; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// BFS(Breadth-First Search, ≥ ∫Ò øÏº± ≈Ωªˆ)
// 1. Ω√¿€¡°(start)¿ª ≈•ø° ª¿‘, πÊπÆ«•Ω√
// 2. ≈•ø° ≥ªøÎ¿Ã ¿÷¥¬ µøæ» π›∫π (front != rear)
//   2-1. ≈•ø°º≠ ¡§¡°¿ª ≤®≥ø
//   2-2. ±◊ ¡§¡°∞˙ ø¨∞·µ» πÊπÆ«œ¡ˆ æ ¿∫ ¡§¡°¿ª √£¿Ω
//   2-3. "ø¨∞·¡°¿Ã ≥°¡°(end)¿Œ¡ˆ »Æ¿Œ«œ∞Ì æ∆¥œ∂Û∏È" ¡§¡°¿ª ≈•ø° ª¿‘, πÊπÆ«•Ω√
int virus_bfs(int start) {
	int queue[MAX];
	int front, rear;
	int used[MAX] = { 0 };
	int cnt = 0;

	front = rear = 0;
	queue[rear++] = start;
	used[start] = 1;
	while (front != rear) {
		int curr = queue[front++];
		//printf("%d\n", curr);
		for (int i = 1; i <= arr[curr][0]; ++i) {
			int next = arr[curr][i];
			if (!used[next]) {
				++cnt;
				queue[rear++] = next;
				used[next] = 1;
			}
		}
	}
	return cnt;
}

// DFS(Depth-First Search, ±Ì¿Ã øÏº± ≈Ωªˆ)
// 1. Ω√¿€¡°(start)¿ª Ω∫≈√ø° ª¿‘, πÊπÆ«•Ω√
// 2. Ω∫≈√ø° ≥ªøÎ¿Ã ¿÷¥¬ µøæ» π›∫π (top > 0)
//   2-1. Ω∫≈√ø°º≠ ¡§¡°¿ª ≤®≥ø
//   2-2. ±◊ ¡§¡°∞˙ ø¨∞·µ» πÊπÆ«œ¡ˆ æ ¿∫ ¡§¡°¿ª √£¿Ω
//   2-3. "ø¨∞·¡°¿Ã ≥°¡°(end)¿Œ¡ˆ »Æ¿Œ«œ∞Ì æ∆¥œ∂Û∏È" ¡§¡°¿ª Ω∫≈√ø° ª¿‘, πÊπÆ«•Ω√
int virus_dfs(int start) {
	int stack[MAX];
	int used[MAX] = { 0 };
	int cnt = 0;
	int top = 0;

	stack[top++] = start;
	used[start] = 1;
	while (top > 0) {
		int curr = stack[--top];
		//printf("%d\n", curr);
		for (int i = 1; i <= arr[curr][0]; ++i) {
			int next = arr[curr][i];
			if (!used[next]) {
				++cnt;
				stack[top++] = next;
				used[next] = 1;
			}
		}
	}
	return cnt;
}

// ¿Á±Õ «‘ºˆ∏¶ ªÁøÎ«— DFS ±∏«ˆ
int used[MAX] = { 0 };
int virus_cnt = 0;
void virus_reculsive(int curr) {
	for (int i = 1; i <= arr[curr][0]; ++i) {
		int next = arr[curr][i];
		if (!used[next]) {
			++virus_cnt;
			used[next] = 1;
			virus_reculsive(next);
		}
	}
}

int main(void) {

	int E, v1, v2;
	(void)freopen("06_data.txt", "r", stdin);
	(void)scanf("%d %d", &V, &E);
	for (int i = 0; i < E; ++i) {
		(void)scanf("%d %d", &v1, &v2);
		arr[v1][++arr[v1][0]] = v2;
		arr[v2][++arr[v2][0]] = v1;
	}
	//print_arr(arr, V);
	//printf("%d\n", virus_dfs(1));
	used[1] = 1;
	virus_cnt = 0;
	virus_reculsive(1);
	printf("%d\n", virus_cnt);
	return 0;
}
#endif

// ¿Œ¡¢ «‡∑ƒ - πŸ¿Ã∑ØΩ∫
#if 0
#define MAX (101)
int arr[MAX][MAX] = { 0 };  // ¿Œ¡¢«‡∑ƒ
int queue[MAX];
int front, rear;
int V;

void print_arr(int (*arr)[MAX], int v) {
	for (int i = 1; i <= v; ++i) {
		for (int j = 1; j <= v; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// BFS(Breadth-First Search, ≥ ∫Ò øÏº± ≈Ωªˆ)
// 1. Ω√¿€¡°(start)¿ª ≈•ø° ª¿‘, πÊπÆ«•Ω√
// 2. ≈•ø° ≥ªøÎ¿Ã ¿÷¥¬ µøæ» π›∫π (front != rear)
//   2-1. ≈•ø°º≠ ¡§¡°¿ª ≤®≥ø
//   2-2. ±◊ ¡§¡°∞˙ ø¨∞·µ» πÊπÆ«œ¡ˆ æ ¿∫ ¡§¡°¿ª √£¿Ω
//   2-3. "ø¨∞·¡°¿Ã ≥°¡°(end)¿Œ¡ˆ »Æ¿Œ«œ∞Ì æ∆¥œ∂Û∏È" ¡§¡°¿ª ≈•ø° ª¿‘, πÊπÆ«•Ω√
int virus_bfs(int start) {
	int used[MAX] = { 0 };
	int cnt = 0;
	front = rear = 0;
	queue[rear++] = start;
	used[start] = 1;
	while (front != rear) {
		int curr = queue[front++];
		//printf("%d\n", curr);
		for (int i = 1; i <= V; ++i) {
			if (arr[curr][i] && used[i] == 0) {
				++cnt;
				queue[rear++] = i;
				used[i] = 1;
			}
		}
	}
	return cnt;
}
     
int main(void) {

	int E, v1, v2;
	(void)scanf("%d %d", &V, &E);
	for (int i = 0; i < E; ++i) {
		(void)scanf("%d %d", &v1, &v2);
		arr[v1][v2] = arr[v2][v1] = 1;
	}
	print_arr(arr, V);
	printf("%d\n", virus_bfs(1));

	return 0;
}
#endif
