#include <stdio.h>

int main(void)
{
	int tableau[100];
	int valeur;
	int present = 0;

	for (int i = 0; i < 100; i++) {
		tableau[i] = i * 2 - 50;
	}

	printf("Tableau :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d%s", tableau[i], i % 10 == 9 ? "\n" : " ");
	}

	printf("\nEntrez l'entier que vous souhaitez chercher : ");
	if (scanf("%d", &valeur) != 1) {
		return 1;
	}

	for (int i = 0; i < 100; i++) {
		if (tableau[i] == valeur) {
			present = 1;
			break;
		}
	}

	printf("Resultat : entier %s\n", present ? "present" : "absent");

	return 0;
}
