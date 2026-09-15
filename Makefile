CC = gcc
CFLAGS = -Wall -Wextra

sll:
	$(CC) $(CFLAGS) \
	./fundamentals/cp/02_SLL_main.c \
	./fundamentals/cp/02_SLL.c \
	-o test

sll-run: sll
	./test

dll:
	$(CC) $(CFLAGS) \
	./fundamentals/cp/02_dll_main.c \
	./fundamentals/cp/02_dll.c \
	-o test

dll-run: dll
	./test


greed:
	$(CC) $(CFLAGS) \
	./algorithms/greed/exam01.c \
	-o test

greed-run: greed
	./test


conq:
	$(CC) $(CFLAGS) \
	./algorithms/Conquer/exam01.c \
	-o test

conq-run: conq
	./test

prob:
	$(CC) $(CFLAGS) \
	./fundamentals/problem/a04.c \
	-o test

prob-run: prob
	./test

heap:
	$(CC) $(CFLAGS) \
	./algorithms/struct/heap.c \
	./algorithms/struct/test_heap.c \
	-o test

heap-run: heap
	./test

clean:
	rm -f test