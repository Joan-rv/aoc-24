#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

extern "C" {
char* get_next_line(int fd);
}

int string_to_int(char** n) {
    int r = 0;
    int sign = 1;
    if (**n == '-') {
        sign = -1;
        (*n)++;
    }
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r * sign;
}

int mod(int a, int m) {
    int r = a % m;
    if (r < 0) {
        r += m;
    }
    return r;
}

struct Robot {
    int vx, vy;
};

void print_robots(std::vector<std::vector<std::vector<Robot>>> robots, int n,
                  int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (robots[i][j].size() == 0) {
                printf(".");
            } else {
                // printf("%lu", robots[i][j].size());
                printf("#");
            }
        }
        puts("");
    }
}

int main() {
    const int n = 103;
    const int m = 101;
    // const int n = 7;
    // const int m = 11;
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    std::vector<std::vector<std::vector<Robot>>> robots(
        n, std::vector<std::vector<Robot>>(m));
    while ((line = get_next_line(input))) {
        line += 2;
        int x0 = string_to_int(&line);
        line++;
        int y0 = string_to_int(&line);
        line += 3;
        Robot r;
        r.vx = string_to_int(&line);
        line++;
        r.vy = string_to_int(&line);
        robots[y0][x0].push_back(r);
    }

    for (int s = 0; s < 10000; s++) {
        std::vector<std::vector<std::vector<Robot>>> robots2(
            n, std::vector<std::vector<Robot>>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (const auto& r : robots[i][j]) {
                    int xf = mod(j + r.vx, m);
                    int yf = mod(i + r.vy, n);
                    robots2[yf][xf].push_back(r);
                }
            }
        }
        robots = robots2;
        print_robots(robots, n, m);
        printf("%d\n", s + 1);
    }

    // print_robots(robots, n, m);
    /*
        int xf = mod(x0 + vx * 100, m);
        int yf = mod(y0 + vy * 100, n);
        robots[yf][xf]++;
    */

    // printf("Safety factor: %d\n", safety_factor);
}
