#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 10
#define MAX_BODY 100

typedef struct
{
    int x;
    int y;
} Point;

typedef struct
{
    Point body[MAX_BODY];
    int length;
    int dx;
    int dy;
} Snake;
// 게임 맵을 전부 공백으로 초기화
void clear_map(char (*map)[WIDTH]){

}

// 맵 테두리에 # 출력용 벽 생성
// void make_wall(char (*map)[WIDTH]);

// Snake 초기 위치와 길이 설정
// void init_snake(Snake *snake);

// 현재 snake 좌표를 map에 표시
// 머리: O
// 몸통: o
// void put_snake_on_map(
//     char (*map)[WIDTH],
//     const Snake *snake);

// 먹이 좌표를 map에 * 로 표시
// void put_food_on_map(
//     char (*map)[WIDTH],
//     const Point *food);

// 맵 전체를 터미널에 출력
// void draw_map(
//     const char (*map)[WIDTH]);

// 뱀을 현재 dx, dy 방향으로 한 칸 이동
// body[0]이 머리
// void move_snake(Snake *snake);

// 뱀이 먹이를 먹었는지 검사
// 먹었으면 1
// 아니면 0
// int check_food(
//     const Snake *snake,
//     const Point *food);

// 먹이를 먹었을 때 길이 1 증가
// void grow_snake(Snake *snake);

// 벽 또는 자기 몸에 부딪혔는지 검사
// 충돌했으면 1
// 아니면 0
// int check_collision(
//     const Snake *snake);

// 랜덤한 위치에 먹이 생성
// void make_food(Point *food);

// 키 입력을 받아 방향 변경
// w = 위
// s = 아래
// a = 왼쪽
// d = 오른쪽
// void change_direction(
//     Snake *snake,
//     char input);
int main(void)
{
    char map[HEIGHT][WIDTH];

    Snake snake;

    Point food;

    // init_snake(&snake);
    // make_food(&food);

    printf("\033[2J");

    while (1)
    {
        clear_map(map);

        // make_wall(map);

        // put_food_on_map(map, &food);

        // put_snake_on_map(map, &snake);

        // printf("\033[H");

        // draw_map(map);

        // printf("length : %d\n", snake.length);

        // move_snake(&snake);

        // if (check_food(&snake, &food))
        // {
        //     grow_snake(&snake);

        //     make_food(&food);
        // }

        // if (check_collision(&snake))
        // {
        //     printf("GAME OVER\n");
        //     break;
        // }

        // usleep(200000);
    }

    return 0;
}