#include <stdio.h>

int main() {
	int somme = 0;

	for (int nombre = 1; nombre <= 1000; nombre++) {
		if (nombre % 11 == 0) {
			continue;
		}

		if (nombre % 5 == 0 || nombre % 7 == 0) {
			somme += nombre;
		}

		if (somme > 5000) {
			break;
		}
	}

	printf("Somme finale : %d\n", somme);

	return 0;
}
