#include <stdio.h>

int main() {
	int num1;
	int num2;
	char op;

	printf("Entrez num1, num2 et l'operateur : ");
	scanf("%d %d %c", &num1, &num2, &op);

	switch (op) {
		case '+':
			printf("Resultat : %d\n", num1 + num2);
			break;
		case '-':
			printf("Resultat : %d\n", num1 - num2);
			break;
		case '*':
			printf("Resultat : %d\n", num1 * num2);
			break;
		case '/':
			if (num2 == 0) {
				printf("Erreur : division par zero\n");
			} else {
				printf("Resultat : %d\n", num1 / num2);
			}
			break;
		case '%':
			if (num2 == 0) {
				printf("Erreur : modulo par zero\n");
			} else {
				printf("Resultat : %d\n", num1 % num2);
			}
			break;
		case '&':
			printf("Resultat : %d\n", num1 & num2);
			break;
		case '|':
			printf("Resultat : %d\n", num1 | num2);
			break;
		case '~':
			printf("Resultat : %d\n", ~num1);
			break;
		default:
			printf("Erreur : operateur inconnu\n");
			break;
	}

	return 0;
}

