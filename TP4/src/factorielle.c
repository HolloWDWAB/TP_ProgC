#include <stdio.h>

unsigned long long factorielle(int nombre)
{
	if (nombre <= 1) {
		return 1;
	}
	return (unsigned long long)nombre * factorielle(nombre - 1);
}

int main(void)
{
	int nombre;

	printf("Entrez un entier naturel (0 a 20) : ");
	if (scanf("%d", &nombre) != 1 || nombre < 0 || nombre > 20) {
		fprintf(stderr, "Valeur invalide.\n");
		return 1;
	}

	printf("%d! = %llu\n", nombre, factorielle(nombre));
	return 0;
}
