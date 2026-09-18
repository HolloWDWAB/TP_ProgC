#include <stdio.h>

int main() {
	char caractere = 'A';
	signed char caractere_signe = -10;
	unsigned char caractere_non_signe = 250;

	short entier_court = -1000;
	signed short entier_court_signe = -2000;
	unsigned short entier_court_non_signe = 2000;

	int entier = -100000;
	signed int entier_signe = -200000;
	unsigned int entier_non_signe = 200000;

	long int entier_long = -300000L;
	signed long int entier_long_signe = -400000L;
	unsigned long int entier_long_non_signe = 400000UL;

	long long int entier_tres_long = -500000LL;
	signed long long int entier_tres_long_signe = -600000LL;
	unsigned long long int entier_tres_long_non_signe = 600000ULL;

	float nombre_float = 3.14f;
	double nombre_double = 6.28;
	long double nombre_long_double = 9.42L;

	printf("char : %c\n", caractere);
	printf("signed char : %hhd\n", caractere_signe);
	printf("unsigned char : %hhu\n", caractere_non_signe);

	printf("short : %hd\n", entier_court);
	printf("signed short : %hd\n", entier_court_signe);
	printf("unsigned short : %hu\n", entier_court_non_signe);

	printf("int : %d\n", entier);
	printf("signed int : %d\n", entier_signe);
	printf("unsigned int : %u\n", entier_non_signe);

	printf("long int : %ld\n", entier_long);
	printf("signed long int : %ld\n", entier_long_signe);
	printf("unsigned long int : %lu\n", entier_long_non_signe);

	printf("long long int : %lld\n", entier_tres_long);
	printf("signed long long int : %lld\n", entier_tres_long_signe);
	printf("unsigned long long int : %llu\n", entier_tres_long_non_signe);

	printf("float : %.2f\n", nombre_float);
	printf("double : %.2f\n", nombre_double);
	printf("long double : %.2Lf\n", nombre_long_double);

	return 0;
}
