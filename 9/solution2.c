#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;
typedef unsigned long long ull;

void print_sectors(ll* sectors, ull n) {
    for (ull i = 0; i < n; i++) {
        if (sectors[i] == -1) {
            printf(".");
        } else {
            printf("%lld", sectors[i]);
        }
    }
    puts("");
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    line = get_next_line(input);
    ull len = strlen(line);
    for (ull i = 0; i < len - 1; i++) {
        line[i] -= '0';
    }

    ull n = 0;
    for (ull i = 0; i < len - 1; i++) {
        n += line[i];
    }
    ll* sectors = malloc(n * sizeof(ll));
    ull i_0 = 0;
    for (ull id = 0; 2 * id < len - 1; id++) {
        for (ull i = 0; i < (ull)(line[2 * id]); i++) {
            sectors[i_0 + i] = id;
        }
        i_0 += line[2 * id];
        if (line[2 * id + 1] == '\n') {
            break;
        }
        for (ull i = 0; i < (ull)(line[2 * id + 1]); i++) {
            sectors[i_0 + i] = -1;
        }
        i_0 += line[2 * id + 1];
    }

    ll i_f = n - 1;
    for (ll id_last = 2 * ((len - 2) / 2); id_last > 0; id_last -= 2) {
        i_0 = 0;
        for (ll id = 1; id < id_last; id += 2) {
            while (sectors[i_0] == -1) {
                i_0++;
            }
            while (sectors[i_0] != -1 && sectors[i_0 + 1] != (id + 1) / 2) {
                i_0++;
            }
            // free space greater than file size
            if (line[id] >= line[id_last]) {
                for (int i = 0; i < line[id_last]; i++) {
                    sectors[i_0 + i] = id_last / 2;
                    sectors[i_f - i] = -1;
                }
                // i_f -= line[id_last - 1];
                line[id] -= line[id_last];
                break;
            }
        }
        while (sectors[i_f] != (id_last - 2) / 2) {
            i_f--;
        }
    }

    ull checksum = 0;
    for (ull i = 0; i < n; i++) {
        if (sectors[i] != -1) {
            checksum += i * sectors[i];
        }
    }

    free(line);
    free(sectors);
    printf("Filesystem checksum: %llu\n", checksum);
}
