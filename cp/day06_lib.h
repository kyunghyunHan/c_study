/*
int a ; //잘못댄 내용
- (1)초기화 없으면 뱐수 중복이 있는 것을 발변하기 어려움
- (2)변수 선언은 c 파일에 하럿
- (3)
 */

#ifndef DAY06_LIB_H
#define DAY06_LIB_H
#include <stddef.h>
extern int m;
void swap(int *ap, int *bp);

void scanf_ary(int *ary, size_t len);
void print_ary(int *ary, size_t len);
int findmax_ary(int *ary, size_t len);
int findmin_ary(int *ary, size_t len);
size_t findmax_idx(int *ary, size_t len);
size_t findmin_idx(int *ary, size_t len);
int sum_ary(int *ary, size_t len);
int avg_ary(int *ary, size_t len);
void find_min_max(int * ary , size_t n);
double var_ary(int *ary, size_t len);
void simple_sort(int *ary, size_t n );
#endif
