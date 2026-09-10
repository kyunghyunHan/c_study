#include <assert.h>
// #include <inttypes.h>
#include <stdbool.h>
#include <stdint.h> // used for uint32_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>

/*
 * 간단한 메모리 할당기(my malloc) 구현 예제
 *
 * 전체 흐름
 * 1) macOS에서는 mmap()으로 큰 가상 메모리 영역을 미리 확보한다.
 * 2) my_sbrk()가 그 영역 안에서 논리적인 힙 끝(program break)을 움직인다.
 * 3) an_malloc()이 요청 크기에 맞는 빈 블록을 찾고, 필요하면 블록을 분할한다.
 * 4) an_free()가 블록을 비우고, 앞/뒤의 빈 블록과 병합한다.
 * 5) 힙 끝에 큰 빈 공간이 남으면 논리적인 힙 크기를 페이지 단위로 줄인다.
 *
 * 주의: 이것은 학습용 allocator이며 실제 libc malloc()을 대체하려는 구현은 아니다.
 */

// 표준 출력으로 디버그 문자열을 바로 출력한다.
void debug_log(const char *msg) { write(STDOUT_FILENO, msg, strlen(msg)); }
// extern long int etext, edata, end;
/* 각 메모리 블록 앞에 붙는 헤더
 * prev/next로 모든 블록을 이중 연결 리스트로 관리한다.
 */
struct free_area {
  uint8_t marker;          // 정상적인 블록 헤더인지 확인하기 위한 매직 값
  struct free_area *prev;  // 이전 블록 헤더 주소
  bool in_use;             // true: 사용 중, false: 빈 블록
  uint32_t length;         // 이 블록의 실제 데이터 영역 크기(바이트)
  struct free_area *next;  // 다음 블록 헤더 주소
};

/* allocator 전체 상태를 힙의 맨 앞에 저장하는 헤더 */
struct stats {
  int magical_bytes;           // allocator가 초기화되었는지 확인하는 값
  bool my_simple_lock;         // 아주 단순한 동시 접근 방지용 플래그
  uint32_t amount_of_blocks; // 현재 블록 개수
  uint16_t amount_of_pages;  // 현재 논리적으로 사용 중인 페이지 수
};

typedef struct stats my_stats;
typedef struct free_area area;

const int MAGICAL_BYTES = 0x55; // allocator 초기화 확인용 매직 값
const int BLOCK_MARKER = 0xDD;  // 각 블록 헤더의 정상 여부 확인용 값
const int FIRST_BLOCK_OFFSET = sizeof(area); // 첫 블록 헤더 크기(현재 코드에서는 직접 사용하지 않음)
const int PAGE_SIZE = 4096; // 학습용 페이지 크기 4KB

char *heap_start = NULL; // allocator가 관리하는 힙의 시작 주소

/*
 * macOS 호환 계층
 *
 * Linux 예제에서 사용하던 sbrk() 대신 mmap()으로 큰 가상 메모리 공간을 한 번 확보한다.
 * 그 안에서 heap_break라는 논리적인 program break를 움직여 sbrk() 동작을 흉내 낸다.
 */
#define HEAP_RESERVE_SIZE (64UL * 1024UL * 1024UL) // 최대 64MB를 가상 힙으로 예약

static char *heap_reserve_start = NULL; // mmap으로 예약한 전체 영역의 시작
static char *heap_reserve_end = NULL;   // mmap으로 예약한 전체 영역의 끝
static char *heap_break = NULL;         // 현재 논리적인 힙의 끝(program break)

/* mmap()으로 가상 힙을 한 번만 준비한다. */
static int init_heap_reserve(void) {
  // 이미 초기화되었다면 다시 mmap하지 않는다.
  if (heap_reserve_start != NULL) {
    return 0;
  }

  // 주소는 OS가 정하고, 읽기/쓰기가 가능한 익명 private 메모리 64MB를 요청한다.
  void *p = mmap(NULL, HEAP_RESERVE_SIZE,
                 PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANON,
                 -1, 0);

  // mmap 실패 시 -1 반환
  if (p == MAP_FAILED) {
    return -1;
  }

  // mmap 결과를 allocator 내부 포인터들에 기록한다.
  heap_reserve_start = (char *)p;
  heap_reserve_end = heap_reserve_start + HEAP_RESERVE_SIZE;
  heap_break = heap_reserve_start;
  return 0;
}

