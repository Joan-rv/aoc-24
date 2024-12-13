#include <fcntl.h>
#include <libgnl.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int_fast64_t i64;

i64 string_to_u64(char** n) {
    i64 r = 0;
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r;
}

i64 find_token_min(i64 a_x, i64 a_y, i64 b_x, i64 b_y, i64 p_x, i64 p_y) {
    double n_b = (double)(p_x * a_y - p_y * a_x) / (a_y * b_x - a_x * b_y);
    i64 n_bi = n_b + 0.5f;
    double n_a = (double)(p_x - b_x * n_b) / a_x;
    i64 n_ai = n_a + 0.5f;
    if (fabs(n_bi - n_b) > 0.001f || fabs(n_ai - n_a) > 0.001f) {
        return 0;
    }
    return 3 * n_ai + n_bi;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    i64 sum = 0;
    while ((line = get_next_line(input))) {
        char* saved = line;
        line += 12;
        i64 a_x = string_to_u64(&line);
        line += 4;
        i64 a_y = string_to_u64(&line);
        free(saved);
        line = get_next_line(input);
        saved = line;
        line += 12;
        i64 b_x = string_to_u64(&line);
        line += 4;
        i64 b_y = string_to_u64(&line);
        free(saved);
        line = get_next_line(input);
        saved = line;
        line += 9;
        i64 p_x = string_to_u64(&line);
        p_x += 10000000000000;
        line += 4;
        i64 p_y = string_to_u64(&line);
        p_y += 10000000000000;
        free(saved);
        free(get_next_line(input));
        sum += find_token_min(a_x, a_y, b_x, b_y, p_x, p_y);
    }
    printf("Fewest tokens: %ld\n", sum);
}
