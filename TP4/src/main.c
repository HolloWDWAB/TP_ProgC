#include "fichier.h"
#include "liste.h"
#include "operator.h"

#include <stdio.h>
#include <string.h>

static int lire_ligne(char *destination, size_t taille)
{
	size_t longueur;

	if (fgets(destination, taille, stdin) == NULL) {
		return 0;
	}
	longueur = strlen(destination);
	if (longueur > 0 && destination[longueur - 1] == '\n') {
		destination[longueur - 1] = '\0';
	}
	return 1;
}

static void exercice_operateurs(void)
{
	int num1;
	int num2;
	char operateur;

	printf("Entrez num1 : ");
	if (scanf("%d", &num1) != 1) {
		return;
	}
	printf("Entrez num2 : ");
	if (scanf("%d", &num2) != 1) {
		return;
	}
	printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
	scanf(" %c", &operateur);

	if ((operateur == '/' || operateur == '%') && num2 == 0) {
		printf("Erreur : division par zero.\n");
		return;
	}
	printf("Resultat : %d\n", calculer(num1, num2, operateur));
}

static void exercice_fichiers(void)
{
	char choix;
	char nom_de_fichier[256];
	char message[1024];

	printf("1. Lire un fichier\n2. Ecrire dans un fichier\nVotre choix : ");
	scanf(" %c", &choix);
	getchar();

	printf("Entrez le nom du fichier : ");
	if (!lire_ligne(nom_de_fichier, sizeof(nom_de_fichier))) {
		return;
	}

	if (choix == '1') {
		printf("Contenu du fichier %s :\n", nom_de_fichier);
		lire_fichier(nom_de_fichier);
	} else if (choix == '2') {
		printf("Entrez le message a ecrire : ");
		if (lire_ligne(message, sizeof(message))
			&& ecrire_dans_fichier(nom_de_fichier, message) == 0) {
			printf("Le message a ete ecrit dans le fichier %s.\n", nom_de_fichier);
		}
	} else {
		printf("Choix invalide.\n");
	}
}

static void exercice_liste(void)
{
	const struct couleur couleurs[10] = {
		{0xff, 0x00, 0x00, 0xff}, {0x00, 0xff, 0x00, 0xff},
		{0x00, 0x00, 0xff, 0xff}, {0xff, 0xff, 0x00, 0xff},
		{0xff, 0x00, 0xff, 0xff}, {0x00, 0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff, 0xff}, {0x00, 0x00, 0x00, 0xff},
		{0x80, 0x80, 0x80, 0xff}, {0xff, 0xa5, 0x00, 0xff}
	};
	struct liste_couleurs liste;

	init_liste(&liste);
	for (int i = 0; i < 10; i++) {
		if (insertion(&couleurs[i], &liste) != 0) {
			printf("Erreur : allocation impossible.\n");
			liberer_liste(&liste);
			return;
		}
	}
	printf("Liste des couleurs :\n");
	parcours(&liste);
	liberer_liste(&liste);
}

int main(void)
{
	int exercice;

	printf("Choisissez un exercice :\n");
	printf("1. Calcul avec operateurs\n");
	printf("2. Gestion de fichiers\n");
	printf("3. Gestion d'une liste de couleurs\n");
	printf("Votre choix : ");
	if (scanf("%d", &exercice) != 1) {
		return 1;
	}
	getchar();

	switch (exercice) {
	case 1:
		exercice_operateurs();
		break;
	case 2:
		exercice_fichiers();
		break;
	case 3:
		exercice_liste();
		break;
	default:
		printf("Choix invalide.\n");
		return 1;
	}
	return 0;
}
