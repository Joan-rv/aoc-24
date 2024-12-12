#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

void add_perimeter(int* perimeter, int i, int j, bool** counted) {
    // if (!counted[i][j]) {
    (*perimeter)++;
    counted[i][j] = true;
    //}
}

void find_fence(char** lines, int n, int m, int i, int j, int* perimeter,
                int* area) {
    (*area)++;
    char c = lines[i][j];
    char c_low = lines[i][j] - 'A' + 'a';
    lines[i][j] = c_low;
    if (0 <= i - 1) {
        if (lines[i - 1][j] == c) {
            find_fence(lines, n, m, i - 1, j, perimeter, area);
        } else if (lines[i - 1][j] != c_low) {
            (*perimeter)++;
        }
    } else {
        (*perimeter)++;
    }
    if (0 <= j - 1) {
        if (lines[i][j - 1] == c) {
            find_fence(lines, n, m, i, j - 1, perimeter, area);
        } else if (lines[i][j - 1] != c_low) {
            (*perimeter)++;
        }
    } else {
        (*perimeter)++;
    }
    if (i + 1 < n) {
        if (lines[i + 1][j] == c) {
            find_fence(lines, n, m, i + 1, j, perimeter, area);
        } else if (lines[i + 1][j] != c_low) {
            (*perimeter)++;
        }
    } else {
        (*perimeter)++;
    }
    if (j + 1 < m) {
        if (lines[i][j + 1] == c) {
            find_fence(lines, n, m, i, j + 1, perimeter, area);
        } else if (lines[i][j + 1] != c_low) {
            (*perimeter)++;
        }
    } else {
        (*perimeter)++;
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

    ull price = 0;
    int* area = malloc(sizeof(int));
    int* perimeter = malloc(sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ('A' <= lines[i][j] && lines[i][j] <= 'Z') {
                *area = 0;
                *perimeter = 0;
                find_fence(lines, n, m, i, j, perimeter, area);
                price += (*perimeter) * (*area);
            }
        }
    }
    free(area);
    free(perimeter);

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Total price: %llu\n", price);
}