/*
 * sbrk() 흉내 함수
 * increment > 0 : 힙 확장
 * increment < 0 : 힙 축소
 * increment == 0: 현재 heap_break 조회
 */
static void *my_sbrk(intptr_t increment) {
  if (init_heap_reserve() != 0) {
    errno = ENOMEM;
    return (void *)-1;
  }

  // 실제 sbrk()처럼 변경 전 break 주소를 반환하기 위해 저장한다.
  char *old_break = heap_break;

  // 힙을 늘리는 경우: 예약한 64MB 끝을 넘는지 검사
  if (increment > 0) {
    if ((size_t)(heap_reserve_end - heap_break) < (size_t)increment) {
      errno = ENOMEM;
      return (void *)-1;
    }
  } else if (increment < 0) {
    // 힙을 줄이는 경우: 예약 영역의 시작보다 아래로 내려가면 안 된다.
    if ((size_t)(heap_break - heap_reserve_start) < (size_t)(-increment)) {
      errno = EINVAL;
      return (void *)-1;
    }
  }

  // 논리적인 힙 끝 이동
  heap_break += increment;
  return old_break;
}

// 뒤에서 정의되는 마지막 블록 검색 함수의 전방 선언
area *find_last_block();

/* 힙 시작 주소를 allocator 전체 통계 헤더(my_stats)로 해석한다. */
my_stats *get_malloc_header() {
  assert(heap_start != NULL);
  my_stats *malloc_header = (my_stats *)heap_start;
  assert(malloc_header->magical_bytes == MAGICAL_BYTES);
  return malloc_header;
}

/* 현재 블록에서 뒤로 이동하면서 가장 가까운 사용 중 블록을 찾는다. */
area *find_previous_used_block(area *ptr) {
  area *mov_ptr = ptr;
  while (mov_ptr->prev != NULL) {
    mov_ptr = mov_ptr->prev;
    if (mov_ptr->in_use == true) {
      return mov_ptr;
    }
  }
  return NULL;
}

/* allocator 헤더 바로 뒤에 위치한 첫 메모리 블록을 반환한다. */
area *find_first_block() {
  my_stats *malloc_header = get_malloc_header();
  return (area *)((char *)malloc_header + sizeof(my_stats));
}

/*
 * 힙 끝부분에 큰 빈 공간이 남았다면 PAGE_SIZE(4096) 단위로
 * 논리적인 heap_break를 뒤로 당겨 allocator의 사용 크기를 줄인다.
 */
void reduce_heap_size_if_possible() {
  // 연결 리스트의 마지막 블록 확인
  area *last_block = find_last_block();
  // 마지막 블록 기준으로 가장 가까운 사용 중 블록을 찾는다.
  area *prev_used_block = find_previous_used_block(last_block);
  if (prev_used_block == NULL) {
    // 사용 중 블록이 하나도 없다면 첫 블록은 유지하고 최소 1페이지는 남긴다.
    if (last_block->length > PAGE_SIZE) {
      last_block->length = PAGE_SIZE;
    }
    prev_used_block = last_block;
  }
  // 마지막 사용 중 블록의 데이터 끝 주소
  void *new_end =
      (char *)prev_used_block + sizeof(area) + prev_used_block->length;
  // 현재 논리적인 힙의 끝 주소 조회
  void *heap_end = my_sbrk(0);
  // 뒤쪽에 한 페이지 이상 여유가 있으면 페이지 단위로 힙을 축소한다.
  while ((char *)new_end < (char *)heap_end - PAGE_SIZE) {
    my_sbrk(-PAGE_SIZE);
    heap_end = my_sbrk(0);
    my_stats *malloc_header = get_malloc_header();
    malloc_header->amount_of_pages -= 1;
  }
  // 힙을 줄이고도 마지막 사용 블록 뒤에 여유 공간이 남으면
  // 그 공간을 하나의 새로운 free block으로 만들어 연결 리스트 끝에 붙인다.
  if ((size_t)((char *)heap_end - (char *)new_end) > sizeof(area) + 1) {
    area *new_not_used_block = (area *)new_end;
    new_not_used_block->marker = BLOCK_MARKER;
    new_not_used_block->in_use = false;
    new_not_used_block->prev = prev_used_block;
    new_not_used_block->next = NULL;
    new_not_used_block->length = (char *)heap_end - (char *)new_end - sizeof(area);
    prev_used_block->next = new_not_used_block;
  }
}

