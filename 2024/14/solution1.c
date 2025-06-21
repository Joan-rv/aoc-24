#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int string_to_int(char** n) {
    int r = 0;
    int sign = 1;
    if (**n == '-') {
        sign = -1;
        (*n)++;
    }
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r * sign;
}

int mod(int a, int m) {
    int r = a % m;
    if (r < 0) {
        r += m;
    }
    return r;
}

int main() {
    const int n = 103;
    const int m = 101;
    // const int n = 7;
    // const int m = 11;
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    int** robots = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        robots[i] = calloc(m, sizeof(int));
    }
    while ((line = get_next_line(input))) {
        line += 2;
        int x0 = string_to_int(&line);
        line++;
        int y0 = string_to_int(&line);
        line += 3;
        int vx = string_to_int(&line);
        line++;
        int vy = string_to_int(&line);
        int xf = mod(x0 + vx * 100, m);
        int yf = mod(y0 + vy * 100, n);
        robots[yf][xf]++;
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", robots[i][j]);
        }
        puts("");
    }
    */

    int safety_factor = 1;
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m / 2; j++) {
            sum1 += robots[i][j];
        }
        for (int j = (m + 1) / 2; j < m; j++) {
            sum2 += robots[i][j];
        }
    }
    safety_factor *= sum1 * sum2;
    sum1 = 0;
    sum2 = 0;
    for (int i = (n + 1) / 2; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
            sum1 += robots[i][j];
        }
        for (int j = (m + 1) / 2; j < m; j++) {
            sum2 += robots[i][j];
        }
    }
    safety_factor *= sum1 * sum2;
    printf("Safety factor: %d\n", safety_factor);
}
