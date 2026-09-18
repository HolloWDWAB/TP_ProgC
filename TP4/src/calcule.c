#include "operator.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char operateur;
	char *fin_numero;
	long num1;
	long num2;

	if (argc != 4 || argv[1][0] == '\0' || argv[1][1] != '\0') {
		fprintf(stderr, "Usage : %s operateur nombre1 nombre2\n", argv[0]);
		return 1;
	}

	operateur = argv[1][0];
	num1 = strtol(argv[2], &fin_numero, 10);
	if (*fin_numero != '\0') {
		fprintf(stderr, "Premier nombre invalide.\n");
		return 1;
	}
	num2 = strtol(argv[3], &fin_numero, 10);
	if (*fin_numero != '\0' || num1 < INT_MIN || num1 > INT_MAX
		|| num2 < INT_MIN || num2 > INT_MAX) {
		fprintf(stderr, "Second nombre invalide.\n");
		return 1;
	}
	if ((operateur == '/' || operateur == '%') && num2 == 0) {
		fprintf(stderr, "Division par zero impossible.\n");
		return 1;
	}

	printf("Resultat : %d\n", calculer((int)num1, (int)num2, operateur));
	return 0;
}
