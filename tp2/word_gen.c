#include "constants.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void word_gen(int word_nb, int word_size, int alphabet_size, FILE *f);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage : ./word_gen FILE_NAME WORD_NB "
                        "WORD_SIZE ALPHABET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    int word_nb = atoi(argv[2]);
    int word_size = atoi(argv[3]);
    int alpha_size = atoi(argv[4]);

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    word_gen(word_nb, word_size, alpha_size, f);
    fclose(f);
    return EXIT_SUCCESS;
}

void word_gen(int word_nb, int word_size, int alphabet_size, FILE *f) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }
    char buf[BUF_SIZE] = {0};
    srand((unsigned int) (word_nb + word_size + alphabet_size +
                          time(NULL) % UINT_MAX));
    int i = 0;
    int j = 0;
    while (i < word_nb) {
        for (int k = 0; k < word_size; k++) {
            buf[j++] = (char) (ALPHA_START + rand() % alphabet_size);
            if (j >= BUF_SIZE - 1) {
                if (fwrite(buf, sizeof(char), (size_t) j, f) == 0) {
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
                if (fwrite(buf, sizeof(char), (size_t) j, f) == 0) {
                    fprintf(stderr, "Echec d'ecriture. 1\n");
                    exit(EXIT_FAILURE);
                }
                j = 0;
            }
        }
    }
    if (fwrite(buf, sizeof(char), (size_t) j, f) == 0 && ferror(f) != 0) {
        fprintf(stderr, "Echec d'ecriture. 1\n");
        exit(EXIT_FAILURE);
    }
}
