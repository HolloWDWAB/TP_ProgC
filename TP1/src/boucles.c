#include <stdio.h>

int main() {
	int compteur = 5;
	int ligne;
	int colonne;

	printf("Triangle avec for :\n");
	for (ligne = 1; ligne <= compteur; ligne++) {
		for (colonne = 1; colonne <= ligne; colonne++) {
			if (ligne == 1 || ligne == 2 || ligne == compteur || colonne == 1 || colonne == ligne) {
				printf("*");
			} else {
				printf("#");
			}

			if (colonne < ligne) {
				printf(" ");
			}
		}
		printf("\n");
	}

	printf("\nTriangle avec while :\n");
	ligne = 1;
	while (ligne <= compteur) {
		colonne = 1;
		while (colonne <= ligne) {
			if (ligne == 1 || ligne == 2 || ligne == compteur || colonne == 1 || colonne == ligne) {
				printf("*");
			} else {
				printf("#");
			}

			if (colonne < ligne) {
				printf(" ");
			}
			colonne++;
		}
		printf("\n");
		ligne++;
	}

	return 0;
}