/*
 * 사용자에게 반환했던 데이터 포인터 ptr을 해제한다.
 * 블록 헤더는 ptr 바로 앞(sizeof(area) 바이트 전)에 있다.
 */
bool an_free(void *ptr) {
  my_stats *malloc_header = get_malloc_header();
  // 다른 malloc/free가 동작 중이면 단순 대기
  while (malloc_header->my_simple_lock) {
    sleep(1);
  };
  // allocator 잠금
  malloc_header->my_simple_lock = true;
  // ptr은 블록 헤더가 아니라 사용자 데이터 영역의 시작 주소이므로
  // sizeof(area)만큼 뒤로 이동해 블록 헤더를 찾는다.
  area *block = (area *)((char *)ptr - sizeof(area));
  // 올바른 allocator 블록인지 marker로 검사
  if (block->marker != BLOCK_MARKER) {
    // 이 allocator가 반환한 정상적인 블록 시작점이 아님
    return false;
  } else {
    // 현재 블록을 free 상태로 변경
    block->in_use = false;
    // 학습용으로 사용자 데이터 영역을 0으로 지운다.
    memset(ptr, 0, block->length);
    if (block->next != NULL && (block->next)->in_use == false) {
      // 다음 블록도 비어 있으면 현재 블록과 병합한다.
      area *not_used_next_block = block->next;
      // 연결 리스트에서 다음 free block의 헤더를 제거한다.
      if (not_used_next_block != NULL) {
        // 현재 블록을 다음다음 블록과 직접 연결한다.
        block->next = not_used_next_block->next;
        // 다음다음 블록이 있다면 prev 포인터도 현재 블록으로 되돌려 연결한다.
        if (not_used_next_block->next != NULL) {
          not_used_next_block->next->prev = block;
        }
      } else {
        block->next = NULL; // 마지막 블록임을 명시
      }
      // 병합하면서 다음 블록의 헤더 크기 + 데이터 크기까지 현재 블록 길이에 더한다.
      block->length += sizeof(area) + not_used_next_block->length;
      // 제거되는 다음 블록의 헤더와 데이터 영역을 0으로 지운다.
      memset((void *)not_used_next_block, 0,
             sizeof(area) + not_used_next_block->length);
      malloc_header->amount_of_blocks -= 1;
      // 10);
    }
    if (block->prev != NULL && (block->prev)->in_use == false) {
      // 이전 블록도 비어 있으면 이전 블록과 현재 블록을 다시 병합한다.
      area *to_delete_block = block;
      block = block->prev;
      // 이전 블록의 크기를 현재 블록까지 포함하도록 확장한다.
      block->length += sizeof(area) + to_delete_block->length;
      // 연결 리스트에서 현재 블록 헤더를 건너뛰도록 연결한다.
      block->next = to_delete_block->next;
      // 다음 블록의 prev 포인터도 병합된 블록으로 수정한다.
      if (block->next != NULL) {
        block->next->prev = block;
      }
      malloc_header->amount_of_blocks -= 1;
    }
    reduce_heap_size_if_possible();
  }
  malloc_header->my_simple_lock = false; // allocator 잠금 해제
  return true;
}

/* next 포인터를 따라가 연결 리스트의 마지막 블록을 반환한다. */
area *find_last_block() {
  my_stats *malloc_header = get_malloc_header();
  area *block = (area *)((char *)malloc_header + sizeof(my_stats));
  while (block->next != NULL) {
    block = block->next;
  }
  return block;
}

