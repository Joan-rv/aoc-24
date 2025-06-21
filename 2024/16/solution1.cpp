#include <fcntl.h>
#include <map>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
char* get_next_line(int fd);
}

typedef unsigned long long ull;

typedef enum {
    North = 1 << 0,
    East = 1 << 1,
    South = 1 << 2,
    West = 1 << 3,
} Direction;

void move_dir(int* i, int* j, Direction dir) {
    if (dir == North) {
        (*i)--;
    } else if (dir == South) {
        (*i)++;
    } else if (dir == East) {
        (*j)++;
    } else {
        (*j)--;
    }
}

Direction rotate_dir(Direction dir, int r) {
    if (r < 0) {
        Direction new_dir = (Direction)(dir >> 1);
        if (new_dir == 0) {
            return West;
        }
        return new_dir;
    } else {
        Direction new_dir = (Direction)(dir << 1);
        if (new_dir > West) {
            return North;
        }
        return new_dir;
    }
}

int min_noneg(int a, int b) {
    if (a == -1) {
        return b;
    } else if (b == -1) {
        return a;
    } else if (a < b) {
        return a;
    } else {
        return b;
    }
}

int add_or_neg(int a, int b) {
    if (a < 0) {
        return a;
    }
    return a + b;
}

void print(char** lines, bool** visited, int n, int m) {
    system("clear");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] == '.' && visited[i][j]) {
                printf("%c", '^');
            } else {
                printf("%c", lines[i][j]);
            }
        }
        puts("");
    }
    puts("");
    // system("sleep 0.1");
}

typedef std::map<std::tuple<int, int, int>, int> Memo;
int find_low_path(char** lines, bool** visited, int i_0, int j_0, int n, int m,
                  Direction dir, Memo& memo) {
    // if (memo.count({i_0, j_0, (int)dir})) {
    //     return memo[{i_0, j_0, (int)dir}];
    // }
    if (i_0 < 0 || i_0 > n || j_0 < 0 || j_0 > m) {
        return -1;
    } else if (visited[i_0][j_0]) {
        return -1;
    } else if (lines[i_0][j_0] == '#') {
        return -1;
    } else if (lines[i_0][j_0] == 'E') {
        return 0;
    }

    print(lines, visited, n, m);
    visited[i_0][j_0] = true;
    int new_i = i_0, new_j = j_0;
    move_dir(&new_i, &new_j, dir);
    int r1 = find_low_path(lines, visited, new_i, new_j, n, m, dir, memo);
    new_i = i_0, new_j = j_0;
    Direction new_dir = rotate_dir(dir, 1);
    move_dir(&new_i, &new_j, new_dir);
    int r2 = find_low_path(lines, visited, new_i, new_j, n, m, new_dir, memo);
    new_i = i_0, new_j = j_0;
    new_dir = rotate_dir(dir, -1);
    move_dir(&new_i, &new_j, new_dir);
    int r3 = find_low_path(lines, visited, new_i, new_j, n, m, new_dir, memo);
    r1 = add_or_neg(r1, 1);
    r2 = add_or_neg(r2, 1001);
    r3 = add_or_neg(r3, 1001);
    visited[i_0][j_0] = false;
    int r = min_noneg(r1, min_noneg(r2, r3));
    memo[{i_0, j_0, (int)dir}] = r;
    return r;
}

void print(char** lines, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s", lines[i]);
    }
    puts("");
}

int main() {
    int input = open("input3.test", O_RDONLY);
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
        lines = (char**)realloc(lines, n * sizeof(char*));
        lines[n - 1] = line;
    }
    int m = strlen(lines[0]) - 1;

    int i_0 = 0, j_0 = 0;
    bool found = false;
    while (i_0 < n && !found) {
        j_0 = 0;
        while (j_0 < m && !found) {
            if (lines[i_0][j_0] == 'S') {
                found = true;
            }
            j_0++;
        }
        i_0++;
    }
    i_0--;
    j_0--;

    bool** visited = (bool**)malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        visited[i] = (bool*)calloc(m, sizeof(bool));
    }

    Memo memo;
    int low_score = find_low_path(lines, visited, i_0, j_0, n, m, East, memo);

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("Lowest possible score: %d\n", low_score);
}
