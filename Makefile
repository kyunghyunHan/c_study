CC = gcc
CFLAGS = -Wall -Wextra

TARGET = test
SRC = ./fundamentals/cp/02_SLL_main.c ./fundamentals/cp/02_SLL.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)