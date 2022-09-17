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
    while (*w != '\0') {
        printf("%c\n", *w);
        if (trie->transition[*w][n] == 0) {
            n = (size_t) trie->nextNode;
            trie->transition[*w][n - 1] = trie->nextNode++;
        } else {
            n = (size_t) trie->transition[*w][n];
        }
        w += sizeof(w[0]);
    }
    trie->finite[n] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {
    if (w == NULL) {
        fprintf(stderr, "word is NULL\n");
        exit(EXIT_FAILURE);
    }
    size_t n = 0;
    while (*w != '\0') {
        if (trie->transition[*w][n] == 0) {
            return -1;
        }
        n = (size_t) trie->transition[*w][n];
        w += sizeof(w[0]);
    }
    // int node;
    // for (size_t i = 0; i <= n; ++i) {
    //     node = trie->transition[w[i]][i];
    //     if (node == 0) {
    //         return -1;
    //     }
    // }
    if (trie->finite[n] == 0) {
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