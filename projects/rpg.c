#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 10

typedef struct
{
    char name[20];
    int attack;
    int price;
} Item;

typedef struct
{
    char name[20];
    int hp;
    int attack;

    Item inventory[MAX_ITEMS];
    int item_count;

    Item *weapon;
} Player;

typedef struct
{
    char name[20];
    int hp;
    int attack;
} Monster;

// 플레이어 초기화
void init_player(Player *player);

// 몬스터 초기화
void init_monster(Monster *monster);

// // 인벤토리에 아이템 추가
void add_item(Player *player);

// 인벤토리 전체 출력
void print_inventory(const Player *player);
// // 이름으로 아이템 검색
// // 찾으면 해당 Item의 주소 반환
// // 없으면 NULL 반환
Item *find_item(
    Player *player,
    const char *name);

// // 아이템 삭제
// // 삭제 후 뒤의 아이템들을 앞으로 한 칸씩 이동
void delete_item(
    Player *player,
    const char *name);

// // 무기 장착
// // find_item()을 이용해서
// // player->weapon에 Item의 주소 저장
void equip_item(
    Player *player,
    const char *name);

// 플레이어 정보 출력
void print_player(
    const Player *player);

// // 플레이어가 몬스터 공격
// void attack_monster(
//     Player *player,
//     Monster *monster
// );

// // 몬스터가 플레이어 공격
// void attack_player(
//     Monster *monster,
//     Player *player
// );

// qsort용 비교 함수
// 이름순으로 정렬
int compare_item(
    const void *a,
    const void *b);

// 인벤토리를 이름순으로 정렬
void sort_inventory(
    Player *player);

int main(void)
{
    Player player;
    Monster monster;

    int menu;

    char item_name[20];

    init_player(&player);
    init_monster(&monster);

    while (1)
    {
        printf("\n");
        printf("===== RPG GAME =====\n");

        printf("0. 종료\n");
        printf("1. 플레이어 정보\n");
        printf("2. 아이템 추가\n");
        printf("3. 인벤토리 출력\n");
        printf("4. 아이템 검색\n");
        printf("5. 아이템 삭제\n");
        printf("6. 무기 장착\n");
        printf("7. 인벤토리 정렬\n");
        printf("8. 몬스터와 전투\n");

        printf("선택: ");

        scanf("%d", &menu);

        switch (menu)
        {
        case 0:

            printf("게임 종료\n");

            return 0;

        case 1:

            print_player(&player);

            break;

        case 2:

            add_item(&player);

            break;

        case 3:

            print_inventory(&player);

            break;

        case 4:
        {
            printf("검색할 아이템 이름: ");

            scanf("%19s", item_name);

            Item *result =
                find_item(&player, item_name);

            if (result != NULL)
            {
                printf("이름 : %s\n", result->name);
                printf("공격력 : %d\n", result->attack);
                printf("가격 : %d\n", result->price);
            }
            else
            {
                printf("아이템이 없습니다.\n");
            }

            break;
        }

        case 5:

            printf("삭제할 아이템 이름: ");

            scanf("%19s", item_name);

            delete_item(
                &player,
                item_name);

            break;

        case 6:

            printf("장착할 아이템 이름: ");

            scanf("%19s", item_name);

            equip_item(
                &player,
                item_name);

            break;

        case 7:

            sort_inventory(&player);

            printf("정렬 완료\n");

            break;

            // case 8:

            //     printf("\n");
            //     printf("===== BATTLE =====\n");

            //     while (
            //         player.hp > 0 &&
            //         monster.hp > 0
            //     )
            //     {
            //         attack_monster(
            //             &player,
            //             &monster
            //         );

            //         if (monster.hp <= 0)
            //         {
            //             printf("%s 처치!\n",
            //                    monster.name);

            //             break;
            //         }

            //         attack_player(
            //             &monster,
            //             &player
            //         );

            //         if (player.hp <= 0)
            //         {
            //             printf("%s 사망!\n",
            //                    player.name);

            //             break;
            //         }
            //     }

            //     break;

        default:

            printf("잘못된 메뉴입니다.\n");

            break;
        }
    }
}
/*
typedef struct {
    char name[20];
    int hp;
    int attack;

    Item inventory[MAX_ITEMS];
    int item_count;

    Item *weapon;
} Player;
 */
