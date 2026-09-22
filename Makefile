CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
TARGET := test

.DEFAULT_GOAL := test

BUILD_TARGETS := \
	test \
	sll dll cll \
	sq cq \
	heap rbt pq sht \
	greed conq prob \
	hw tc ssn day jungol dfs \
	graph topolo mst dijkstra

RUN_TARGETS := $(addsuffix -run,$(BUILD_TARGETS))

.PHONY: $(BUILD_TARGETS) $(RUN_TARGETS) clean help

# 기본 테스트
test: SOURCES := test.c

# 연결 리스트
sll: SOURCES := acadamy/cp/02_SLL_main.c acadamy/cp/02_SLL.c
dll: SOURCES := acadamy/cp/02_dll_main.c acadamy/cp/02_dll.c
cll: SOURCES := acadamy/cp/02_cll_main.c acadamy/cp/02_cll.c

# 큐
sq: SOURCES := acadamy/cp/03_queue_main.c acadamy/cp/03_queue.c
cq: SOURCES := acadamy/cp/03_cq_main.c acadamy/cp/03_cq.c

# 자료구조
heap: SOURCES := algorithms/struct/heap.c algorithms/struct/test_heap.c
rbt: SOURCES := algorithms/struct/rbt.c algorithms/struct/test_rbt.c
pq: SOURCES := algorithms/struct/priority_queue.c algorithms/struct/test_priority_queue.c
sht: SOURCES := algorithms/struct/simple_hash_table.c algorithms/struct/test_simple_hash_table.c

# 알고리즘 연습
greed: SOURCES := algorithms/greed/exam01.c
conq: SOURCES := algorithms/Conquer/exam01.c
prob: SOURCES := acadamy/problem/a05.c
ssn: SOURCES := algorithms/search/sequential_search.c algorithms/struct/linked_list.c
dfs: SOURCES := algorithms/dfs/exam01.c

# 과제 및 문제 풀이
hw: SOURCES := homework/hw8.c
tc: SOURCES := testcase/test05.c
day: SOURCES := acadamy/cp/05_st_main.c
jungol: SOURCES := acadamy/jungol/p1078.c

# 그래프
graph: SOURCES := algorithms/Graph/test_graph.c algorithms/Graph/graph.c
topolo: SOURCES := \
	algorithms/Graph/test_topological_sort.c \
	algorithms/Graph/topological_sort.c \
	algorithms/Graph/linked_list.c \
	algorithms/Graph/graph.c

mst: SOURCES := \
	algorithms/Graph/minimum_spanning_tree/test_mst.c \
	algorithms/Graph/minimum_spanning_tree/mst.c \
	algorithms/Graph/graph.c

dijkstra: SOURCES := \
	algorithms/Graph/shortest_path/test_dijkstra.c \
	algorithms/Graph/shortest_path/dijkstra.c \
	algorithms/Graph/graph.c

# 공통 빌드 및 실행 규칙
$(BUILD_TARGETS):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

$(RUN_TARGETS): %-run: %
	./$(TARGET)

clean:
	rm -f $(TARGET)

help:
	@echo "빌드: make <이름>"
	@echo "실행: make <이름>-run"
	@echo "이름: $(BUILD_TARGETS)"
	@echo "정리: make clean"
