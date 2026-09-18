#include <stdio.h>

int main(void)
{
	int n;
	int precedent = 0;
	int courant = 1;

	printf("Nombre de termes : ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("%d", precedent);

		if (i < n - 1) {
			printf(", ");
		}

		int suivant = precedent + courant;
		precedent = courant;
		courant = suivant;
	}

	printf("\n");

	return 0;
}
