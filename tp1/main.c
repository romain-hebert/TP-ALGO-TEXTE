#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 101
#define WORD_SIZE 255

int main(void) {
    Trie trie = createTrie(MAX_NODES);
    if (trie == NULL) {
        fprintf(stderr, "createTrie()");
        exit(EXIT_FAILURE);
    }
    unsigned char w[WORD_SIZE] = "Test";
    insertInTrie(trie, w);
    unsigned char w2[WORD_SIZE] = "Terre";
    insertInTrie(trie, w2);
    unsigned char w3[WORD_SIZE] = "Testol";
    insertInTrie(trie, w3);
    unsigned char w4[WORD_SIZE] = "Testa";
    unsigned char w5[WORD_SIZE] = "Bonjour";
    insertInTrie(trie, w5);
    unsigned char w6[WORD_SIZE] = "Aurevoir";
    insertInTrie(trie, w6);
    unsigned char w7[WORD_SIZE] = "Une phrase peut aussi etre un mot!"
                                  "Meme si elle est tres longue.";
    insertInTrie(trie, w7);

    printf("%s : %d\n", w, isInTrie(trie, w));
    printf("%s : %d\n", w2, isInTrie(trie, w2));
    printf("%s : %d\n", w3, isInTrie(trie, w3));
    printf("%s : %d (un mot que l'on a pas inseré dans la table)\n", w4,
        isInTrie(trie, w4));
    printf("%s : %d\n", w5, isInTrie(trie, w5));
    printf("%s : %d\n", w6, isInTrie(trie, w6));
    printf("%s : %d\n\n", w7, isInTrie(trie, w7));

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

    freeTrie(trie);
    return EXIT_SUCCESS;
}