#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
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
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < m - 2; j++) {
            if (((lines[i][j] == 'S' && lines[i + 2][j + 2] == 'M') ||
                 (lines[i][j] == 'M' && lines[i + 2][j + 2] == 'S')) &&
                ((lines[i][j + 2] == 'S' && lines[i + 2][j] == 'M') ||
                 (lines[i][j + 2] == 'M' && lines[i + 2][j] == 'S')) &&
                lines[i + 1][j + 1] == 'A') {

                count++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    printf("Count of all occurrences: %d\n", count);
}
