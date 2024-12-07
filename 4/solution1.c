#include <fcntl.h>
#include <libgnl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) { return (a < b ? b : a); }

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int n = 0;
    char** lines = NULL;
    char* line;
    while ((line = get_next_line(input))) {
        n++;
        lines = realloc(lines, n * sizeof(char*));
        lines[n - 1] = line;
    }

    int m = strlen(lines[0]);

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 3; j++) {
            if (strncmp(lines[i] + j, "XMAS", 4) == 0) {
                count++;
            }
            if (strncmp(lines[i] + j, "SAMX", 4) == 0) {
                count++;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n - 3; i++) {
            if (lines[i][j] == 'X' && lines[i + 1][j] == 'M' &&
                lines[i + 2][j] == 'A' && lines[i + 3][j] == 'S') {
                count++;
            }
            if (lines[i][j] == 'S' && lines[i + 1][j] == 'A' &&
                lines[i + 2][j] == 'M' && lines[i + 3][j] == 'X') {
                count++;
            }
        }
    }

    for (int i = -n + 1; i < n; i++) {
        for (int o = max(-i, 0); o + i < n - 3; o++) {
            if (o < m - 3) {
                if (lines[i + o][o] == 'X' && lines[i + o + 1][o + 1] == 'M' &&
                    lines[i + o + 2][o + 2] == 'A' &&
                    lines[i + o + 3][o + 3] == 'S') {
                    count++;
                }
                if (lines[i + o][o] == 'S' && lines[i + o + 1][o + 1] == 'A' &&
                    lines[i + o + 2][o + 2] == 'M' &&
                    lines[i + o + 3][o + 3] == 'X') {
                    count++;
                }
            }
            if (m - o - 4 >= 0) {
                if (lines[i + o][m - o - 1] == 'X' &&
                    lines[i + o + 1][m - o - 2] == 'M' &&
                    lines[i + o + 2][m - o - 3] == 'A' &&
                    lines[i + o + 3][m - o - 4] == 'S') {
                    count++;
                }
                if (lines[i + o][m - o - 1] == 'S' &&
                    lines[i + o + 1][m - o - 2] == 'A' &&
                    lines[i + o + 2][m - o - 3] == 'M' &&
                    lines[i + o + 3][m - o - 4] == 'X') {
                    count++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Count of all occurrences: %d\n", count);
}
