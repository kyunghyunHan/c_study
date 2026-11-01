#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *arr, int size)
{
    for (int end = size - 1; end > 0; end--) {
        int swapped = 0;

        for (int i = 0; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}
void quick_sort(int *arr, int size)
{
    if (size < 2) {
        return;
    }

    int pivot = arr[size / 2];
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        while (arr[left] < pivot) {
            left++;
        }
        while (arr[right] > pivot) {
            right--;
        }
        if (left <= right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }

    quick_sort(arr, right + 1);
    quick_sort(arr + left, size - left);
}

typedef struct SortPolicy SortPolicy;

/* 가상 메서드: self는 C++의 this에 해당합니다. */
typedef struct SortPolicyVTable {
    void (*sort)(SortPolicy *self, int *arr, int size);
    void (*destroy)(SortPolicy *self);
} SortPolicyVTable;

struct SortPolicy {
    const SortPolicyVTable *vtable;
};

/* 기반 객체를 첫 멤버로 포함하여 상속 관계를 표현합니다. */
typedef struct BubbleSort {
    SortPolicy base;
} BubbleSort;

typedef struct QuickSort {
    SortPolicy base;
} QuickSort;

static void BubbleSort_sort(SortPolicy *self, int *arr, int size)
{
    (void)self;
    bubble_sort(arr, size);
}

static void BubbleSort_destroy(SortPolicy *self)
{
    free((BubbleSort *)self);
}

static void QuickSort_sort(SortPolicy *self, int *arr, int size)
{
    (void)self;
    quick_sort(arr, size);
}

static void QuickSort_destroy(SortPolicy *self)
{
    free((QuickSort *)self);
}

static const SortPolicyVTable bubble_vtable = {
    BubbleSort_sort, BubbleSort_destroy
};

static const SortPolicyVTable quick_vtable = {
    QuickSort_sort, QuickSort_destroy
};

static SortPolicy *BubbleSort_new(void)
{
    BubbleSort *self = malloc(sizeof *self);
    if (self == NULL) {
        return NULL;
    }
    self->base.vtable = &bubble_vtable;
    return &self->base;
}

static SortPolicy *QuickSort_new(void)
{
    QuickSort *self = malloc(sizeof *self);
    if (self == NULL) {
        return NULL;
    }
    self->base.vtable = &quick_vtable;
    return &self->base;
}

enum SortType
{
    QUICK_SORT = 1,
    BUBBLE_SORT = 2
};

typedef struct SortFactory SortFactory;

struct SortFactory {
    SortPolicy *(*getSortPolicy)(SortFactory *self, int type);
};

static SortPolicy *SortFactory_getSortPolicy(SortFactory *self, int type)
{
    (void)self;
    switch (type) {
    case QUICK_SORT:
        return QuickSort_new();
    case BUBBLE_SORT:
        return BubbleSort_new();
    default:
        return NULL;
    }
}

static void SortFactory_init(SortFactory *self)
{
    self->getSortPolicy = SortFactory_getSortPolicy;
}

typedef struct User User;

struct User {
    int *numbers;
    int size;
    SortFactory factory;
    int (*sort_number)(User *self, int type);
};

static int User_sort_number(User *self, int type)
{
    SortPolicy *policy = self->factory.getSortPolicy(&self->factory, type);
    if (policy == NULL) {
        return 0;
    }

    /* 실제 객체의 타입에 따라 구현이 선택됩니다(다형성). */
    policy->vtable->sort(policy, self->numbers, self->size);
    policy->vtable->destroy(policy);
    return 1;
}

static void User_init(User *self, int *numbers, int size)
{
    self->numbers = numbers;
    self->size = size;
    SortFactory_init(&self->factory);
    self->sort_number = User_sort_number;
}

int main(void)
{
    int numbers[] = {5, 3, 8, 1, 2, 7, 4, 6};
    User user;
    User_init(&user, numbers, (int)(sizeof numbers / sizeof numbers[0]));

    if (!user.sort_number(&user, QUICK_SORT)) {
        fprintf(stderr, "Could not create sort policy\n");
        return 1;
    }

    for (int i = 0; i < user.size; i++) {
        printf("%d ", numbers[i]);
    }
    putchar('\n');
    return 0;
}

