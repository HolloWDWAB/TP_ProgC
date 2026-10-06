#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "repertoire.h"

static char *concat_chemin(const char *base, const char *nom)
{
  size_t longueur = strlen(base) + strlen(nom) + 2;
  char *chemin = malloc(longueur);

  if (chemin == NULL)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  snprintf(chemin, longueur, "%s/%s", base, nom);
  return chemin;
}

void lire_dossier(const char *nom_repertoire)
{
  DIR *repertoire;
  struct dirent *entree;

  if (nom_repertoire == NULL || nom_repertoire[0] == '\0')
  {
    fprintf(stderr, "Erreur : nom de répertoire invalide.\n");
    return;
  }

  repertoire = opendir(nom_repertoire);
  if (repertoire == NULL)
  {
    perror("opendir");
    return;
  }

  while ((entree = readdir(repertoire)) != NULL)
  {
    if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
    {
      continue;
    }

    printf("%s\n", entree->d_name);
  }

  closedir(repertoire);
}

void lire_dossier_recursif(const char *nom_repertoire)
{
  DIR *repertoire;
  struct dirent *entree;
  struct stat informations;

  if (nom_repertoire == NULL || nom_repertoire[0] == '\0')
  {
    fprintf(stderr, "Erreur : nom de répertoire invalide.\n");
    return;
  }

  repertoire = opendir(nom_repertoire);
  if (repertoire == NULL)
  {
    perror("opendir");
    return;
  }

  while ((entree = readdir(repertoire)) != NULL)
  {
    char *chemin_complet;

    if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
    {
      continue;
    }

    printf("%s\n", entree->d_name);

    chemin_complet = concat_chemin(nom_repertoire, entree->d_name);
    if (stat(chemin_complet, &informations) == 0 && S_ISDIR(informations.st_mode))
    {
      lire_dossier_recursif(chemin_complet);
    }

    free(chemin_complet);
  }

  closedir(repertoire);
}

void lire_dossier_iteratif(const char *nom_repertoire)
{
  char **pile = NULL;
  size_t taille = 0;
  size_t capacite = 0;

  if (nom_repertoire == NULL || nom_repertoire[0] == '\0')
  {
    fprintf(stderr, "Erreur : nom de répertoire invalide.\n");
    return;
  }

  capacite = 8;
  pile = malloc(sizeof(char *) * capacite);
  if (pile == NULL)
  {
    perror("malloc");
    return;
  }

  pile[taille++] = strdup(nom_repertoire);

  while (taille > 0)
  {
    char *repertoire_courant = pile[--taille];
    DIR *repertoire = opendir(repertoire_courant);
    struct dirent *entree;

    if (repertoire == NULL)
    {
      perror("opendir");
      free(repertoire_courant);
      continue;
    }

    while ((entree = readdir(repertoire)) != NULL)
    {
      char *chemin_complet;
      struct stat informations;

      if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
      {
        continue;
      }

      printf("%s\n", entree->d_name);

      chemin_complet = concat_chemin(repertoire_courant, entree->d_name);
      if (stat(chemin_complet, &informations) == 0 && S_ISDIR(informations.st_mode))
      {
        if (taille == capacite)
        {
          capacite *= 2;
          pile = realloc(pile, sizeof(char *) * capacite);
          if (pile == NULL)
          {
            perror("realloc");
            exit(EXIT_FAILURE);
          }
        }

        pile[taille++] = chemin_complet;
      }
      else
      {
        free(chemin_complet);
      }
    }

    closedir(repertoire);
    free(repertoire_courant);
  }

  free(pile);
}

int main(int argc, char *argv[])
{
  if (argc != 2 && argc != 3)
  {
    fprintf(stderr, "Utilisation : %s [--recursif|--iteratif] <nom_du_repertoire>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (argc == 2)
  {
    lire_dossier(argv[1]);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1], "--recursif") == 0)
  {
    lire_dossier_recursif(argv[2]);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1], "--iteratif") == 0)
  {
    lire_dossier_iteratif(argv[2]);
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "Option inconnue : %s\n", argv[1]);
  return EXIT_FAILURE;
}
