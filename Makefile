CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
AR=ar
RM=rm -f
BIN=1/solution1 1/solution2 2/solution1 2/solution2 3/solution1 3/solution2 4/solution1 4/solution2 5/solution1 5/solution2 6/solution1 6/solution2 7/solution1 7/solution2 8/solution1 8/solution2

.PHONY: clean all

all: $(BIN)

$(BIN): %: %.o
	$(CC) -lgnl $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) **/*.o $(BIN)
