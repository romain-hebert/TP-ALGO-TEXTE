#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 50

int main(void) {
    Trie trie = createTrie(MAX_NODES);
    if (trie == NULL) {
        fprintf(stderr, "createTrie()");
        exit(EXIT_FAILURE);
    }
    unsigned char w[10] = {'\0'};
    strcpy((char *) w, "Test");
    insertInTrie(trie, w);
    printf("%s : %d\n", w, isInTrie(trie, w));
    unsigned char w2[10] = {'\0'};
    strcpy((char *) w2, "Testa");
    printf("%s : %d\n\n", w2, isInTrie(trie, w2));

    for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
        for (size_t j = 0; j < UCHAR_MAX; j++) {
            printf("%d\t", trie->transition[j][i]);
        }
        printf("\n");
    }

    freeTrie(trie);
    return EXIT_SUCCESS;
}