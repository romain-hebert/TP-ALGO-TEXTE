#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ALPHA 78
#define BUF_SIZE 4096

void text_gen(size_t len, unsigned int alphabet_size, FILE *f);

int main(void) {
    FILE *f = fopen("text2.txt", "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    text_gen(500000, 2, f);
    fclose(f);

    f = fopen("text4.txt", "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    text_gen(500000, 4, f);
    fclose(f);

    f = fopen("text20.txt", "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    text_gen(500000, 20, f);
    fclose(f);

    f = fopen("text70.txt", "w");
    if (f == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    text_gen(500000, 70, f);
    fclose(f);
    return EXIT_SUCCESS;
}

void text_gen(size_t len, unsigned int alphabet_size, FILE *f) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }
    char buf[BUF_SIZE] = {0};
    srand((unsigned int) len + alphabet_size);
    size_t i = 0;
    size_t j = 0;
    while (i++ < len) {
        buf[j++] = (char) (48 + ((unsigned int) rand() % alphabet_size));
        if (j >= BUF_SIZE - 1) {
            if (fwrite(buf, sizeof(char), j, f) <= 0) {
                fprintf(stderr, "Echec d'ecriture. 1\n");
                exit(EXIT_FAILURE);
            }
            j = 0;
        }
    }
    if (fwrite(buf, sizeof(char), j, f) <= 0) {
        fprintf(stderr, "Echec d'ecriture. 1\n");
        exit(EXIT_FAILURE);
    }
}