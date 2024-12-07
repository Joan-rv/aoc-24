#include <fcntl.h>
#include <libgnl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

ull string_to_ull(char** n) {
    ull r = 0;
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r;
}

ull pow_i(ull b, ull e) {
    ull r = 1;
    for (ull i = 0; i < e; i++) {
        r *= b;
    }
    return r;
}

ull concat_i(ull a, ull b) {
    ull p = 1;
    while (p <= b) {
        p *= 10;
    }
    return a * p + b;
}

ull eval_eq(ull* n, size_t n_s, ull op) {
    ull r = n[0];
    for (size_t i = 1; i < n_s; i++) {
        ull d = op / pow_i(3, i - 1);
        if (d % 3 == 0) {
            r *= n[i];
        } else if (d % 3 == 1) {
            r += n[i];
        } else {
            r = concat_i(r, n[i]);
        }
    }
    return r;
}

bool can_be_solved(ull t, ull* n, size_t n_s) {
    for (ull op = 0; op < pow_i(3, n_s - 1); op++) {
        if (eval_eq(n, n_s, op) == t) {
            return true;
        }
    }
    return false;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    unsigned long long sum = 0;
    ull* numbers = NULL;
    size_t numbers_size = 0;
    while ((line = get_next_line(input))) {
        char* saved = line;
        ull target = string_to_ull(&line);
        line++;
        while (*(line++) == ' ') {
            ull n = string_to_ull(&line);
            numbers_size++;
            numbers = realloc(numbers, numbers_size * sizeof(ull));
            numbers[numbers_size - 1] = n;
        }
        if (can_be_solved(target, numbers, numbers_size)) {
            if (sum + target < sum) {
                fprintf(stderr, "OVERFLOW!!!\n");
                return -1;
            }
            sum += target;
        }
        numbers_size = 0;
        free(numbers);
        numbers = NULL;
        free(saved);
    }
    printf("Total calibration result: %llu\n", sum);
}
