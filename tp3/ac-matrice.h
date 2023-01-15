#define MAX_NODES 1000

// Trie
struct _trie {
    int maxNode;            /* Nombre maximal de noeuds du trie */
    int nextNode;           /* Indice du prochain noeud disponible */
    int **transition;       /* matrice de transition */
    unsigned char **sortie; /* Sortie pour chaque noeud */
    int *sup;               /* Tableau des supleants */
};

typedef struct _trie *Trie;

Trie createTrie(int maxNode);

void insertInTrie(Trie trie, unsigned char *w);

int isInTrie(Trie trie, unsigned char *w);

void freeTrie(Trie trie);

// AC
Trie pre_ac(unsigned char *words[], int nb_words);

void completer(Trie Trie);
