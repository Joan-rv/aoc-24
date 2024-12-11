CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
AR=ar
RM=rm -f
BIN=$(patsubst %.c, %, $(wildcard **/*.c))

.PHONY: clean all

all: $(BIN)

$(BIN): %: %.o
	$(CC) -lgnl -lm $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) **/*.o $(BIN)
