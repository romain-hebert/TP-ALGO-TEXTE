#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 20

int main(void) {
    Trie trie = createTrie(MAX_NODES);
    if (trie == NULL) {
        fprintf(stderr, "createTrie()");
        exit(EXIT_FAILURE);
    }
    unsigned char w[10] = {'\0'};
    strcpy((char *) w, "Test");
    insertInTrie(trie, w);
    printf("%d\n", isInTrie(trie, w));
    unsigned char w2[10] = {'\0'};
    strcpy((char *) w2, "Testa");
    printf("%d\n", isInTrie(trie, w2));
    freeTrie(trie);
    return EXIT_SUCCESS;
}