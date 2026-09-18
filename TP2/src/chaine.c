#include <stdio.h>

int main(void)
{
	char premiere[80];
	char deuxieme[80];
	char copie[80];
	char concatenee[160];
	int longueurPremiere = 0;
	int longueurConcatenee = 0;
	int i;

	printf("Premiere chaine : ");
	fgets(premiere, sizeof(premiere), stdin);
	printf("Deuxieme chaine : ");
	fgets(deuxieme, sizeof(deuxieme), stdin);

	while (premiere[longueurPremiere] != '\0') {
		if (premiere[longueurPremiere] == '\n') {
			premiere[longueurPremiere] = '\0';
			break;
		}
		longueurPremiere++;
	}

	i = 0;
	while (premiere[i] != '\0') {
		copie[i] = premiere[i];
		i++;
	}
	copie[i] = '\0';

	i = 0;
	while (premiere[i] != '\0') {
		concatenee[i] = premiere[i];
		i++;
	}

	longueurConcatenee = i;
	i = 0;
	while (deuxieme[i] != '\0' && deuxieme[i] != '\n') {
		concatenee[longueurConcatenee] = deuxieme[i];
		longueurConcatenee++;
		i++;
	}
	concatenee[longueurConcatenee] = '\0';

	printf("Longueur de la premiere chaine : %d\n", longueurPremiere);
	printf("Copie : %s\n", copie);
	printf("Concatenation : %s\n", concatenee);
	printf("Longueur concatenee : %d\n", longueurConcatenee);

	return 0;
}
