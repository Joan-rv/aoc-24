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

int find_token_min(int a_x, int a_y, int b_x, int b_y, int p_x, int p_y) {
    int tok_a_min = 3 * 100;
    int tok_b_min = 100;
    bool found = false;
    for (int n_a = 0; n_a < 100; n_a++) {
        for (int n_b = 0; n_b < 100; n_b++) {
            if (a_x * n_a + b_x * n_b == p_x && a_y * n_a + b_y * n_b == p_y) {
                found = true;
                if (n_a * 3 + n_b < tok_a_min + tok_b_min) {
                    tok_a_min = n_a * 3;
                    tok_b_min = n_b;
                }
            }
        }
    }
    if (!found) {
        return 0;
    } else {
        return tok_a_min + tok_b_min;
    }
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    int sum = 0;
    while ((line = get_next_line(input))) {
        char* saved = line;
        line += 12;
        int a_x = string_to_int(&line);
        line += 4;
        int a_y = string_to_int(&line);
        free(saved);
        line = get_next_line(input);
        saved = line;
        line += 12;
        int b_x = string_to_int(&line);
        line += 4;
        int b_y = string_to_int(&line);
        free(saved);
        line = get_next_line(input);
        saved = line;
        line += 9;
        int p_x = string_to_int(&line);
        line += 4;
        int p_y = string_to_int(&line);
        free(saved);
        free(get_next_line(input));
        sum += find_token_min(a_x, a_y, b_x, b_y, p_x, p_y);
    }
    printf("Fewest tokens: %d\n", sum);
}
