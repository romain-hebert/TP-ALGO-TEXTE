#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ALPHA 78

void text_gen(unsigned long len, int alphabet_size);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage : ./genere-texte [--help] TEXT_LENGTH "
                        "ALPHABET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    unsigned long text_len = strtoul(argv[1], NULL, 10);
    int alpha_size = atoi(argv[2]);

    text_gen(text_len, alpha_size);
    return EXIT_SUCCESS;
}

void text_gen(unsigned long len, int alphabet_size) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }

    srand((unsigned int) len + (unsigned int) alphabet_size +
          (unsigned int) time(NULL));
    for (size_t i = 0; i < len; i++) {
        printf("%c", (char) (48 + (rand() % alphabet_size)));
    }
    printf("\n");
}
