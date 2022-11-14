#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _USE_HASH
// Avec matrice de transitions.

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
        // printf("%c\n", *w);
        if (trie->transition[*w][n] == 0) {
            trie->transition[*w][n] = trie->nextNode;
            n = (size_t) trie->nextNode;
            trie->nextNode += 1;
        } else {
            n = (size_t) trie->transition[*w][n];
        }
        w += sizeof(*w);
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
// Avec table de hashage

#define PRIME1 23
#define PRIME2 21

int hash(const Trie trie, int nodeNb, unsigned char c);

Trie createTrie(int maxNode) {
    Trie t = malloc(sizeof(struct _trie));
    if (t == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    t->maxNode = maxNode;
    t->nextNode = 1;
    t->transition = calloc(sizeof(List), (size_t) maxNode);
    if (t->transition == NULL) {
        perror("malloc()");
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
    int n = 0;
    while (*w != '\0') {
        int h = hash(trie, n, *w);
        List p = trie->transition[h];
        while (p != NULL && p->startNode != n) {
            p = p->next;
        }
        if (p != NULL) {
            // la transition est dans la table.
            n = p->targetNode;
        } else {
            // la transition n'est pas encore dans la table.
            if (trie->nextNode >= trie->maxNode) {
                fprintf(stderr, "Limite de noeuds dépassée!\n");
                return;
            }

            p = trie->transition[h];
            List q = malloc(sizeof(*q));
            if (q == NULL) {
                perror("malloc()");
                exit(EXIT_FAILURE);
            }
            q->next = p;
            q->letter = *w;
            q->startNode = n;
            q->targetNode = trie->nextNode;
            trie->transition[h] = q;
            n = trie->nextNode;
            trie->nextNode += 1;
        }
        w += sizeof(*w);
    }

    trie->finite[n] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {
    if (w == NULL) {
        fprintf(stderr, "word is NULL\n");
        exit(EXIT_FAILURE);
    }
    int n = 0;
    while (*w != '\0') {
        List p = trie->transition[hash(trie, n, *w)];
        while (p != NULL && p->letter != *w) {
            p = p->next;
        }
        if (p == NULL) {
            return -1;
        }
        n = p->targetNode;
        w += sizeof(w[0]);
    }
    if (trie->finite[n] == 0) {
        return -1;
    }
    return 0;
}

int hash(const Trie trie, int nodeNb, unsigned char c) {
    int hash = nodeNb * PRIME1;
    hash += c * PRIME2;
    return hash % (int) trie->maxNode;
}

void freeTrie(Trie trie) {
    free(trie->finite);
    for (size_t k = 0; k < (size_t) trie->maxNode; ++k) {
        List p = trie->transition[k];
        while (p != NULL) {
            trie->transition[k] = p->next;
            free(p);
            p = trie->transition[k];
        }
    }
    free(trie->transition);
    free(trie);
}

#endif
