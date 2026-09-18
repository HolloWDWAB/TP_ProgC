#include <stdio.h>

int main() {
	int nombres[] = {0, 4096, 65536, 65535, 1024};
	int nombre_de_valeurs = sizeof(nombres) / sizeof(nombres[0]);

	for (int valeur = 0; valeur < nombre_de_valeurs; valeur++) {
		int nombre = nombres[valeur];
		int bits[32];
		int nombre_de_bits = 0;
		int temporaire = nombre;

		if (nombre == 0) {
			bits[nombre_de_bits++] = 0;
		} else {
			for (; temporaire > 0; temporaire /= 2) {
				bits[nombre_de_bits++] = temporaire % 2;
			}
		}

		printf("%d en binaire : ", nombre);
		for (int position = nombre_de_bits - 1; position >= 0; position--) {
			printf("%d", bits[position]);
		}
		printf("\n");
	}

	return 0;
}
