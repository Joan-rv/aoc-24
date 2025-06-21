#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

bool can_move(char** lines, int n, int m, int i_0, int j_0, char move) {
    if (move == '^') {
        for (int i = i_0 - 1; i > 0; i--) {
            if (lines[i][j_0] == '.') {
                return true;
            } else if (lines[i][j_0] == '#') {
                return false;
            }
        }
    } else if (move == 'v') {
        for (int i = i_0 + 1; i < n - 1; i++) {
            if (lines[i][j_0] == '.') {
                return true;
            } else if (lines[i][j_0] == '#') {
                return false;
            }
        }
    } else if (move == '>') {
        for (int j = j_0 + 1; j < m - 1; j++) {
            if (lines[i_0][j] == '.') {
                return true;
            } else if (lines[i_0][j] == '#') {
                return false;
            }
        }
    } else if (move == '<') {
        for (int j = j_0 - 1; j > 0; j--) {
            if (lines[i_0][j] == '.') {
                return true;
            } else if (lines[i_0][j] == '#') {
                return false;
            }
        }
    }
    return false;
}

void move(char** lines, int* i_0, int* j_0, char move) {
    int i_f = *i_0, j_f = *j_0;
    if (move == '^') {
        while (lines[i_f][j_f] != '.') {
            i_f--;
        }
        for (int i = i_f + 1; i <= *i_0; i++) {
            lines[i - 1][j_f] = lines[i][j_f];
        }
        lines[*i_0][*j_0] = '.';
        (*i_0)--;
    } else if (move == 'v') {
        while (lines[i_f][j_f] != '.') {
            i_f++;
        }
        for (int i = i_f - 1; i >= *i_0; i--) {
            lines[i + 1][j_f] = lines[i][j_f];
        }
        lines[*i_0][*j_0] = '.';
        (*i_0)++;
    } else if (move == '>') {
        while (lines[i_f][j_f] != '.') {
            j_f++;
        }
        for (int j = j_f - 1; j >= *j_0; j--) {
            lines[i_f][j + 1] = lines[i_f][j];
        }
        lines[*i_0][*j_0] = '.';
        (*j_0)++;
    } else if (move == '<') {
        while (lines[i_f][j_f] != '.') {
            j_f--;
        }
        for (int j = j_f + 1; j <= *j_0; j++) {
            lines[i_f][j - 1] = lines[i_f][j];
        }
        lines[*i_0][*j_0] = '.';
        (*j_0)--;
    }
}

void print(char** lines, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s", lines[i]);
    }
    puts("");
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
        if (*line == '\n') {
            break;
        }
        n++;
        lines = realloc(lines, n * sizeof(char*));
        lines[n - 1] = line;
    }
    int m = strlen(lines[0]) - 1;

    int i_0 = 0, j_0 = 0;
    bool found = false;
    while (i_0 < n && !found) {
        j_0 = 0;
        while (j_0 < m && !found) {
            if (lines[i_0][j_0] == '@') {
                found = true;
            }
            j_0++;
        }
        i_0++;
    }
    i_0--;
    j_0--;
    while ((line = get_next_line(input))) {
        char* saved = line;
        while (*line != '\n') {
            if (can_move(lines, n, m, i_0, j_0, *line)) {
                move(lines, &i_0, &j_0, *line);
                // print(lines, n);
            }
            line++;
        }
        free(saved);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] == 'O') {
                sum += i * 100 + j;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Sum of all GPS coordinates: %d\n", sum);
}
