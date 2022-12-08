#include "constants.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_COUNT 100
#define TEXT_LEN 500000

void bon_pref(const char *x, unsigned long m, int *bon_pref);

void meil_pref(const char *x, unsigned long m, int *meil_pref);

void dern_occ(const char *x, int m, int alpha, int *dernocc);

// Return nb of occurence of x, a word of size m, in y, a text of size n
unsigned long naive_bi(const char *x, size_t m, const char *y, size_t n);

unsigned long naive_bi_br(const char *x, size_t m, const char *y, size_t n);

unsigned long naive_bi_br_sent(const char *x, size_t m, char *y, size_t n);

unsigned long naive_strncmp(const char *x, size_t m, const char *y, size_t n);

unsigned long naive_strncmp_br(
    const char *x, size_t m, const char *y, size_t n);

unsigned long naive_strncmp_br_sent(const char *x, size_t m, char *y, size_t n);

unsigned long morris_pratt(const char *x, size_t m, const char *y, size_t n);

unsigned long knuth_mp(const char *x, size_t m, const char *y, size_t n);

int main(void) {
    FILE *y = fopen("texts/text2.txt", "rw");
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

    // Remplir le tableau words avec les mots du fichier x
    if (fread(buf, sizeof(char), BUF_SIZE, x) <= 0) {
        perror("fread on x");
        exit(EXIT_FAILURE);
    }
    words[i++] = strtok(buf, " ");
    while (i < WORD_COUNT) {
        words[i++] = strtok(NULL, " ");
    }
    fclose(x);

    // Mettre le texte dans un char*
    char text[TEXT_LEN * 2] = {'\0'};
    if (fread(text, sizeof(char), TEXT_LEN, y) <= 0) {
        perror("fread on y");
        exit(EXIT_FAILURE);
    }
    fclose(y);

    printf("Search of %s\n", words[0]);
    unsigned long mp = morris_pratt(words[0], 12, text, TEXT_LEN);
    unsigned long kmp = knuth_mp(words[0], 12, text, TEXT_LEN);
    unsigned long nbb = naive_bi_br(words[0], 12, text, TEXT_LEN);
    unsigned long nsb = naive_strncmp_br(words[0], 12, text, TEXT_LEN);
    unsigned long nbbs = naive_bi_br_sent(words[0], 12, text, TEXT_LEN);
    unsigned long nsbs = naive_strncmp_br_sent(words[0], 12, text, TEXT_LEN);

    // print au format cvs
    printf("nbb,%zu\nnbbs,%zu\nnsb,%zu\nnsbs,%zu\nmp,%zu\nkmp,%zu\n", nbb, nbbs,
        nsb, nsbs, mp, kmp);
    return EXIT_SUCCESS;
}

// ALGOS
// unsigned long naive_bi(const char *x, unsigned long m, char *y, unsigned long
// n) {}

unsigned long naive_bi_br(const char *x, size_t m, const char *y, size_t n) {
    unsigned long occ = 0;
    size_t i;
    for (size_t j = 0; j <= n - m; j++) {
        for (i = 0; i < m && x[i] == y[i + j]; i++) {}
        if (i >= m) {
            occ++;
        }
    }
    return occ;
}

void add_sent(const char *x, size_t m, char *y, size_t n) {
    for (size_t i = 0; i < m; i++) {
        y[n + i] = x[i];
    }
}

void remove_sent(char *text, size_t text_len) { text[text_len + 1] = '\0'; }

unsigned long naive_bi_br_sent(const char *x, size_t m, char *y, size_t n) {
    unsigned long occ = 0;
    add_sent(x, m, y, n);

    size_t i, j = 0;
    while (1) {
        for (i = 0; i < m && x[i] == y[i + j]; ++i) {}
        if (i >= m) {
            if (j == n) {
                remove_sent(y, n);
                return occ;
            }
            occ++;
        }
        j++;
        i = 0;
    }
    exit(EXIT_FAILURE);
}

