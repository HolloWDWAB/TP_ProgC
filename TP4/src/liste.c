#include "liste.h"

#include <stdio.h>
#include <stdlib.h>

void init_liste(struct liste_couleurs *liste)
{
	liste->tete = NULL;
}

int insertion(const struct couleur *couleur, struct liste_couleurs *liste)
{
	struct element_couleur *nouvel_element = malloc(sizeof(*nouvel_element));
	struct element_couleur *dernier;

	if (nouvel_element == NULL) {
		return -1;
	}

	nouvel_element->valeur = *couleur;
	nouvel_element->suivant = NULL;

	if (liste->tete == NULL) {
		liste->tete = nouvel_element;
		return 0;
	}

	dernier = liste->tete;
	while (dernier->suivant != NULL) {
		dernier = dernier->suivant;
	}
	dernier->suivant = nouvel_element;

	return 0;
}

void parcours(const struct liste_couleurs *liste)
{
	const struct element_couleur *element = liste->tete;

	while (element != NULL) {
		printf("Rouge : %u, Vert : %u, Bleu : %u, Alpha : %u\n",
			   (unsigned int)element->valeur.rouge,
			   (unsigned int)element->valeur.vert,
			   (unsigned int)element->valeur.bleu,
			   (unsigned int)element->valeur.alpha);
		element = element->suivant;
	}
}

void liberer_liste(struct liste_couleurs *liste)
{
	struct element_couleur *element = liste->tete;

	while (element != NULL) {
		struct element_couleur *suivant = element->suivant;
		free(element);
		element = suivant;
	}
	liste->tete = NULL;
}
