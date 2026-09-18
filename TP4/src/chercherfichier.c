#include <stdio.h>
#include <string.h>

static int compter_occurrences(const char *ligne, const char *phrase)
{
	int occurrences = 0;
	size_t longueur_phrase = strlen(phrase);

	if (longueur_phrase == 0) {
		return 0;
	}

	for (size_t i = 0; ligne[i] != '\0'; i++) {
		size_t j = 0;

		while (j < longueur_phrase && ligne[i + j] == phrase[j]) {
			j++;
		}
		if (j == longueur_phrase) {
			occurrences++;
		}
	}

	return occurrences;
}

static void retirer_fin_de_ligne(char *texte)
{
	size_t longueur = strlen(texte);

	while (longueur > 0
		   && (texte[longueur - 1] == '\n' || texte[longueur - 1] == '\r')) {
		texte[--longueur] = '\0';
	}
}

int main(int argc, char **argv)
{
	char nom_fichier[256];
	char phrase[256];
	char ligne[1024];
	FILE *fichier;
	int numero_ligne = 0;
	int total_occurrences = 0;

	if (argc >= 2) {
		snprintf(nom_fichier, sizeof(nom_fichier), "%s", argv[1]);
	} else {
		printf("Entrez le nom du fichier : ");
		if (fgets(nom_fichier, sizeof(nom_fichier), stdin) == NULL) {
			return 1;
		}
		retirer_fin_de_ligne(nom_fichier);
	}

	printf("Entrez la phrase que vous souhaitez rechercher : ");
	if (fgets(phrase, sizeof(phrase), stdin) == NULL) {
		return 1;
	}
	retirer_fin_de_ligne(phrase);
	if (phrase[0] == '\0') {
		fprintf(stderr, "La phrase ne peut pas etre vide.\n");
		return 1;
	}

	fichier = fopen(nom_fichier, "r");
	if (fichier == NULL) {
		perror("Impossible d'ouvrir le fichier");
		return 1;
	}

	printf("\nResultats de la recherche :\n");
	while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
		int occurrences;

		numero_ligne++;
		occurrences = compter_occurrences(ligne, phrase);
		if (occurrences > 0) {
			printf("Ligne %d, %d fois\n", numero_ligne, occurrences);
			total_occurrences += occurrences;
		}
	}
	fclose(fichier);

	if (total_occurrences == 0) {
		printf("Aucune occurrence trouvee.\n");
	}
	return 0;
}
