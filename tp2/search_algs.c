#include "search_algs.h"
#include "constants.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ALGOS
// int naive_bi(const char *x, int m, char *y, int n) {}

int naive_bi_br(const char *x, int m, const char *y, int n) {
    int occ = 0;
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

int naive_bi_br_sent(const char *x, int m, char *y, int n) {
    int occ = 0;
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

// int naive_strncmp(const char *x, int m, char *y, int n) {}

int naive_strncmp_br(const char *x, int m, const char *y, int n) {
    int occ = 0;
    for (int j = 0; j <= n - m; j++)
        if (strncmp(y + j, x, (size_t) m) == 0)
            occ += 1;
    return occ;
}

int naive_strncmp_br_sent(const char *x, int m, char *y, int n) {
    int occ = 0;
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

int morris_pratt(const char *x, int m, const char *y, int n) {
    int bp[m];
    for (int i = 0; i < m; i++)
        bp[i] = 0;
    bon_pref(x, m, bp);

    int occ = 0;
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

int knuth_mp(const char *x, int m, const char *y, int n) {
    int mp[m];
    for (int i = 0; i < m; i++)
        mp[i] = 0;
    meil_pref(x, m, mp);

    int occ = 0;
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

int boyer_moore(const char *x, int m, const char *y, int n, int alpha) {
    int occ = 0;

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

int horspool(char const *x, int m, const char *y, int n, int alpha) {
    int occ = 0;

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

void dern_occ2(const char *x, int m, int alpha, int *dernocc2) {
    int i;

    for (i = 0; i < alpha; ++i)
        dernocc2[i] = m + 1;
    for (i = 0; i < m; ++i)
        dernocc2[x[i] - ALPHA_START] = m - i;
}

int quick_search(const char *x, int m, const char *y, int n, int alpha) {
    int occ = 0;

    int dernocc2[alpha];
    dern_occ2(x, m, alpha, dernocc2);

    int j = 0;
    while (j <= n - m) {
        if (strncmp(y + j, x, (size_t) m) == 0)
            occ += 1;
        j += dernocc2[*(y + j + m) - ALPHA_START];
    }
    return occ;
}