void init_player(Player *player)
{
    strcpy(player->name, "바보");

    player->hp = 200;
    player->attack = 20;

    strcpy(player->inventory[0].name, "Sword");
    player->inventory[0].attack = 10;
    player->inventory[0].price = 100;

    player->item_count = 1;
    player->weapon = NULL;
}
/*
typedef struct
{
    char name[20];
    int hp;
    int attack;
} Monster;

 */
void init_monster(Monster *monster)
{
    strcpy((*monster).name, "골렘");
    (*monster).hp = 200;
    (*monster).attack = 10;
}

// 플레이어 정보 출력
void print_player(
    const Player *player)
{
    int len = (*player).item_count;
    int index = len - 1;
    printf("이름 : %s\n", (*player).name);
    printf("hp : %d\n", (*player).hp);
    printf("attack : %d\n", (*player).attack);
    printf("가지고 있는 아이템 수 : %d\n", len);
    for (int i = 0; i < len; i++)
    {
        printf("무기 이름 : %s\n", (*player).inventory[i].name);
        printf("무기 공격력 : %d\n", (*player).inventory[i].attack);
        printf("무기 가격  : %d\n", (*player).inventory[i].price);
    }
    printf("장착 아이템 : %s\n", (*(*player).weapon).name);
}

void add_item(Player *player)
{
    ++(*player).item_count;
    int len = (*player).item_count;
    int index = len - 1;

    strcpy((*player).inventory[index].name, "워터");
    (*player).inventory[index].attack = 1;
    (*player).inventory[index].price = 20;
}

void print_inventory(const Player *player)
{
    int len = (*player).item_count;

    for (int i = 0; i < len; i++)
    {
        printf("무기%d : %s\n", i, (*player).inventory[i].name);
    }
}

// // 이름으로 아이템 검색
// // 찾으면 해당 Item의 주소 반환
// // 없으면 NULL 반환
Item *find_item(
    Player *player,
    const char *name)
{
    int len = (*player).item_count;

    for (int i = 0; i < len; i++)
    {
        if (strcmp((*player).inventory[i].name, name) == 0)
        {
            printf("찾았다\n");

            return &player->inventory[i];
        }
    }
    return NULL;
}

// // 아이템 삭제
// // 삭제 후 뒤의 아이템들을 앞으로 한 칸씩 이동
void delete_item(
    Player *player,
    const char *name)
{
    Item *result = find_item(player, name);
    if (result == NULL)
    {
        printf("아이템을 찾을수 없습니다.");
        return;
    }
    int index = result - player->inventory;
    for (int i = index; i < player->item_count - 1; i++)
    {
        player->inventory[i] = player->inventory[i + 1];
    }
    (player->item_count)--;
}

// // 무기 장착
// // find_item()을 이용해서
// // player->weapon에 Item의 주소 저장
void equip_item(
    Player *player,
    const char *name)
{
    Item *result = find_item(player, name);
    if (result == NULL)
    {
        printf("아이템을 찾을수 없습니다.");
        return;
    }
    (*player).weapon = result;
}


int compare_item(
    const void *a,
    const void *b)
{
    const Item *item_a = a;
    const Item *item_b = b;

    return strcmp(item_a->name, item_b->name);
}

// 인벤토리를 이름순으로 정렬
void sort_inventory(
    Player *player)
{
    qsort(
        player->inventory,        // 정렬할 배열 시작 주소
        player->item_count,           // 원소 개수
        sizeof(Item), // 원소 하나의 크기
        compare_item  // 비교 함수
    );
}
