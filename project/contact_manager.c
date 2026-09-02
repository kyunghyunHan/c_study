#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

typedef struct {
    char name[20];
    char phone[20];
}Contact;

// 연락처 하나를 추가한다.
// contacts 배열의 count 위치에 이름과 전화번호를 입력받아 저장
void add_contact(Contact *contacts,int *count);
// 전체 연락처를 출력한다.
// 포인터 연산을 사용해서 구현해볼 것.
// 가능하면 contacts[i] 대신 (contacts + i)를 사용해보기
void print_contacts(Contact *contacts,int count);

// 이름을 입력받아서 연락처를 찾는다.
// 찾으면 해당 Contact의 주소 반환
// 못 찾으면 NULL 반환
// Contact * find_contact(
//    Contact *contacts,
//    int count,
//    const char *name  
// );
// 이름을 입력받아서 연락처를 삭제한다.
// 삭제된 뒤 뒤쪽 연락처들을 한 칸씩 앞으로 이동
// void delete_contact(
//     Contact *contacts,
//     int *count,
//     const char *name
// );
// 이름 기준 오름차순 정렬
// qsort() 사용
// void sort_contacts(Contact *contacts, int count);
// qsort()에 넘길 비교 함수

// int compare_contact(const void *a, const void *b);


int main(){
    Contact contacts[MAX_CONTACTS]= {0};

    int count = 0;
    int menu;

    char name[20];

      char *menu_text[] = {
        "종료",
        "연락처 추가",
        "전체 출력",
        "연락처 검색",
        "연락처 삭제",
        "이름순 정렬"
    };
    
        while (1) {

        printf("\n===== Contact Manager =====\n");

        for (int i = 0; i < 6; i++) {
            printf("%d. %s\n", i, menu_text[i]);
        }

        printf("선택: \n ");
        scanf("%d", &menu);

        switch (menu) {

        case 0:
            printf("종료합니다.\n");
            return 0;

        case 1:
            add_contact(contacts, &count);
            break;

        case 2:
            print_contacts(contacts, count);
            break;

        // case 3: {
        //     printf("검색할 이름: ");
        //     scanf("%19s", name);

        //     Contact *result =
        //         find_contact(contacts, count, name);

        //     if (result != NULL) {
        //         printf("이름: %s\n", result->name);
        //         printf("전화번호: %s\n", result->phone);
        //     }
        //     else {
        //         printf("찾을 수 없습니다.\n");
        //     }

        //     break;
        // }

        // case 4:
        //     printf("삭제할 이름: ");
        //     scanf("%19s", name);

        //     delete_contact(contacts, &count, name);
        //     break;

        // case 5:
        //     sort_contacts(contacts, count);
        //     printf("정렬 완료\n");
        //     break;

        // default:
        //     printf("잘못된 입력입니다.\n");
        //     break;
         }
    }

}

// 연락처 하나를 추가한다.
// contacts 배열의 count 위치에 이름과 전화번호를 입력받아 저장
void add_contact(Contact *contacts, int *count)
{
    char name[20];
    char phone[20];

    scanf("%19s %19s", name, phone);

    strcpy((contacts + *count)->name, name);
    strcpy((contacts + *count)->phone, phone);

    (*count)++;
}

void print_contacts(Contact *contacts,int count){
    for (int i = 0; i<count;i++){
        printf("name:%s phone:%s\n",(contacts+i)->name,(contacts+i)->phone);
    }
}

// 이름을 입력받아서 연락처를 찾는다.
// 찾으면 해당 Contact의 주소 반환
// 못 찾으면 NULL 반환
// Contact * find_contact(
//    Contact *contacts,
//    int count,
//    const char *name  
// );
// 이름을 입력받아서 연락처를 삭제한다.
// 삭제된 뒤 뒤쪽 연락처들을 한 칸씩 앞으로 이동
// void delete_contact(
//     Contact *contacts,
//     int *count,
//     const char *name
// );
// 이름 기준 오름차순 정렬
// qsort() 사용
// void sort_contacts(Contact *contacts, int count){

// }
// qsort()에 넘길 비교 함수

// int compare_contact(const void *a, const void *b){

// }
