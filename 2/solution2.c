#include <fcntl.h>
#include <libgnl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int string_to_int(char** n) {
    int r = 0;
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r;
}

bool is_tolerate_safe_efficient(int* data, size_t size, bool dampen) {
    if (!dampen) {
        int tmp = data[0];
        data[0] = 0;
        if (is_tolerate_safe_efficient(data, size, true)) {
            return true;
        }
        data[0] = tmp;
    }
    bool increasing;
    int prev = data[0];
    int start_i = 1;
    if (data[0] == 0) {
        increasing = data[1] < data[2];
        prev = data[1];
        start_i = 2;
    } else if (data[1] == 0) {
        increasing = data[0] < data[2];
    } else {
        increasing = data[0] < data[1];
    }

    for (size_t i = start_i; i < size; i++) {
        if (data[i] == 0) {
            continue;
        }
        int dif;
        if (increasing) {
            dif = data[i] - prev;
        } else {
            dif = prev - data[i];
        }
        if (dif < 1 || dif > 3) {
            if (dampen) {
                return false;
            }
            int tmp = data[i];
            data[i] = 0;
            bool r = is_tolerate_safe_efficient(data, size, true);
            data[i - 1] = 0;
            data[i] = tmp;
            return (r || is_tolerate_safe_efficient(data, size, true));
        }
        prev = data[i];
    }
    return true;
}

bool is_safe(int* data, size_t size) {
    bool increasing;
    int prev = data[0];
    int start_i = 1;
    if (data[0] == 0) {
        increasing = data[1] < data[2];
        prev = data[1];
        start_i = 2;
    } else if (data[1] == 0) {
        increasing = data[0] < data[2];
    } else {
        increasing = data[0] < data[1];
    }

    for (size_t i = start_i; i < size; i++) {
        if (data[i] == 0) {
            continue;
        }
        int dif;
        if (increasing) {
            dif = data[i] - prev;
        } else {
            dif = prev - data[i];
        }
        if (dif < 1 || dif > 3) {
            return false;
        }
        prev = data[i];
    }
    return true;
}

bool is_tolerate_safe(int* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        int tmp = data[i];
        data[i] = 0;
        if (is_safe(data, size)) {
            data[i] = tmp;
            return true;
        }
        data[i] = tmp;
    }
    return false;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    int n = 0;
    char* line;
    while ((line = get_next_line(input))) {
        char* saved = line;
        int* data;
        size_t s = 0;
        while (*line != '\n' && *line != '\0') {
            while (*line == ' ') {
                line++;
            }
            s++;
            data = realloc(data, s * sizeof(int));
            data[s - 1] = string_to_int(&line);
        }
        if (is_tolerate_safe_efficient(data, s, false)) {
            n++;
        }
        free(saved);
        s = 0;
        data = realloc(data, 0);
    }
    printf("%d reports are safe\n", n);
}