// unsigned long naive_strncmp(const char *x, unsigned long m, char *y, unsigned
// long n)
// {}

unsigned long naive_strncmp_br(
    const char *x, unsigned long m, const char *y, unsigned long n) {
    unsigned long occ = 0;
    for (size_t j = 0; j <= n - m; j++) {
        if (strncmp(y + j, x, m) == 0) {
            occ += 1;
        }
    }
    return occ;
}

unsigned long naive_strncmp_br_sent(
    const char *x, unsigned long m, char *y, unsigned long n) {
    unsigned long occ = 0;
    add_sent(x, m, y, n);
    size_t j = 0;
    while (1) {
        if (strncmp(y + j, x, m) == 0) {
            if (j == n) {
                remove_sent(y, n);
                return occ;
            }
            occ += 1;
        }
        j += 1;
    }
}

void bon_pref(const char *x, size_t m, int *bp) {
    bp[0] = -1;
    int i = 0;
    for (size_t j = 1; j < (size_t) m; j++) {
        bp[j] = i;
        while (i >= 0 && x[i] != x[j]) {
            i = bp[i];
        }
        i += 1;
    }
    bp[m] = i;
}

void meil_pref(const char *x, size_t m, int *mp) {
    mp[0] = -1;
    int i = 0;
    for (size_t j = 1; j < (size_t) m; j++) {
        if (x[i] == x[j]) {
            mp[j] = mp[i];
        } else {
            mp[j] = i;
            do {
                i = mp[i];
            } while (i >= 0 && x[i] != x[j]);
        }
        i += 1;
    }
    mp[m] = i;
}

unsigned long morris_pratt(const char *x, size_t m, const char *y, size_t n) {
    int bp[m];
    for (size_t i = 0; i < (size_t) m; i++) {
        bp[i] = 0;
    }
    bon_pref(x, m, bp);

    unsigned long occ = 0;
    long i = 0;
    for (long j = 0; j < (long) (n - m); j++) {
        while (i >= 0 && x[i] != y[j]) {
            i = bp[i];
        }
        i += 1;
        if (i == (long) m) {
            occ += 1;
            i = bp[i];
        }
    }
    return occ;
}

unsigned long knuth_mp(const char *x, size_t m, const char *y, size_t n) {
    int mp[m];
    for (size_t i = 0; i < (size_t) m; i++) {
        mp[i] = 0;
    }
    meil_pref(x, m, mp);

    unsigned long occ = 0;
    long i = 0;
    for (long j = 0; j < (long) (n - m); j++) {
        while (i >= 0 && x[i] != y[j]) {
            i = mp[i];
        }
        i += 1;
        if (i == (long) m) {
            occ += 1;
            i = mp[i];
        }
    }
    return occ;
}

void create_dern_occ(const char *x, int m, int alpha, int *dern_occ) {
    for (int i = 0; i < alpha; i++) {
        dern_occ[i] = m;
    }
    for (int i = 0; i < m - 2; i++) {
        dern_occ[x[i] - ALPHA_START] = m - 1 - i;
    }
}

void create_suff(const char *x, int m, int *suff) {
    int f = 0;

    suff[m - 1] = m;
    int g = m - 1;
    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                g -= 1;
            suff[i] = f - g;
        }
    }
}

void create_bon_suff(const char *x, int m, int *bon_suff) {
    int suff[m];
    for (int i = 0; i < m; i++) {
        suff[i] = 0;
    }
    create_suff(x, m, suff);

    for (int i = 0; i < m; ++i)
        bon_suff[i] = m;
    for (int i = m - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (int j = 0; j < m - 1 - i; ++j)
                if (bon_suff[j] == m)
                    bon_suff[j] = m - 1 - i;
    for (int i = 0; i <= m - 2; ++i)
        bon_suff[m - 1 - suff[i]] = m - 1 - i;
}
