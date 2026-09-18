#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	enum { TAILLE = 11 };
	int entiers[TAILLE];
	float flottants[TAILLE];
	int *pEntier;
	float *pFlottant;

	srand((unsigned int)time(NULL));

	pEntier = entiers;
	pFlottant = flottants;
	for (int i = 0; i < TAILLE; i++) {
		*pEntier = rand() % 100 + 1;
		*pFlottant = (float)rand() / (float)RAND_MAX * 10.0f;
		pEntier++;
		pFlottant++;
	}

	printf("Tableau d'entiers (avant la multiplication par 3) :\n");
	pEntier = entiers;
	for (int i = 0; i < TAILLE; i++) {
		printf("%d%s", *pEntier, i == TAILLE - 1 ? "\n" : ", ");
		pEntier++;
	}

	printf("Tableau de nombres a virgule flottante (avant la multiplication par 3) :\n");
	pFlottant = flottants;
	for (int i = 0; i < TAILLE; i++) {
		printf("%.2f%s", *pFlottant, i == TAILLE - 1 ? "\n" : ", ");
		pFlottant++;
	}

	pEntier = entiers;
	pFlottant = flottants;
	for (int i = 0; i < TAILLE; i++) {
		if (i % 2 == 0) {
			*pEntier *= 3;
			*pFlottant *= 3.0f;
		}
		pEntier++;
		pFlottant++;
	}

	printf("\nTableau d'entiers (apres la multiplication par 3) :\n");
	pEntier = entiers;
	for (int i = 0; i < TAILLE; i++) {
		printf("%d%s", *pEntier, i == TAILLE - 1 ? "\n" : ", ");
		pEntier++;
	}

	printf("Tableau de nombres a virgule flottante (apres la multiplication par 3) :\n");
	pFlottant = flottants;
	for (int i = 0; i < TAILLE; i++) {
		printf("%.2f%s", *pFlottant, i == TAILLE - 1 ? "\n" : ", ");
		pFlottant++;
	}

	return 0;
}
