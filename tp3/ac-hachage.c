#include "ac-hachage.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Algos AC
Trie pre_ac(unsigned char *words[], int nb_words) {
    Trie trie = createTrie(1000);
    for (int i = 0; i < nb_words; i++) {
        insertInTrie(trie, words[i]);
    }

    completer(trie);
    return trie;
}

// File
struct _queue {
    int node;
    struct _queue *next;
};

struct queue {
    struct _queue *head;
    struct _queue *tail;
    int size;
};

void enqueue(struct queue *q, int node) {
    struct _queue *newNode = (struct _queue *) malloc(sizeof(struct _queue));
    newNode->node = node;
    newNode->next = NULL;
    if (q->tail == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size++;
}

int dequeue(struct queue *q) {
    if (q->head == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    int node = q->head->node;
    struct _queue *temp = q->head;
    q->head = q->head->next;
    free(temp);
    q->size--;
    return node;
}

void completer(Trie trie) {
    struct queue q;
    q.head = NULL, q.tail = NULL;
    q.size = 0;
    // …
}

int main() {
    unsigned char *words[100];
    // Lecture du fichier mots

    Trie trie = pre_ac(words, 100);

    freeTrie(trie);
    return EXIT_SUCCESS;
}
