#include <stdio.h>

static void afficherHex(const char *nom, const void *adresse, size_t taille)
{
	const unsigned char *octets = adresse;

	printf("Adresse de %s : %p, Valeur : 0x", nom, adresse);
	for (size_t i = taille; i > 0; i--) {
		printf("%02x", (unsigned int)octets[i - 1]);
	}
	printf("\n");
}

int main(void)
{
	char caractere = 'A';
	short entierCourt = -1000;
	int entier = -100000;
	long int entierLong = -300000L;
	long long int entierTresLong = -500000LL;
	float nombreFloat = 3.14f;
	double nombreDouble = 6.28;
	long double nombreLongDouble = 9.42L;

	char *pCaractere = &caractere;
	short *pEntierCourt = &entierCourt;
	int *pEntier = &entier;
	long int *pEntierLong = &entierLong;
	long long int *pEntierTresLong = &entierTresLong;
	float *pNombreFloat = &nombreFloat;
	double *pNombreDouble = &nombreDouble;
	long double *pNombreLongDouble = &nombreLongDouble;

	printf("Avant la manipulation :\n");
	afficherHex("caractere", pCaractere, sizeof(caractere));
	afficherHex("entierCourt", pEntierCourt, sizeof(entierCourt));
	afficherHex("entier", pEntier, sizeof(entier));
	afficherHex("entierLong", pEntierLong, sizeof(entierLong));
	afficherHex("entierTresLong", pEntierTresLong, sizeof(entierTresLong));
	afficherHex("nombreFloat", pNombreFloat, sizeof(nombreFloat));
	afficherHex("nombreDouble", pNombreDouble, sizeof(nombreDouble));
	afficherHex("nombreLongDouble", pNombreLongDouble, sizeof(nombreLongDouble));

	(*pCaractere)++;
	(*pEntierCourt)++;
	(*pEntier)++;
	(*pEntierLong)++;
	(*pEntierTresLong)++;
	(*pNombreFloat) += 1.0f;
	(*pNombreDouble) += 1.0;
	(*pNombreLongDouble) += 1.0L;

	printf("\nApres la manipulation :\n");
	afficherHex("caractere", pCaractere, sizeof(caractere));
	afficherHex("entierCourt", pEntierCourt, sizeof(entierCourt));
	afficherHex("entier", pEntier, sizeof(entier));
	afficherHex("entierLong", pEntierLong, sizeof(entierLong));
	afficherHex("entierTresLong", pEntierTresLong, sizeof(entierTresLong));
	afficherHex("nombreFloat", pNombreFloat, sizeof(nombreFloat));
	afficherHex("nombreDouble", pNombreDouble, sizeof(nombreDouble));
	afficherHex("nombreLongDouble", pNombreLongDouble, sizeof(nombreLongDouble));

	return 0;
}
