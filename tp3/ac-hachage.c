#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enqueue(int *sup_queue, int *tail, int node) {
    sup_queue[(*tail)++] = node;
}

int dequeue(int *sup_queue, int *head) {
    return sup_queue[(*head)++];
}

void build_fail_pointers(Trie trie, int *sup) {
    int sup_queue[trie->maxNode];
    int head = 0, tail = 0;

    trie->finite[0] = 0;
    sup[0] = 0;

    enqueue(sup_queue, &tail, 0);

    while (head < tail) {
        int curr_node = dequeue(sup_queue, &head);
        List transition = trie->transition[curr_node];
        while (transition != NULL) {
            int target_node = transition->targetNode;
            enqueue(sup_queue, &tail, target_node);
            int fail_node = trie->finite[curr_node];
            while (fail_node > 0 && trie->transition[fail_node] == NULL) {
                fail_node = trie->finite[fail_node];
            }
            if (trie->transition[fail_node] != NULL) {
                List fail_transition = trie->transition[fail_node];
                while (fail_transition != NULL &&
                        fail_transition->letter != transition->letter) {
                    fail_transition = fail_transition->next;
                }
                if (fail_transition != NULL) {
                    fail_node = fail_transition->targetNode;
                }
            }
            sup[target_node] = fail_node;
            transition = transition->next;
        }
    }
}

int main() {
    Trie trie = createTrie(1000);

    // Add some patterns to the trie
    insertInTrie(trie, "hello");
    insertInTrie(trie, "world");
    insertInTrie(trie, "test");

    int *sup = malloc(trie->maxNode * sizeof(int));

    build_fail_pointers(trie, sup);

    return EXIT_SUCCESS;
}
