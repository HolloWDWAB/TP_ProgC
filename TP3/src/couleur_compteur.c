#include <stdio.h>

struct Couleur {
	unsigned char rouge;
	unsigned char vert;
	unsigned char bleu;
	unsigned char alpha;
};

struct CouleurDistincte {
	struct Couleur couleur;
	int occurrences;
};

int main(void)
{
	const struct Couleur palette[5] = {
		{0xff, 0x23, 0x23, 0x45},
		{0xff, 0x00, 0x23, 0x12},
		{0x12, 0x34, 0x56, 0xff},
		{0x00, 0xff, 0x80, 0xff},
		{0xab, 0xcd, 0xef, 0xff}
	};
	struct Couleur couleurs[100];
	struct CouleurDistincte distinctes[100];
	int nombreDistinctes = 0;

	for (int i = 0; i < 100; i++) {
		couleurs[i] = palette[i % 5];
	}

	for (int i = 0; i < 100; i++) {
		int indice = -1;

		for (int j = 0; j < nombreDistinctes; j++) {
			if (distinctes[j].couleur.rouge == couleurs[i].rouge
				&& distinctes[j].couleur.vert == couleurs[i].vert
				&& distinctes[j].couleur.bleu == couleurs[i].bleu
				&& distinctes[j].couleur.alpha == couleurs[i].alpha) {
				indice = j;
				break;
			}
		}

		if (indice >= 0) {
			distinctes[indice].occurrences++;
		} else {
			distinctes[nombreDistinctes].couleur = couleurs[i];
			distinctes[nombreDistinctes].occurrences = 1;
			nombreDistinctes++;
		}
	}

	for (int i = 0; i < nombreDistinctes; i++) {
		struct Couleur couleur = distinctes[i].couleur;

		printf("%02x %02x %02x %02x : %d\n",
			   (unsigned int)couleur.rouge,
			   (unsigned int)couleur.vert,
			   (unsigned int)couleur.bleu,
			   (unsigned int)couleur.alpha,
			   distinctes[i].occurrences);
	}

	return 0;
}
