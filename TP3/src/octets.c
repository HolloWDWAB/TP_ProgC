#include <stdio.h>

static void afficherOctets(const char *nom, const void *adresse, size_t taille)
{
	const unsigned char *octets = adresse;

	printf("Octets de %s :\n", nom);
	for (size_t i = 0; i < taille; i++) {
		printf(" %02x", (unsigned int)octets[i]);
	}
	printf("\n\n");
}

int main(void)
{
	short entierCourt = 0x0302;
	int entier = 0x04030201;
	long int entierLong = 0x0807060504030201L;
	float nombreFloat = 3.0f;
	double nombreDouble = 1.0;
	long double nombreLongDouble = 1.0L;

	afficherOctets("short", &entierCourt, sizeof(entierCourt));
	afficherOctets("int", &entier, sizeof(entier));
	afficherOctets("long int", &entierLong, sizeof(entierLong));
	afficherOctets("float", &nombreFloat, sizeof(nombreFloat));
	afficherOctets("double", &nombreDouble, sizeof(nombreDouble));
	afficherOctets("long double", &nombreLongDouble, sizeof(nombreLongDouble));

	return 0;
}
