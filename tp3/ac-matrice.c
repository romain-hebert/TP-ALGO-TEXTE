#include "ac-matrice.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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
    t->sortie = calloc((size_t) t->maxNode + 1, sizeof(char));
    if (t->sortie == NULL) {
        perror("calloc()");
        free(t->transition);
        free(t);
        exit(EXIT_FAILURE);
    }
    t->sup = calloc((size_t) t->maxNode + 1, sizeof(char));
    if (t->sup == NULL) {
        perror("calloc()");
        free(t->transition);
        free(t->sortie);
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
        if (trie->transition[*w][n] == 0) {
            trie->transition[*w][n] = trie->nextNode;
            n = (size_t) trie->nextNode;
            trie->nextNode += 1;
        } else {
            n = (size_t) trie->transition[*w][n];
        }
        w += sizeof(*w);
    }
    trie->sortie[n] = w;
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
    if (trie->sortie[n] == NULL) {
        return -1;
    }
    return 0;
}

void freeTrie(Trie trie) {
    free(trie->sortie);
    for (size_t k = 0; k < UCHAR_MAX; ++k) {
        free(trie->transition[k]);
    }
    free(trie->transition);
    free(trie->sortie);
    free(trie->sup);
    free(trie);
}

// AC
Trie pre_ac(unsigned char *words[], int nb_words) {
    Trie trie = createTrie(MAX_NODES);
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

void enqueue(struct queue *q, int data) {
    struct _queue *newNode = (struct _queue *) malloc(sizeof(struct _queue));
    newNode->node = data;
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
    int data = q->head->node;
    struct _queue *temp = q->head;
    q->head = q->head->next;
    free(temp);
    q->size--;
    return data;
}

void completer(Trie trie) {
    struct queue q;
    q.head = NULL, q.tail = NULL;
    q.size = 0;

    int **t = trie->transition;
    for (unsigned char j = 0; j < UCHAR_MAX; j++) {
        if (t[j][0] == 0) {
            continue;
        }
        enqueue(&q, t[j][0]);
    }
    while (q.size >= 0) {
        int r = dequeue(&q);
        if (r == -1) {
            fprintf(stderr, "Queue error\n");
            exit(EXIT_FAILURE);
        }

        for (unsigned char i = 0; i < UCHAR_MAX; i++) {
            /* code */
        }
    }
    // …
}

int main(void) {
    unsigned char *words[100];
    // Lecture du fichier mots

    Trie trie = pre_ac(words, 100);

    freeTrie(trie);
    return EXIT_SUCCESS;
}
