#include "operator.h"

int somme(int num1, int num2)
{
	return num1 + num2;
}

int difference(int num1, int num2)
{
	return num1 - num2;
}

int produit(int num1, int num2)
{
	return num1 * num2;
}

int quotient(int num1, int num2)
{
	return num2 == 0 ? 0 : num1 / num2;
}

int modulo(int num1, int num2)
{
	return num2 == 0 ? 0 : num1 % num2;
}

int et_logique(int num1, int num2)
{
	return num1 & num2;
}

int ou_logique(int num1, int num2)
{
	return num1 | num2;
}

int negation(int num1, int num2)
{
	(void)num2;
	return ~num1;
}

int calculer(int num1, int num2, char operateur)
{
	switch (operateur) {
	case '+':
		return somme(num1, num2);
	case '-':
		return difference(num1, num2);
	case '*':
		return produit(num1, num2);
	case '/':
		return quotient(num1, num2);
	case '%':
		return modulo(num1, num2);
	case '&':
		return et_logique(num1, num2);
	case '|':
		return ou_logique(num1, num2);
	case '~':
		return negation(num1, num2);
	default:
		return 0;
	}
}
