#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_next_line(int fd);

typedef unsigned long long ull;
typedef enum {
    Left = 1 << 1,
    Top = 1 << 2,
    Right = 1 << 3,
    Bottom = 1 << 4
} Side;
void add_side(int* side, Side dir, Side** sides, int i, int j) {
    (*side)++;
    sides[i][j] |= dir;
}

void find_fence(char** lines, int n, int m, int i, int j, int* side, int* area,
                Side** sides) {
    (*area)++;
    char c = lines[i][j];
    char c_low = lines[i][j] - 'A' + 'a';
    lines[i][j] = c_low;
    if (0 <= i - 1) {
        if (lines[i - 1][j] == c) {
            find_fence(lines, n, m, i - 1, j, side, area, sides);
        } else if (lines[i - 1][j] != c_low) {
            add_side(side, Top, sides, i - 1, j);
        }
    } else {
        add_side(side, Top, sides, i - 1, j);
    }
    if (0 <= j - 1) {
        if (lines[i][j - 1] == c) {
            find_fence(lines, n, m, i, j - 1, side, area, sides);
        } else if (lines[i][j - 1] != c_low) {
            add_side(side, Left, sides, i, j - 1);
        }
    } else {
        add_side(side, Left, sides, i, j - 1);
    }
    if (i + 1 < n) {
        if (lines[i + 1][j] == c) {
            find_fence(lines, n, m, i + 1, j, side, area, sides);
        } else if (lines[i + 1][j] != c_low) {
            add_side(side, Bottom, sides, i + 1, j);
        }
    } else {
        add_side(side, Bottom, sides, i + 1, j);
    }
    if (j + 1 < m) {
        if (lines[i][j + 1] == c) {
            find_fence(lines, n, m, i, j + 1, side, area, sides);
        } else if (lines[i][j + 1] != c_low) {
            add_side(side, Right, sides, i, j + 1);
        }
    } else {
        add_side(side, Right, sides, i, j + 1);
    }
}

int count_sides(Side** sides, int n, int m) {
    int side = 0;
    for (int i = -1; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            if (sides[i][j] & Top && !(sides[i][j - 1] & Top)) {
                side++;
            }
            if (sides[i][j] & Bottom && !(sides[i][j - 1] & Bottom)) {
                side++;
            }
        }
    }
    for (int j = -1; j < m + 1; j++) {
        for (int i = 0; i < n + 1; i++) {
            if (sides[i][j] & Left && !(sides[i - 1][j] & Left)) {
                side++;
            }
            if (sides[i][j] & Right && !(sides[i - 1][j] & Right)) {
                side++;
            }
        }
    }
    return side;
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
        lines = (char**)realloc(lines, n * sizeof(char*));
        lines[n - 1] = line;
    }
    int m = strlen(lines[0]) - 1;

    ull price = 0;
    int* area = (int*)malloc(sizeof(int));
    int* side = (int*)malloc(sizeof(int));
    Side** sides = malloc((n + 2) * sizeof(Side*));
    for (int i = 0; i < n + 2; i++) {
        sides[i] = malloc((m + 2) * sizeof(Side));
        sides[i]++;
    }
    sides++;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ('A' <= lines[i][j] && lines[i][j] <= 'Z') {
                *area = 0;
                *side = 0;
                for (int i = -1; i < n + 1; i++) {
                    memset(sides[i] - 1, 0, (m + 2) * sizeof(Side));
                }
                find_fence(lines, n, m, i, j, side, area, sides);
                int siden = count_sides(sides, n, m);
                price += siden * (*area);
            }
        }
    }
    free(area);
    free(side);

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Total price: %llu\n", price);
}
