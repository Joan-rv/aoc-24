#include <fcntl.h>
#include <libgnl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

typedef struct Node {
    ull num;
    struct Node* next;
} Node;

ull string_to_int(char** n) {
    ull r = 0;
    while ('0' <= **n && **n <= '9') {
        r = r * 10 + **n - '0';
        (*n)++;
    }
    return r;
}

ull blink(Node* node) {
    ull n = 0;
    while (node != NULL) {
        ull d = (int)log10(node->num) + 1;
        if (node->num == 0) {
            node->num = 1;
            node = node->next;
        } else if (d % 2 == 0) {
            Node* node2 = malloc(sizeof(Node));
            node2->next = node->next;
            node->next = node2;
            node2->num = node->num % (ull)pow(10, (ull)(d / 2));
            node->num = node->num / (ull)pow(10, (ull)(d / 2));
            node = node2->next;
            n++;
        } else {
            node->num *= 2024;
            node = node->next;
        }
        n++;
    }
    return n;
}

int main() {
    int input = open("input", O_RDONLY);
    if (input < 0) {
        perror("open");
    }
    char* line;
    char* data;
    data = get_next_line(input);
    line = data;
    Node* head = malloc(sizeof(Node));
    Node* node = head;
    node->num = string_to_int(&line);
    while (*line != '\n') {
        line++;
        node->next = malloc(sizeof(Node));
        node = node->next;
        node->num = string_to_int(&line);
        node->next = NULL;
    }
    free(data);

    for (int i = 0; i < 24; i++) {
        ull n = blink(head);
        printf("n=%llu i=%d\r", n, i);
        fflush(stdout);
    }
    printf("Number of stones: %llu\n", blink(head));
}
