#include "constants.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void text_gen(int len, int alphabet_size, FILE *f);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage : ./text_gen FILE_NAME TEXT_LENGTH "
                        "ALPHABET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    int text_len = atoi(argv[2]);
    int alpha_size = atoi(argv[3]);

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    text_gen(text_len, alpha_size, f);
    fclose(f);
    return EXIT_SUCCESS;
}

void text_gen(int len, int alphabet_size, FILE *f) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }
    char buf[BUF_SIZE] = {0};
    srand((unsigned int) (len + alphabet_size + time(NULL)));
    int i = 0;
    int j = 0;
    while (i < len) {
        buf[j++] = (char) (48 + (rand() % alphabet_size));
        if (j >= BUF_SIZE - 1) {
            if (fwrite(buf, sizeof(char), (size_t) j, f) == 0) {
                fprintf(stderr, "Echec d'ecriture. 1\n");
                exit(EXIT_FAILURE);
            }
            j = 0;
        }
        i++;
    }
    if (fwrite(buf, sizeof(char), (size_t) j, f) == 0 && ferror(f) != 0) {
        fprintf(stderr, "Echec d'ecriture. 1\n");
        exit(EXIT_FAILURE);
    }
}
