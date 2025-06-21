#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_score(char** map, int n, int m, int i, int j, char h) {
    if (h == '9') {
        return 1;
    }
    int s = 0;
    if (i - 1 >= 0) {
        if (map[i - 1][j] == h + 1) {
            s += find_score(map, n, m, i - 1, j, h + 1);
        }
    }
    if (j - 1 >= 0) {
        if (map[i][j - 1] == h + 1) {
            s += find_score(map, n, m, i, j - 1, h + 1);
        }
    }
    if (i + 1 < n) {
        if (map[i + 1][j] == h + 1) {
            s += find_score(map, n, m, i + 1, j, h + 1);
        }
    }
    if (j + 1 < m) {
        if (map[i][j + 1] == h + 1) {
            s += find_score(map, n, m, i, j + 1, h + 1);
        }
    }
    return s;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int n = 0;
    char** map = NULL;
    char* line;
    while ((line = get_next_line(input))) {
        n++;
        map = realloc(map, n * sizeof(char*));
        map[n - 1] = line;
    }
    int m = strlen(map[0]) - 1;

    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == '0') {
                sum += find_score(map, n, m, i, j, '0');
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(map[i]);
    }
    free(map);
    printf("Sum of scores of trailheads: %d\n", sum);
}
