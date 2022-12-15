#include "constants.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_COUNT 100
#define TEXT_LEN 500000

void bon_pref(const char *x, int m, int *bon_pref);

void meil_pref(const char *x, int m, int *meil_pref);

void dern_occ(const char *x, int m, int alpha, int *dernocc);

// Return nb of occurence of x, a word of size m, in y, a text of size n
unsigned long naive_bi(const char *x, int m, const char *y, int n);

unsigned long naive_bi_br(const char *x, int m, const char *y, int n);

unsigned long naive_bi_br_sent(const char *x, int m, char *y, int n);

unsigned long naive_strncmp(const char *x, int m, const char *y, int n);

unsigned long naive_strncmp_br(const char *x, int m, const char *y, int n);

unsigned long naive_strncmp_br_sent(const char *x, int m, char *y, int n);

unsigned long morris_pratt(const char *x, int m, const char *y, int n);

unsigned long knuth_mp(const char *x, int m, const char *y, int n);

unsigned long boyer_moore(const char *x, int m, const char *y, int n,
        int alpha);

unsigned long horspool(char const *x, int m, const char *y, int n, int alpha);

int main(void) {
    // Cette fonction sert à tester les différents algorithmes
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
    int word_len = 12;

    // Remplir le tableau words avec les mots du fichier x
    char buf[BUF_SIZE] = {'\0'};
    if (fread(buf, sizeof(char), BUF_SIZE, x) <= 0) {
        perror("fread on x");
        exit(EXIT_FAILURE);
    }

    char *words[WORD_COUNT + 1];
    int i = 0;
    words[i++] = strtok(buf, " ");
    while (i < WORD_COUNT) {
        words[i++] = strtok(NULL, " ");
    }
    fclose(x);

    // Mettre le texte dans un char*
    char text[TEXT_LEN + word_len + 1];
    if (fread(text, sizeof(char), TEXT_LEN, y) <= 0) {
        perror("fread on y");
        exit(EXIT_FAILURE);
    }
    fclose(y);

    printf("Search of %s\n", words[0]);
    unsigned long mp = morris_pratt(words[0], word_len, text, TEXT_LEN);
    unsigned long kmp = knuth_mp(words[0], word_len, text, TEXT_LEN);
    // unsigned long nb = naive_bi(words[0], word_len, text, TEXT_LEN);
    unsigned long nbb = naive_bi_br(words[0], word_len, text, TEXT_LEN);
    // unsigned long ns = naive_strncmp(words[0], word_len, text, TEXT_LEN);
    unsigned long nsb = naive_strncmp_br(words[0], word_len, text, TEXT_LEN);
    unsigned long nbbs = naive_bi_br_sent(words[0], word_len, text, TEXT_LEN);
    unsigned long nsbs =
            naive_strncmp_br_sent(words[0], word_len, text, TEXT_LEN);
    unsigned long bm = boyer_moore(words[0], word_len, text, TEXT_LEN, 2);
    unsigned long hp = horspool(words[0], word_len, text, TEXT_LEN, 2);

    // print au format cvs
    printf("nbb,%zu\nnbbs,%zu\nnsb,%zu\nnsbs,%zu\nmp,%zu\nkmp,%zu\nbm,%"
           "zu\nhp,%zu\n",
            nbb, nbbs, nsb, nsbs, mp, kmp, bm, hp);
    return EXIT_SUCCESS;
}

// ALGOS
// unsigned long naive_bi(const char *x, unsigned long m, char *y, unsigned long
// n) {}

unsigned long naive_bi_br(const char *x, int m, const char *y, int n) {
    unsigned long occ = 0;
    int i;
    for (int j = 0; j <= n - m; j++) {
        for (i = 0; i < m && x[i] == y[i + j]; i++) {}
        if (i >= m)
            occ++;
    }
    return occ;
}

void add_sent(const char *x, int m, char *y, int n) {
    for (int i = 0; i < m; i++)
        y[n + i] = x[i];
}

void remove_sent(char *text, int text_len) {
    text[text_len + 1] = '\0';
}