/*
 * 실제 할당 핵심 함수
 * 1) size 이상을 담을 수 있는 가장 작은 free block(best fit)을 찾는다.
 * 2) 없으면 my_sbrk()로 힙을 페이지 단위 확장한다.
 * 3) 선택된 블록을 사용 중으로 바꾸고 남는 공간은 새 free block으로 분할한다.
 */
int *add_used_block(ssize_t size) {
  // 힙 시작 부분을 allocator 전체 상태 헤더(my_stats)로 해석한다.
  my_stats *malloc_header = get_malloc_header();
  // 다른 malloc/free가 동작 중이면 단순 대기
  while (malloc_header->my_simple_lock) {
    sleep(1);
  };
  // allocator 잠금
  malloc_header->my_simple_lock = true;
  // 모든 블록을 순회하면서 요청 크기를 수용할 수 있는 가장 작은 free block을 찾는다.
  area *block = (area *)((char *)heap_start + sizeof(my_stats));
  area *smallest_block = NULL;
  area *last_block = block;
  // best-fit 전략: 들어갈 수 있는 블록 중 가장 작은 블록 선택
  while (block != NULL) {
    assert(block->marker == BLOCK_MARKER);
    if ((size_t)block->length + sizeof(area) >= (size_t)size && block->in_use == false) {
      if (smallest_block == NULL || smallest_block->length > block->length) {
        smallest_block = block;
      }
    }
    last_block = block;
    block = block->next;
  }
  // 충분히 큰 free block이 없다면 마지막 free block을 힙 확장으로 키운다.
  if (smallest_block == NULL) {
    // 연결 리스트의 마지막 블록 확인
  area *last_block = find_last_block();
    // 요청 크기를 수용할 때까지 4KB씩 확장
    while (last_block->length < size) {
      my_sbrk(4096);
      last_block->length += 4096;
      malloc_header->amount_of_pages += 1;
    }
    smallest_block = last_block;
  }
  // 사용할 블록을 찾았으므로 사용 중 상태로 변경
  smallest_block->in_use = true;
  // 사용하고 남는 공간에는 새로운 free block을 만든다.
  // 새 블록은 area 헤더 + 최소 1바이트 데이터 공간이 필요하다.
  int must_have_size = smallest_block->length - size - sizeof(area) - 1;
  // 새 free block을 만들 공간이 부족하면 페이지 하나를 더 확장한다.
  if (must_have_size <= 0) {
    my_sbrk(4096);
    malloc_header->amount_of_pages += 1;
    last_block->length += 4096;
    must_have_size = smallest_block->length - size - sizeof(area) - 1;
  }
  int remaining_size = must_have_size + 1;
  malloc_header->amount_of_blocks += 1;
  // 현재 블록 헤더 + 사용자 데이터(size) 바로 뒤에 새 free block 헤더 생성
  area *new_block = (area *)((char *)smallest_block + sizeof(area) + size);
  new_block->marker = BLOCK_MARKER;
  new_block->prev = smallest_block;
  new_block->next = smallest_block->next;
  if (new_block->next != NULL) {
    (new_block->next)->prev = new_block;
  }
  smallest_block->next = new_block;
  new_block->length = remaining_size;
  smallest_block->length = size;
  malloc_header->my_simple_lock = false;
  // 사용자에게는 블록 헤더 다음의 실제 데이터 영역 주소만 반환한다.
  return (int *)((char *)smallest_block + sizeof(area));
}

/* 사용자에게 보이는 malloc 역할의 진입 함수 */
int *an_malloc(ssize_t size) {
  // 첫 malloc 호출이면 heap_start를 설정하고 최초 1페이지를 확보한다.
  if (heap_start == NULL) {
    heap_start = (char *)my_sbrk(0);
    if (heap_start == (void *)-1 || my_sbrk(PAGE_SIZE) == (void *)-1) {
      return NULL;
    }
  }
  // 현재 힙의 끝 주소와 전체 사용 길이를 계산한다.
  char *heap_end = my_sbrk(0);
  long int length = heap_end - heap_start;
  // 힙 맨 앞의 매직 값을 확인해서 allocator가 초기화되었는지 검사한다.
  if ((*heap_start) != MAGICAL_BYTES) {
    // 최초 실행: allocator 전체 헤더와 첫 free block을 구성한다.
    *(heap_start) = MAGICAL_BYTES;
    my_stats *malloc_header = (my_stats *)heap_start;
    malloc_header->amount_of_blocks = 1;
    malloc_header->amount_of_pages = 1;
    // my_stats 바로 뒤에 첫 번째 메모리 블록 헤더를 만든다.
    area *first_block = (area *)((char *)heap_start + sizeof(my_stats));
    first_block->marker = BLOCK_MARKER;
    first_block->in_use = false;
    first_block->length = length - sizeof(my_stats) - sizeof(area);
    first_block->next = NULL;
    first_block->prev = NULL;
  }
  // 실제 best-fit 검색/블록 분할 작업 수행
  return add_used_block(size);
}

