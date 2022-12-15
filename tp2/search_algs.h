void bon_pref(const char *x, int m, int *bon_pref);

void meil_pref(const char *x, int m, int *meil_pref);

void dern_occ(const char *x, int m, int alpha, int *dernocc);

// Return nb of occurence of x, a word of size m, in y, a text of size n
int naive_bi(const char *x, int m, const char *y, int n);

int naive_bi_br(const char *x, int m, const char *y, int n);

// Le texte y doit avoir suffisement de place alloué pour y ajouter la
// sentinelle.
int naive_bi_br_sent(const char *x, int m, char *y, int n);

int naive_strncmp(const char *x, int m, const char *y, int n);

int naive_strncmp_br(const char *x, int m, const char *y, int n);

// Le texte y doit avoir suffisement de place alloué pour y ajouter la
// sentinelle.
int naive_strncmp_br_sent(const char *x, int m, char *y, int n);

int morris_pratt(const char *x, int m, const char *y, int n);

int knuth_mp(const char *x, int m, const char *y, int n);

int boyer_moore(const char *x, int m, const char *y, int n, int alpha);

int horspool(char const *x, int m, const char *y, int n, int alpha);