unsigned long naive_bi_br_sent(const char *x, int m, char *y, int n) {
    unsigned long occ = 0;
    add_sent(x, m, y, n);

    int i, j = 0;
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

// unsigned long naive_strncmp(const char *x, int m, char *y, int n) {}

unsigned long naive_strncmp_br(const char *x, int m, const char *y, int n) {
    unsigned long occ = 0;
    for (int j = 0; j <= n - m; j++)
        if (strncmp(y + j, x, (size_t) m) == 0)
            occ += 1;
    return occ;
}

unsigned long naive_strncmp_br_sent(const char *x, int m, char *y, int n) {
    unsigned long occ = 0;
    add_sent(x, m, y, n);
    int j = 0;
    while (1) {
        if (strncmp(y + j, x, (size_t) m) == 0) {
            if (j == n) {
                remove_sent(y, n);
                return occ;
            }
            occ += 1;
        }
        j += 1;
    }
}

void bon_pref(const char *x, int m, int *bp) {
    bp[0] = -1;
    int i = 0;
    for (int j = 1; j < m; j++) {
        bp[j] = i;
        while (i >= 0 && x[i] != x[j])
            i = bp[i];
        i += 1;
    }
    bp[m] = i;
}

void meil_pref(const char *x, int m, int *mp) {
    mp[0] = -1;
    int i = 0;
    for (int j = 1; j < m; j++) {
        if (x[i] == x[j])
            mp[j] = mp[i];
        else {
            mp[j] = i;
            do
                i = mp[i];
            while (i >= 0 && x[i] != x[j]);
        }
        i += 1;
    }
    mp[m] = i;
}

unsigned long morris_pratt(const char *x, int m, const char *y, int n) {
    int bp[m];
    for (int i = 0; i < m; i++)
        bp[i] = 0;
    bon_pref(x, m, bp);

    unsigned long occ = 0;
    int i = 0;
    for (int j = 0; j < n - m; j++) {
        while (i >= 0 && x[i] != y[j])
            i = bp[i];
        i += 1;
        if (i == m) {
            occ += 1;
            i = bp[i];
        }
    }
    return occ;
}

unsigned long knuth_mp(const char *x, int m, const char *y, int n) {
    int mp[m];
    for (int i = 0; i < m; i++)
        mp[i] = 0;
    meil_pref(x, m, mp);

    unsigned long occ = 0;
    int i = 0;
    for (int j = 0; j < n - m; j++) {
        while (i >= 0 && x[i] != y[j])
            i = mp[i];
        i += 1;
        if (i == m) {
            occ += 1;
            i = mp[i];
        }
    }
    return occ;
}

void dern_occ(const char *x, int m, int alpha, int *dernocc) {
    for (int i = 0; i < alpha; i++)
        dernocc[i] = m;
    for (int i = 0; i < m - 1; i++)
        dernocc[x[i] - ALPHA_START] = m - i - 1;
}

void suff(const char *x, int m, int *s) {
    for (int i = 0; i < m; i++)
        s[i] = 0;

    int f = 0;

    s[m - 1] = m;
    int g = m - 1;
    for (int i = m - 2; i >= 0; --i) {
        if (i > g && s[i + m - 1 - f] < i - g)
            s[i] = s[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                g -= 1;
            s[i] = f - g;
        }
    }
}

void bon_suff(const char *x, int m, int *bonsuff) {
    int s[m];
    suff(x, m, s);

    for (int i = 0; i < m; ++i)
        bonsuff[i] = m;
    for (int i = m - 1; i >= 0; --i)
        if (s[i] == i + 1)
            for (int j = 0; j < m - 1 - i; ++j)
                if (bonsuff[j] == m)
                    bonsuff[j] = m - 1 - i;

    for (int i = 0; i <= m - 2; ++i)
        bonsuff[m - 1 - s[i]] = m - 1 - i;
}

unsigned long boyer_moore(const char *x, int m, const char *y, int n,
        int alpha) {
    unsigned long occ = 0;

    int dernocc[alpha];
    dern_occ(x, m, alpha, dernocc);

    int bonsuff[m];
    bon_suff(x, m, bonsuff);

    int i;
    int j = 0;
    while (j <= n - m) {
        for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i) {}
        if (i < 0) {
            occ++;
            j += bonsuff[0];
        } else {
            int d = dernocc[y[j + i] - ALPHA_START] - m + 1 + i;
            j += (bonsuff[i] > d ? bonsuff[i] : d);
        }
    }
    return occ;
}

unsigned long horspool(char const *x, int m, const char *y, int n, int alpha) {
    unsigned int occ = 0;

    int dernocc[alpha];
    dern_occ(x, m, alpha, dernocc);

    int j = 0;
    while (j <= n - m) {
        char yj = y[j + m - 1];
        if (x[m - 1] == yj && strncmp(x, y + j, (size_t) m - 1) == 0)
            occ += 1;
        j += dernocc[yj - ALPHA_START];
    }
    return occ;
}
