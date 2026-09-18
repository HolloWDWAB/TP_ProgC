#include "fichier.h"

#include <stdio.h>
#include <stdlib.h>

struct etudiant {
	char nom[64];
	char prenom[64];
	char adresse[160];
	float note_programmation;
	float note_systeme;
};

int main(void)
{
	struct etudiant etudiants[5];
	char ligne[512];

	remove("etudiant.txt");
	for (int i = 0; i < 5; i++) {
		printf("Entrez les details de l'etudiant.e %d :\n", i + 1);
		printf("Nom : ");
		if (scanf(" %63[^\n]", etudiants[i].nom) != 1) {
			return 1;
		}
		printf("Prenom : ");
		if (scanf(" %63[^\n]", etudiants[i].prenom) != 1) {
			return 1;
		}
		printf("Adresse : ");
		if (scanf(" %159[^\n]", etudiants[i].adresse) != 1) {
			return 1;
		}
		printf("Note 1 : ");
		if (scanf("%f", &etudiants[i].note_programmation) != 1) {
			return 1;
		}
		printf("Note 2 : ");
		if (scanf("%f", &etudiants[i].note_systeme) != 1) {
			return 1;
		}

		snprintf(ligne, sizeof(ligne), "%s;%s;%s;%.2f;%.2f",
				 etudiants[i].nom,
				 etudiants[i].prenom,
				 etudiants[i].adresse,
				 etudiants[i].note_programmation,
				 etudiants[i].note_systeme);
		if (ecrire_dans_fichier("etudiant.txt", ligne) != 0) {
			return 1;
		}
	}

	printf("Les details des etudiants ont ete enregistres dans etudiant.txt.\n");
	return 0;
}
