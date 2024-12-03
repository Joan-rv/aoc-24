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

int do_mul(char** line, bool* enabled) {
    while (**line != '\n') {
        if (strncmp(*line, "do()", 4) == 0) {
            *enabled = true;
            *line += 4;
        } else if (strncmp(*line, "don't()", 7) == 0) {
            *enabled = false;
            *line += 7;
        } else if (*enabled && strncmp(*line, "mul(", 4) == 0) {
            *line += 4;
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
        } else {
            (*line)++;
        }
    }
    return 0;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int sum = 0;
    bool enabled = true;
    char* line;
    while ((line = get_next_line(input))) {
        char* saved = line;
        while (*line != '\n') {
            sum += do_mul(&line, &enabled);
        }
        free(saved);
    }
    printf("Sum of all muls: %d\n", sum);
}