/* 1바이트 할당과 읽기/쓰기 기본 테스트 */
void test_basic_malloc() {
  char *ptr = (char *)an_malloc(1);
  area *first_block = (area *)((char *)ptr - sizeof(area));
  assert(first_block->marker == BLOCK_MARKER);
  *ptr = 'C';
  assert(*ptr == 'C');
}

/* 현재 페이지보다 큰 5000바이트 요청 테스트 */
void test_bigger_than_available_malloc() {
  uint16_t *ptr = (uint16_t *)an_malloc(5000);
  area *first_block = (area *)((char *)ptr - sizeof(area));
  for (uint16_t i = 0; i <= 2499; i = i + 1) {
    *(ptr + i) = i;
  }
  assert(first_block->marker == BLOCK_MARKER);
  assert(*ptr == 0);
  assert(*(ptr + 2) == 2);
  assert(*(ptr + 2499) == 2499);
  // 아래 바이트 단위 검사는 little-endian 환경에서만 유효
  assert(*((uint8_t *)ptr + 4999) == (2499 >> 8));
  assert(*((uint8_t *)ptr + 4998) == (2499 & 0xFF));
}

/* free 후 블록 병합과 길이 복구 테스트 */
void test_free() {
  uint8_t *first = (uint8_t *)an_malloc(2048);
  area *first_block = (area *)((char *)first - sizeof(area));
  assert(first_block->next != NULL);
  assert(first_block->length == 2048);
  area *second_block = first_block->next;
  assert(second_block->marker == BLOCK_MARKER);
  assert(second_block->in_use == false);
  assert(second_block->next == NULL);
  assert(second_block->length == PAGE_SIZE - sizeof(my_stats) -
                                     (2 * sizeof(area)) - first_block->length);
  an_free(first);
  assert(first_block->marker == BLOCK_MARKER);
  assert(first_block->next == NULL);
  assert(first_block->length == PAGE_SIZE - sizeof(my_stats) - sizeof(area));
}

