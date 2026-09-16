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
cll:
	$(CC) $(CFLAGS) \
	./fundamentals/cp/02_cll_main.c \
	./fundamentals/cp/02_cll.c \
	-o test

cll-run: cll
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
	./fundamentals/problem/a05.c \
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
	
rbt:
	$(CC) $(CFLAGS) \
	./algorithms/struct/rbt.c \
	./algorithms/struct/test_rbt.c \
	-o test

rbt-run: rbt
	./test

pq:
	$(CC) $(CFLAGS) \
	./algorithms/struct/priority_queue.c \
	./algorithms/struct/test_priority_queue.c \
	-o test

pq-run: rbt
	./test

sht:
	$(CC) $(CFLAGS) \
	./algorithms/struct/simple_hash_table.c \
	./algorithms/struct/test_simple_hash_table.c \
	-o test

sht-run: sht
	./test

.PHONY: test test-run

test:
	$(CC) $(CFLAGS) \
	./test.c \
	-o test

test-run: test
	./test


sq:
	$(CC) $(CFLAGS) \
	./acadamy/cp/03_queue_main.c \
	./acadamy/cp/03_queue.c \
	-o test

sq-run: sq
	./test

cq:
	$(CC) $(CFLAGS) \
	./acadamy/cp/03_cq_main.c \
	./acadamy/cp/03_cq.c \
	-o test

cq-run: cq
	./test

hw:
	$(CC) $(CFLAGS) \
	./homework/hw2.c \
	-o test

hw-run: hw
	./test
clean:
	rm -f test
