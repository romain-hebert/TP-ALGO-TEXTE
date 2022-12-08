#include "constants.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void word_gen(unsigned long word_nb, unsigned long word_size,
    unsigned int alphabet_size, FILE *f);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage : ./word_gen FILE_NAME WORD_NB "
                        "WORD_SIZE ALPHABET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    unsigned long word_nb = strtoul(argv[2], NULL, 10);
    unsigned long word_size = strtoul(argv[3], NULL, 10);
    unsigned int alpha_size = (unsigned int) strtol(argv[4], NULL, 10);

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    word_gen(word_nb, word_size, alpha_size, f);
    fclose(f);
    return EXIT_SUCCESS;
}

void word_gen(unsigned long word_nb, unsigned long word_size,
    unsigned int alphabet_size, FILE *f) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }
    char buf[BUF_SIZE] = {0};
    srand((unsigned int) (word_nb + word_size + alphabet_size +
                          (unsigned int) time(NULL) % UINT_MAX));
    size_t i = 0;
    size_t j = 0;
    while (i < word_nb) {
        for (size_t k = 0; k < word_size; k++) {
            buf[j++] =
                (char) (ALPHA_START + ((unsigned int) rand() % alphabet_size));
            if (j >= BUF_SIZE - 1) {
                if (fwrite(buf, sizeof(char), j, f) == 0) {
                    fprintf(stderr, "Echec d'ecriture. 1\n");
                    exit(EXIT_FAILURE);
                }
                j = 0;
            }
        }
        i++;
        if (i != word_nb) {
            buf[j++] = ' ';
            if (j >= BUF_SIZE - 1) {
                if (fwrite(buf, sizeof(char), j, f) == 0) {
                    fprintf(stderr, "Echec d'ecriture. 1\n");
                    exit(EXIT_FAILURE);
                }
                j = 0;
            }
        }
    }
    if (fwrite(buf, sizeof(char), j, f) == 0 && ferror(f) != 0) {
        fprintf(stderr, "Echec d'ecriture. 1\n");
        exit(EXIT_FAILURE);
    }
}
