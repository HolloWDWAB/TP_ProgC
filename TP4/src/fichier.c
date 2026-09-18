#include "fichier.h"

#include <stdio.h>

int lire_fichier(const char *nom_de_fichier)
{
	FILE *fichier = fopen(nom_de_fichier, "r");
	int caractere;

	if (fichier == NULL) {
		perror("Impossible d'ouvrir le fichier en lecture");
		return -1;
	}

	while ((caractere = fgetc(fichier)) != EOF) {
		putchar(caractere);
	}

	if (fclose(fichier) != 0) {
		perror("Impossible de fermer le fichier");
		return -1;
	}

	return 0;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
	FILE *fichier = fopen(nom_de_fichier, "a");

	if (fichier == NULL) {
		perror("Impossible d'ouvrir le fichier en ecriture");
		return -1;
	}

	if (fputs(message, fichier) == EOF || fputc('\n', fichier) == EOF) {
		perror("Impossible d'ecrire dans le fichier");
		fclose(fichier);
		return -1;
	}

	if (fclose(fichier) != 0) {
		perror("Impossible de fermer le fichier");
		return -1;
	}

	return 0;
}
