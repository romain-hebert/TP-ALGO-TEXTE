#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ALPHA 78

void word_gen(
    int word_nb, int min_word_size, int max_word_size, int alphabet_size);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage : ./word_gen WORD_NB "
                        "MIN_WORD_SIZE MAX_WORD_SIZE ALPHABET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    int word_nb = atoi(argv[1]);
    int min_word_size = atoi(argv[2]);
    int max_word_size = atoi(argv[3]);
    int alpha_size = atoi(argv[4]);

    word_gen(word_nb, min_word_size, max_word_size, alpha_size);
    return EXIT_SUCCESS;
}

void word_gen(
    int word_nb, int min_word_size, int max_word_size, int alphabet_size) {
    if (alphabet_size >= MAX_ALPHA) {
        // On tombe à court de caractères ASCII lisibles.
        fprintf(stderr, "Alphabet trop grand!\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned int) word_nb + (unsigned int) min_word_size +
          (unsigned int) alphabet_size + (unsigned int) time(NULL));

    for (int i = 0; i < word_nb; i++) {
        int word_size =
            min_word_size + (rand() % (max_word_size - min_word_size + 1));
        for (int k = 0; k < word_size; k++) {
            printf("%c", (char) (48 + (rand() % alphabet_size)));
        }
        printf("\n");
    }
}
