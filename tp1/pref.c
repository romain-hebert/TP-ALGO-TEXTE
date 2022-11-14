#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 101
#define WORD_SIZE 255

void printTrie(Trie trie);

int main(int argc, char *argv[]) {
    char usage[255] = "Usage: pref MOT";
    if (argc != 2) {
        fprintf(stderr, "%s\n", usage);
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "%s\n", usage);
        exit(EXIT_FAILURE);
    }
    size_t n = strlen(argv[1]);
    Trie trie = createTrie(MAX_NODES);
    for (size_t i = 1; i < n - 1; i++) {
        unsigned char w[WORD_SIZE] = {'\0'};
        strncpy((char *) w, argv[1], i);
        insertInTrie(trie, w);
    }
    printTrie(trie);
    freeTrie(trie);
    return EXIT_SUCCESS;
}

void printTrie(Trie trie) {
#ifndef _USE_HASH

    for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
        for (size_t j = 0; j < UCHAR_MAX; j++) {
            printf("%d\t", trie->transition[j][i]);
        }
        printf("\n");
    }

#else

    for (size_t k = 0; k < (size_t) trie->maxNode; ++k) {
        printf("[%2zu]", k);
        List p = trie->transition[k];
        while (p != NULL) {
            printf("->|%2d %c %2d|", p->startNode, p->letter, p->targetNode);
            p = p->next;
        }
        printf("\n");
    }

#endif

    printf("\n\nFinite:\n");
    for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
        if (trie->finite[i] == 1)
            printf("%zu ", i);
    }
    printf("\n");
}
