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
	./fundamentals/cp/03_DLL_main.c \
	./fundamentals/cp/03_DLL.c \
	-o test

dll-run: dll
	./test


greed:
	$(CC) $(CFLAGS) \
	./algorithms/greed/exam01.c \
	-o test

greed-run: greed
	./test

clean:
	rm -f test