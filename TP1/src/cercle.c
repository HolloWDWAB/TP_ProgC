#include <stdio.h>

int main() {
    const double pi = 3.14159;
    double rayon;
    double aire;
    double perimetre;

    printf("Entrez le rayon du cercle : ");
    scanf("%lf", &rayon);

    aire = pi * rayon * rayon;
    perimetre = 2 * pi * rayon;

    printf("Aire du cercle = %.2f\n", aire);
    printf("Perimetre du cercle = %.2f\n", perimetre);
}

