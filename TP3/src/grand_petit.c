#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int tableau[100];
	int plusPetit;
	int plusGrand;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++) {
		tableau[i] = rand() % 1000 + 1;
	}

	plusPetit = tableau[0];
	plusGrand = tableau[0];
	for (int i = 1; i < 100; i++) {
		if (tableau[i] < plusPetit) {
			plusPetit = tableau[i];
		}
		if (tableau[i] > plusGrand) {
			plusGrand = tableau[i];
		}
	}

	printf("Le numero le plus grand est : %d\n", plusGrand);
	printf("Le numero le plus petit est : %d\n", plusPetit);

	return 0;
}
