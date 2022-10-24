#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 4096
#define WORD_COUNT 100

void bon_pref(const char *x, int m, int *bon_pref);

void meil_pref(const char *x, int m, int *meil_pref);

// Return nb of occurence of x, a word of size m, in y, a text of size n
unsigned long morris_pratt(const char *x, int m, FILE *y, unsigned long n);

int main(void) {
    FILE *y = fopen("texts/text2.txt", "r");
    if (y == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    FILE *x = fopen("words/word2.txt", "r");
    if (x == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    char *words[WORD_COUNT + 1];
    char buf[BUF_SIZE] = {'\0'};
    size_t i = 0;

    fread(buf, sizeof(char), BUF_SIZE, x);
    words[i++] = strtok(buf, " ");
    while (i < WORD_COUNT) {
        words[i++] = strtok(NULL, " ");
    }

    printf("Search of %s\n", words[0]);
    unsigned long occ = morris_pratt(words[0], 12, y, 500000);
    printf("%zu\n", occ);
    return EXIT_SUCCESS;
}

void bon_pref(const char *x, int m, int *bp) {
    bp[0] = -1;
    int i = 0;
    for (size_t j = 1; j < (size_t) m - 1; j++) {
        bp[j] = i;
        while (i >= 0 && x[i] != x[j]) {
            i = bp[i];
        }
        i += 1;
    }
    bp[m] = i;
}

void meil_pref(const char *x, int m, int *mp) {
    mp[0] = -1;
    int i = 0;
    for (size_t j = 1; j < (size_t) m - 1; j++) {
        if (x[i] == x[j]) {
            mp[j] = mp[i];
        } else {
            mp[j] = i;
            do {
                i = mp[i];
            } while (i >= 0 && x[i != x[j]]);
        }
        i += 1;
    }
    mp[m] = i;
}

unsigned long morris_pratt(const char *x, int m, FILE *y, unsigned long n) {
    int bp[m + 1];
    for (size_t i = 0; i < (size_t) m; i++) {
        bp[i] = 0;
    }

    bon_pref(x, m, bp);
    printf("Calcul bonpref : ");
    for (size_t i = 0; i < (size_t) m; i++) {
        printf("%d ", bp[i]);
    }
    printf("\n");

    unsigned long occ = 0;
    int i = 0;
    for (size_t j = 0; j < n - 1; j++) {
        char yj = (char) fgetc(y);
        while (i >= 0 && x[i] != yj) {
            // printf("%c\n", yj);
            i = bp[i];
        }
        i += 1;
        if (i == m) {
            occ++;
            i = bp[i];
        }
    }
    return occ;
}
