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

bool is_valid_update(int* r1, int* r2, size_t r_s, int* u, size_t u_s) {
    bool* seen = malloc(r_s * sizeof(bool));
    memset(seen, 0, r_s * sizeof(bool));
    for (size_t i = 0; i < u_s; i++) {
        for (size_t j = 0; j < r_s; j++) {
            if (r2[j] == u[i]) {
                seen[j] = true;
            }
        }

        for (size_t j = 0; j < r_s; j++) {
            if (r1[j] == u[i] && seen[j]) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int* rule1 = NULL;
    int* rule2 = NULL;
    size_t rule_size = 0;
    char* line;
    while ((line = get_next_line(input))) {
        if (*line == '\n') {
            break;
        }
        char* saved = line;
        int n = string_to_int(&line);
        rule_size++;
        rule1 = realloc(rule1, rule_size * sizeof(int));
        rule1[rule_size - 1] = n;
        line++;
        n = string_to_int(&line);
        rule2 = realloc(rule2, rule_size * sizeof(int));
        rule2[rule_size - 1] = n;
        free(saved);
    }
    free(line);

    int sum = 0;
    int* update = malloc(sizeof(int));
    size_t update_size = 1;
    while ((line = get_next_line(input))) {
        char* saved = line;
        int n = string_to_int(&line);
        update[0] = n;
        while (*(line++) == ',') {
            int n = string_to_int(&line);
            update_size++;
            update = realloc(update, update_size * sizeof(int));
            update[update_size - 1] = n;
        }
        if (is_valid_update(rule1, rule2, rule_size, update, update_size)) {
            sum += update[update_size / 2];
        }
        update_size = 1;
        update = realloc(update, update_size * sizeof(int));
        free(saved);
    }
    printf("Sum of all middle pages: %d\n", sum);
}
