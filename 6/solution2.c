#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Direction {
    North = 1 << 0,
    East = 1 << 1,
    South = 1 << 2,
    West = 1 << 3
} Direction;

bool will_exit(char** orig_lines, int n, int m) {
    char** lines = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        lines[i] = malloc(m * sizeof(char));
        memcpy(lines[i], orig_lines[i], m);
    }
    int i = 0;
    int j = 0;
    bool found = false;
    while (i < n && !found) {
        j = 0;
        while (j < m && !found) {
            if (lines[i][j] == '^') {
                found = true;
            }
            j++;
        }
        i++;
    }
    i--;
    j--;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] == '.' || lines[i][j] == '^') {
                lines[i][j] = 0;
            }
        }
    }

    Direction direction = North;
    while (i >= 0 && j >= 0 && i < n && j < m) {
        int new_i = i;
        int new_j = j;
        if (direction == North) {
            new_i--;
        } else if (direction == South) {
            new_i++;
        } else if (direction == East) {
            new_j++;
        } else if (direction == West) {
            new_j--;
        }
        if (new_i >= 0 && new_j >= 0 && new_i < n && new_j < m) {
            if (lines[new_i][new_j] == '#') {
                if (direction == West) {
                    direction = North;
                } else {
                    direction <<= 1;
                }
            } else {
                if (lines[new_i][new_j] & direction) {
                    for (int i = 0; i < n; i++) {
                        free(lines[i]);
                    }
                    return false;
                }
                i = new_i;
                j = new_j;
                lines[i][j] |= direction;
            }
        } else {
            i = new_i;
            j = new_j;
        }
    }
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    return true;
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
    // don't include new line
    int m = strlen(lines[0]) - 1;

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] == '.') {
                lines[i][j] = '#';
                if (!will_exit(lines, n, m)) {
                    count++;
                }
                lines[i][j] = '.';
            }
        }
    }
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Count of distinct positions: %d\n", count);
}
