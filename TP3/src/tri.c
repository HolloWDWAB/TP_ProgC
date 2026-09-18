#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int tableau[100];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++) {
		tableau[i] = rand() % 2001 - 1000;
	}

	printf("Tableau non trie :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d%s", tableau[i], i % 10 == 9 ? "\n" : " ");
	}

	for (int passage = 0; passage < 99; passage++) {
		for (int i = 0; i < 99 - passage; i++) {
			if (tableau[i] > tableau[i + 1]) {
				int temporaire = tableau[i];
				tableau[i] = tableau[i + 1];
				tableau[i + 1] = temporaire;
			}
		}
	}

	printf("\nTableau trie par ordre croissant :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d%s", tableau[i], i % 10 == 9 ? "\n" : " ");
	}

	return 0;
}
