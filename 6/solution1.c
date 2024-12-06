#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Direction { North, East, South, West } Direction;

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

    Direction direction = North;
    while (i >= 0 && j >= 0 && i < n && j < m) {
        lines[i][j] = 'X';

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
                    direction++;
                }
            } else {
                i = new_i;
                j = new_j;
            }
        } else {
            i = new_i;
            j = new_j;
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] == 'X') {
                count++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    printf("Count of distinct positions: %d\n", count);
}
