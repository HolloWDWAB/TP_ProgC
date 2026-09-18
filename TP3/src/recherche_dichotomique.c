#include <stdio.h>

int main(void)
{
	int tableau[100];
	int valeur;
	int debut = 0;
	int fin = 99;
	int present = 0;

	for (int i = 0; i < 100; i++) {
		tableau[i] = i * 2 - 50;
	}

	printf("Tableau trie :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d%s", tableau[i], i % 10 == 9 ? "\n" : " ");
	}

	printf("\nEntrez l'entier que vous souhaitez chercher : ");
	if (scanf("%d", &valeur) != 1) {
		return 1;
	}

	while (debut <= fin) {
		int milieu = debut + (fin - debut) / 2;

		if (tableau[milieu] == valeur) {
			present = 1;
			break;
		}
		if (tableau[milieu] < valeur) {
			debut = milieu + 1;
		} else {
			fin = milieu - 1;
		}
	}

	printf("Resultat : entier %s\n", present ? "present" : "absent");

	return 0;
}
