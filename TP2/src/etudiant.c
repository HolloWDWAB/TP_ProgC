#include <stdio.h>

int main(void)
{
	const char *noms[5] = {
		"Dupont", "Martin", "Bernard", "Moreau", "Petit"
	};
	const char *prenoms[5] = {
		"Marie", "Pierre", "Sophie", "Lucas", "Emma"
	};
	const char *adresses[5] = {
		"20 Boulevard Niels Bohr, Lyon",
		"22 Boulevard Niels Bohr, Lyon",
		"5 rue des Lilas, Grenoble",
		"8 avenue Victor Hugo, Paris",
		"14 rue Pasteur, Lille"
	};
	float notesProgrammation[5] = {16.5f, 14.0f, 15.5f, 12.0f, 17.0f};
	float notesSysteme[5] = {12.1f, 14.1f, 13.5f, 15.0f, 16.0f};

	for (int i = 0; i < 5; i++) {
		printf("Etudiant.e %d :\n", i + 1);
		printf("Nom : %s\n", noms[i]);
		printf("Prenom : %s\n", prenoms[i]);
		printf("Adresse : %s\n", adresses[i]);
		printf("Note en programmation C : %.1f\n", notesProgrammation[i]);
		printf("Note en systeme d'exploitation : %.1f\n\n", notesSysteme[i]);
	}

	return 0;
}
