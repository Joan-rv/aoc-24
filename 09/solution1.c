#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    line = get_next_line(input);

    char* position = malloc((strlen(line) - 1) * sizeof(char*));
    for (ull i = 0; i < (ull)strlen(line) - 1; i++) {
        position[i] = line[i] - '0';
    }
    ull id_start = 0;
    ull id_end = (strlen(line) - 2) / 2;
    ull i_string = 0;
    ull i = 0;
    ull checksum = 0;
    while (position[2 * id_end] > 0 || position[2 * id_start] > 0) {
        if (i_string % 2 == 0 && position[i_string] > 0) {
            if (checksum + i * id_start < checksum) {
                fprintf(stderr, "OVERFLOW!");
                return -1;
            }
            checksum += i * id_start;
            printf("%llu * %llu\n", i, id_start);
            position[i_string]--;
            if (position[i_string] == 0) {
                i_string++;
                id_start++;
            }
            i++;
        } else if (position[i_string] > 0) {
            if (checksum + i * id_start < checksum) {
                fprintf(stderr, "OVERFLOW!");
                return -1;
            }
            checksum += i * id_end;
            printf("%llu * %llu\n", i, id_end);
            position[i_string]--;
            position[2 * id_end]--;
            position[2 * id_end + 1]++;
            if (position[i_string] == 0) {
                i_string++;
            }
            if (position[2 * id_end] == 0) {
                id_end--;
            }
            i++;
        } else {
            i_string++;
        }
    }

    free(line);
    free(position);
    printf("Filesystem checksum: %llu\n", checksum);
}
