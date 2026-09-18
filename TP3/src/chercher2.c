#include <stdio.h>

int main(void)
{
    const char phrases[10][100] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };
    char recherche[100];
    int trouve = 0;

    printf("Entrez une phrase a rechercher : ");
    if (fgets(recherche, sizeof(recherche), stdin) == NULL) {
        return 1;
    }

    for (int i = 0; recherche[i] != '\0'; i++) {
        if (recherche[i] == '\n') {
            recherche[i] = '\0';
            break;
        }
    }

    for (int i = 0; i < 10 && !trouve; i++) {
        int j = 0;

        while (phrases[i][j] != '\0'
               && recherche[j] != '\0'
               && phrases[i][j] == recherche[j]) {
            j++;
        }

        if (phrases[i][j] == '\0' && recherche[j] == '\0') {
            trouve = 1;
        }
    }

    printf("Phrase %s\n", trouve ? "trouvee" : "non trouvee");

    return 0;
}