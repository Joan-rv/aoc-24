#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int string_to_int(char** n) {
    int r = 0;
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r;
}

bool is_safe(char* line) {
    int prev = string_to_int(&line);
    bool first = true;
    bool increasing;
    while (*line != '\n') {
        while (*line == ' ') {
            line++;
        }
        int n = string_to_int(&line);
        if (first) {
            if (prev < n) {
                increasing = true;
            } else {
                increasing = false;
            }
            first = false;
        }
        if (increasing) {
            if (n < prev || n - prev < 1 || n - prev > 3) {
                return false;
            }
        } else {
            if (n > prev || prev - n < 1 || prev - n > 3) {
                return false;
            }
        }
        prev = n;
    }
    return true;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int n = 0;
    char* line;
    while ((line = get_next_line(input))) {
        if (is_safe(line)) {
            n++;
        }
        free(line);
    }
    printf("%d reports are safe\n", n);
}
