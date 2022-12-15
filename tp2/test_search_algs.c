#include "constants.h"
#include "search_algs.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cette fonction sert à tester les différents algorithmes
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "USAGE: ./test_search_algs TEXT_FILE WORDS_FILE\n");
        exit(EXIT_FAILURE);
    }

    FILE *y = fopen(argv[1], "r");
    if (y == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    FILE *x = fopen(argv[2], "r");
    if (x == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

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
    int word_len = (int) strlen(words[0]);

    // Mettre le texte dans un char*
    char text[TEXT_LEN + word_len + 1];
    if (fread(text, sizeof(char), TEXT_LEN, y) <= 0) {
        perror("fread on y");
        exit(EXIT_FAILURE);
    }
    fclose(y);

    printf("Search of %s\n", words[0]);
    // int nb = naive_bi(words[0], word_len, text, TEXT_LEN);
    int nbb = naive_bi_br(words[0], word_len, text, TEXT_LEN);
    int nbbs = naive_bi_br_sent(words[0], word_len, text, TEXT_LEN);
    // int ns = naive_strncmp(words[0], word_len, text, TEXT_LEN);
    int nsb = naive_strncmp_br(words[0], word_len, text, TEXT_LEN);
    int nsbs = naive_strncmp_br_sent(words[0], word_len, text, TEXT_LEN);
    int mp = morris_pratt(words[0], word_len, text, TEXT_LEN);
    int kmp = knuth_mp(words[0], word_len, text, TEXT_LEN);
    int bm = boyer_moore(words[0], word_len, text, TEXT_LEN, 2);
    int hp = horspool(words[0], word_len, text, TEXT_LEN, 2);

    // print au format cvs
    printf("nbb,%d\nnbbs,%d\nnsb,%d\nnsbs,%d\nmp,%d\nkmp,%d\nbm,%"
           "d\nhp,%d\n",
            nbb, nbbs, nsb, nsbs, mp, kmp, bm, hp);
    return EXIT_SUCCESS;
}
