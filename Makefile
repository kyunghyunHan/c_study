CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
CXX := c++
CXXFLAGS := -std=c++14 -Wall -Wextra -Wpedantic
BUILD_DIR ?= build
TARGET = $(BUILD_DIR)/$(patsubst %-run,%,$@)

.DEFAULT_GOAL := test

C_BUILD_TARGETS := \
	test \
	sll dll cll \
	sq cq \
	heap rbt pq sht \
	greed conq prob \
	hw tc ssn day jungol dfs \
	graph topolo mst dijkstra bit driver

CPP_BUILD_TARGETS := sort-cpp sort-owned
BUILD_TARGETS := $(C_BUILD_TARGETS) $(CPP_BUILD_TARGETS)
RUN_TARGETS := $(addsuffix -run,$(BUILD_TARGETS))

.PHONY: $(BUILD_TARGETS) $(RUN_TARGETS) clean help

# 기본 테스트
test: SOURCES := design_patterns/sort_strategy/c/main.c

# 연결 리스트
sll: SOURCES := fundamentals/cp/02_SLL_main.c fundamentals/cp/02_SLL.c
dll: SOURCES := fundamentals/cp/02_dll_main.c fundamentals/cp/02_dll.c
cll: SOURCES := fundamentals/cp/02_cll_main.c fundamentals/cp/02_cll.c

# 큐
sq: SOURCES := fundamentals/cp/03_queue_main.c fundamentals/cp/03_queue.c
cq: SOURCES := fundamentals/cp/03_cq_main.c fundamentals/cp/03_cq.c

# 자료구조
heap: SOURCES := algorithms/data_structures/heap.c algorithms/data_structures/test_heap.c
rbt: SOURCES := algorithms/data_structures/rbt.c algorithms/data_structures/test_rbt.c
pq: SOURCES := algorithms/data_structures/priority_queue.c algorithms/data_structures/test_priority_queue.c
sht: SOURCES := algorithms/data_structures/simple_hash_table.c algorithms/data_structures/test_simple_hash_table.c

# 알고리즘 연습
greed: SOURCES := algorithms/greedy/exam01.c
conq: SOURCES := algorithms/divide_and_conquer/exam01.c
prob: SOURCES := exercises/problem/a26.c
ssn: SOURCES := algorithms/search/sequential_search.c algorithms/data_structures/linked_list.c
dfs: SOURCES := algorithms/dfs/exam01.c

# 과제 및 문제 풀이
hw: SOURCES := exercises/homework/hw9.c
tc: SOURCES := exercises/testcase/test05.c
day: SOURCES := fundamentals/cp/05_st_main.c
jungol: SOURCES := exercises/jungol/p1661.c

# 그래프
graph: SOURCES := algorithms/graphs/test_graph.c algorithms/graphs/graph.c
topolo: SOURCES := \
	algorithms/graphs/test_topological_sort.c \
	algorithms/graphs/topological_sort.c \
	algorithms/graphs/linked_list.c \
	algorithms/graphs/graph.c

mst: SOURCES := \
	algorithms/graphs/minimum_spanning_tree/test_mst.c \
	algorithms/graphs/minimum_spanning_tree/mst.c \
	algorithms/graphs/graph.c

dijkstra: SOURCES := \
	algorithms/graphs/shortest_path/test_dijkstra.c \
	algorithms/graphs/shortest_path/dijkstra.c \
	algorithms/graphs/graph.c

# 비트 연산과 가상 장치 드라이버

bit: SOURCES := fundamentals/bit/exam02.c
# 공통 빌드 및 실행 규칙
driver: SOURCES := systems/device_driver/device_driver.c

# C++ 정렬 전략 예제
sort-cpp: SOURCES := $(wildcard design_patterns/sort_strategy/cpp/*.cpp)
sort-owned: SOURCES := design_patterns/sort_strategy/cpp_owned/main.cpp

$(C_BUILD_TARGETS):
	mkdir -p $(dir $(TARGET))
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

$(CPP_BUILD_TARGETS):
	mkdir -p $(dir $(TARGET))
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

$(RUN_TARGETS): %-run: %
	./$(TARGET)

clean:
	$(RM) $(addprefix $(BUILD_DIR)/,$(BUILD_TARGETS))

help:
	@echo "빌드: make <이름>"
	@echo "실행: make <이름>-run"
	@echo "이름: $(BUILD_TARGETS)"
	@echo "출력: $(BUILD_DIR)/<이름>"
	@echo "정리: make clean"
