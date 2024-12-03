#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_to_int(char** n) {
    int r = 0;
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r;
}

int do_mul(char** line) {
    while (**line != '\n') {
        while (strncmp(*line, "mul(", 4)) {
            (*line)++;
            if (**line == '\n') {
                return 0;
            }
        }
        (*line) += 4;
        char* orig = *line;
        int n1 = string_to_int(line);
        if (**line == ',' && *line != orig) {
            (*line)++;

            orig = *line;
            int n2 = string_to_int(line);
            if (**line == ')' && *line != orig) {
                (*line)++;
                return n1 * n2;
            }
        }
        (*line)++;
    }
    return 0;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int sum = 0;
    char* line;
    while ((line = get_next_line(input))) {
        char* saved = line;
        while (*line != '\n') {
            sum += do_mul(&line);
        }
        free(saved);
    }
    printf("Sum of all muls: %d\n", sum);
}
