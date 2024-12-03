CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
AR=ar
RM=rm -f
BIN=1/solution1 1/solution2 2/solution1 2/solution2

.PHONY: clean all $(addprefix all.,$(SUBDIRS))

all: $(BIN)

$(BIN): %: %.o
	$(CC) -lgnl $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) **/*.o $(BIN)
