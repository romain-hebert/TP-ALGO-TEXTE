#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _USE_HASH

Trie createTrie(int maxNode) {
    Trie t = malloc(sizeof(struct _trie));
    if (t == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    t->maxNode = maxNode;
    t->nextNode = 1;
    t->transition = calloc(UCHAR_MAX, sizeof(int *));
    for (size_t k = 0; k < UCHAR_MAX; ++k) {
        t->transition[k] = calloc((size_t) t->maxNode + 1, sizeof(int));
    }

    if (t->transition == NULL) {
        perror("calloc()");
        free(t);
        exit(EXIT_FAILURE);
    }
    t->finite = calloc((size_t) t->maxNode + 1, sizeof(char));
    if (t->finite == NULL) {
        perror("calloc()");
        free(t->transition);
        free(t);
        exit(EXIT_FAILURE);
    }
    return t;
}

void insertInTrie(Trie trie, unsigned char *w) {
    if (w == NULL) {
        fprintf(stderr, "word is NULL\n");
        exit(EXIT_FAILURE);
    }
    size_t n = 0;
    while (w[n++] != '\0') {}
    for (size_t i = 0; i <= n; ++i) {
        trie->transition[w[i]][i] = trie->nextNode;
        trie->nextNode++;
    }
    trie->finite[trie->nextNode - 1] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {
    if (w == NULL) {
        fprintf(stderr, "word is NULL\n");
        exit(EXIT_FAILURE);
    }
    size_t n = 0;
    while (w[n++] != '\0') {}
    int node;
    for (size_t i = 0; i <= n; ++i) {
        node = trie->transition[w[i]][i];
        if (node == 0) {
            return -1;
        }
    }
    if (trie->finite[node] == 0) {
        return -1;
    }

    return 0;
}

void freeTrie(Trie trie) {
    free(trie->finite);
    for (size_t k = 0; k < UCHAR_MAX; ++k) {
        free(trie->transition[k]);
    }
    free(trie->transition);
    free(trie);
}

#else

#endif