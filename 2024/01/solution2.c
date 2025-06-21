#include <fcntl.h>
#include <libgnl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_to_int(char** s) {
    int r = 0;
    while ('0' <= (*s)[0] && (*s)[0] <= '9') {
        r = r * 10 + (*s)[0] - '0';
        (*s)++;
    }
    return r;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(int* l, size_t s) {
    if (s == 1) {
        return;
    }
    int* low = l;
    size_t low_s = s / 2;
    size_t high_s = s - s / 2;
    int* high = l + s / 2;
    quicksort(low, low_s);
    quicksort(high, high_s);

    // TODO merge lists
}

void bubblesort(int* l, size_t s) {
    for (size_t i = 0; i < s; i++) {
        for (size_t j = i + 1; j < s; j++) {
            if (l[j] < l[i]) {
                swap(l + j, l + i);
            }
        }
    }
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        fprintf(stderr, "Error reading data\n");
        perror("open");
        return -1;
    }
    int* l1 = NULL;
    int* l2 = NULL;
    size_t s1 = 0;
    size_t s2 = 0;
    char* line;
    while ((line = get_next_line(input))) {
        char* dat = line;
        int n1 = string_to_int(&dat);
        while ((*(dat++)) == ' ')
            ;
        dat--;
        int n2 = string_to_int(&dat);
        s1++;
        s2++;
        l1 = realloc(l1, s1 * sizeof(int));
        l1[s1 - 1] = n1;
        l2 = realloc(l2, s2 * sizeof(int));
        l2[s2 - 1] = n2;
        free(line);
    }
    bubblesort(l1, s1);
    bubblesort(l2, s2);
    int* freq = malloc(s1 * sizeof(int));
    memset(freq, 0, s1 * sizeof(int));
    size_t j = 0;
    for (size_t i = 0; i < s1 && j < s2; i++) {
        while (l2[j] < l1[i]) {
            j++;
            if (j >= s2) {
                break;
            }
        }
        while (l1[i] == l2[j] && j < s2) {
            freq[i]++;
            j++;
            if (j >= s2) {
                break;
            }
        }
    }

    int score = 0;
    for (size_t i = 0; i < s1; i++) {
        score += l1[i] * freq[i];
    }
    printf("similarity score: %d\n", score);
    free(l1);
    free(l2);
}
