CC=gcc
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -g
CFLAGS=-Wall -Wextra -Werror -g
AR=ar
RM=rm -f
BIN=$(patsubst %.c, %, $(wildcard **/*.c))
BINXX=$(patsubst %.cpp, %, $(wildcard **/*.cpp))

.PHONY: clean all

all: $(BIN) $(BINXX)

$(BIN): %: %.o
	$(CC) -lgnl -lm $^ -o $@
$(BINXX): %: %.o
	$(CXX) -lgnl $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	$(RM) **/*.o $(BIN)