/* 여러 malloc/free 조합에서 분할/병합/페이지 증감이 맞는지 검사 */
void complex_set_of_malloc_and_free_calls() {
  uint8_t *first =
      (uint8_t *)an_malloc(2048); // will leave another 2048 on the first page
  area *first_block = find_first_block();
  assert(first_block->length == 2048);
  area *second_block = first_block->next;
  assert(second_block->length ==
         PAGE_SIZE - sizeof(my_stats) - 2 * sizeof(area) - first_block->length);
  assert(second_block->next == NULL);
  assert(second_block->prev == first_block);
  uint8_t *second =
      (uint8_t *)an_malloc(10000); // will need around two more pages
  assert(second_block->length == 10000);
  assert(second_block->next != NULL);
  area *third_block = second_block->next;
  assert(third_block->length == 3 * PAGE_SIZE - sizeof(my_stats) -
                                    3 * sizeof(area) - first_block->length -
                                    second_block->length);
  my_stats *malloc_header = get_malloc_header();
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 3);
  an_free(second);
  assert(malloc_header->amount_of_pages == 1);
  assert(malloc_header->amount_of_blocks == 2);
  int heap_size = (int)((char *)my_sbrk(0) - heap_start);
  assert(heap_size == PAGE_SIZE);
  // The second block is whatever is left from the first page
  assert(second_block->in_use == false);
  assert(first_block->length == 2048);
  assert(second_block->length ==
         PAGE_SIZE - sizeof(my_stats) - 2 * sizeof(area) - first_block->length);
  assert(second_block->next == NULL);
  // test block unification, add three blocks, free the left, free the right,
  // and then free the middle
  uint8_t *third = (uint8_t *)an_malloc(1000);
  assert(malloc_header->amount_of_pages == 1);
  assert(malloc_header->amount_of_blocks == 3);
  // A third, empty block has been created
  area *third_block_new = second_block->next;
  assert(third_block_new->marker == BLOCK_MARKER);
  assert(third_block_new->in_use == false);
  // The second block, which before was longer, now is used for the call. The
  // third block is the one that is empty
  assert(second_block->length == 1000);
  assert(third_block_new->length == PAGE_SIZE - sizeof(my_stats) -
                                        3 * sizeof(area) - first_block->length -
                                        second_block->length);
  assert(third_block_new->next == NULL);
  uint8_t *fourth = (uint8_t *)an_malloc(5000);
  // third block has been used for the fourth malloc call
  assert(third_block_new->length == 5000);
  assert(third_block_new->next != NULL);
  assert(third_block_new->in_use == true);
  assert(third_block_new->prev == second_block);
  assert(malloc_header->amount_of_pages ==
         3); // the 5000 needed a second page, and then another page was needed
             // to create a third block
  assert(malloc_header->amount_of_blocks == 4);
  uint8_t *fifth = (uint8_t *)an_malloc(1000);
  // a new block has been created
  area *fourth_block = third_block_new->next;
  assert(fourth_block->marker == BLOCK_MARKER);
  assert(third_block_new->length == 5000);
  assert(fourth_block->length == 1000);
  assert(fourth_block->in_use == true);
  assert(fourth_block->next != NULL);
  area *fifth_block = fourth_block->next;
  assert(fifth_block->marker == BLOCK_MARKER);
  assert(fifth_block->in_use == false);
  assert(fifth_block->next == NULL);
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 5); // fifth malloc made a new block
  uint8_t *sixth = (uint8_t *)an_malloc(
      1000); // just as buffer between the end and the fifth block
  assert(fifth_block->in_use == true);
  assert(fifth_block->length == 1000);
  assert(fifth_block->next != NULL);
  assert(fifth_block->prev == fourth_block);
  area *sixth_block = fifth_block->next;
  assert(sixth_block->marker == BLOCK_MARKER);
  assert(sixth_block->in_use == false);
  assert(sixth_block->next == NULL);
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 6);
  an_free(third);
  assert(second_block->in_use == false);
  assert(second_block->length == 1000); // should be unchanged
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 6); // because we have a free block
  an_free(fifth);
  assert(fourth_block->in_use == false);
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 6);
  an_free(fourth);
  assert(third_block_new->in_use == false);
  assert(malloc_header->amount_of_pages == 3);  // that is normal, as block six is still there
  assert(malloc_header->amount_of_blocks == 4); // three blocks have become one
}

/*
 * 함수 포인터로 테스트 함수를 전달받아 자식 프로세스에서 실행한다.
 * 테스트 중 assert/메모리 오류로 자식이 죽어도 부모가 다음 테스트를 계속할 수 있다.
 */
void call_test(void (*test_func)(), const char *msg) {
  // fork 전에 표준 입출력 버퍼를 비워 중복 출력 방지
  fflush(NULL);
  // 테스트 하나당 자식 프로세스를 하나 생성
  pid_t pid = fork();
  if (pid == 0) {
    // 전달받은 함수 포인터가 가리키는 테스트 실행
    test_func();
    // stdio 버퍼를 다시 flush하지 않고 자식 프로세스 즉시 종료
    _exit(0);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
      printf("%s crashed with signal %d\n", msg, WTERMSIG(status));
    } else {
      printf("%s passed\n", msg);
    }
  }
}

/* 모든 allocator 테스트 실행 */
int main() {
  call_test(test_basic_malloc, "Basic Malloc");
  call_test(test_bigger_than_available_malloc, "Request more memory Malloc");
  call_test(test_free, "Basic Free");
  call_test(complex_set_of_malloc_and_free_calls, "Complex");
  debug_log("DONE");
}