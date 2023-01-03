#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ALPHA 78

void text_gen(int len, int alphabet_size);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage : ./genere-texte [--help] TEXT_LENGTH "
                        "ALPHABET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    int text_len = atoi(argv[1]);
    int alpha_size = atoi(argv[2]);

    text_gen(text_len, alpha_size);
    return EXIT_SUCCESS;
}

void text_gen(int len, int alphabet_size) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }

    srand((unsigned int) (len + alphabet_size) + (unsigned int) time(NULL));
    for (int i = 0; i < len; i++) {
        printf("%c", (char) (48 + (rand() % alphabet_size)));
    }
    printf("\n");
}
