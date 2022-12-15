#include "constants.h"
#include "search_algs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE "USAGE: ./search -[p] TEXT_FILE WORDS_FILE ALPHA_SIZE ALG_NO\n"
#define ALG_NO                                                                 \
    "ALG_NO:\n1. Naive quick loop\n2. Naive quick loop with"                   \
    " sentinel\n3. Naive quick loop with strncmp\n"                            \
    "4. Naive quick loop with strncmp and sentinel\n"                          \
    "5. Morris-Pratt\n6. Knuth-Morris-Pratt\n"                                 \
    "7. Boyer-Moore\n8. Horspool\n9. Quick search\n"
#define PRINT "-p: Displays results on output, might make the program slower.\n"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, USAGE ALG_NO PRINT);
        exit(EXIT_FAILURE);
    }
    int arg = 1;
    FILE *out;
    if (strcmp("-p", argv[arg]) == 0) {
        out = stdout;
        arg++;
    } else {
        out = fopen("/dev/null", "w");
    }

    FILE *y = fopen(argv[arg++], "r");
    if (y == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    FILE *x = fopen(argv[arg++], "r");
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

    char *words[WORD_COUNT];
    char *saveptr;
    words[0] = strtok_r(buf, " ", &saveptr);
    for (size_t i = 1; i < WORD_COUNT; i++) {
        words[i] = strtok_r(NULL, " \0\n", &saveptr);
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

    int alpha_size = atoi(argv[arg++]);
    int res = 0;
    switch (atoi(argv[arg++])) {
    case 1:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = naive_bi_br(words[i], word_len, text, TEXT_LEN);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 2:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = naive_bi_br_sent(words[i], word_len, text, TEXT_LEN);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 3:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = naive_strncmp_br(words[i], word_len, text, TEXT_LEN);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 4:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = naive_strncmp_br_sent(words[i], word_len, text, TEXT_LEN);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 5:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = morris_pratt(words[i], word_len, text, TEXT_LEN);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 6:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = knuth_mp(words[i], word_len, text, TEXT_LEN);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 7:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = boyer_moore(words[i], word_len, text, TEXT_LEN, alpha_size);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 8:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = horspool(words[i], word_len, text, TEXT_LEN, alpha_size);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    case 9:
        for (size_t i = 0; i < WORD_COUNT; i++) {
            res = quick_search(words[i], word_len, text, TEXT_LEN, alpha_size);
            fprintf(out, "Occurences of %s: %d\n", words[i], res);
        }
        break;
    default:
        fprintf(stderr, "Wrong ALG_NO\nALG_NO");
        break;
    }
    fclose(out);

    return EXIT_SUCCESS;
}
