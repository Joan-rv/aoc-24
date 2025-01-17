#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_antinodes(int i1, int j1, int i2, int j2, int n, int m,
                   bool** antinodes) {
    int di = i2 - i1;
    int dj = j2 - j1;
    int i = i1;
    int j = j1;
    while (0 <= i && i < n && 0 <= j && j < m) {
        antinodes[i][j] = true;
        i += di;
        j += dj;
    }
    i = i1;
    j = j1;
    while (0 <= i && i < n && 0 <= j && j < m) {
        antinodes[i][j] = true;
        i -= di;
        j -= dj;
    }
}

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
    int m = strlen(lines[0]) - 1;
    bool** antinodes = calloc(n, sizeof(bool*));
    for (int i = 0; i < n; i++) {
        antinodes[i] = calloc(m, sizeof(bool));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] != '.') {
                for (int j2 = j + 1; j2 < m; j2++) {
                    if (lines[i][j2] == lines[i][j]) {
                        add_antinodes(i, j, i, j2, n, m, antinodes);
                    }
                }
                for (int i2 = i + 1; i2 < n; i2++) {
                    for (int j2 = 0; j2 < n; j2++) {
                        if (lines[i][j] == lines[i2][j2]) {
                            add_antinodes(i, j, i2, j2, n, m, antinodes);
                        }
                    }
                }
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (antinodes[i][j]) {
                count++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Unique locations with antinodes: %d\n", count);
}
