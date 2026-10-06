/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "bmp.h"
#include "client.h"

static int compare_couleur24_compteur(const void *a, const void *b)
{
  const couleur24_compteur *ca = (const couleur24_compteur *)a;
  const couleur24_compteur *cb = (const couleur24_compteur *)b;

  if (ca->compte < cb->compte)
    return 1;
  if (ca->compte > cb->compte)
    return -1;
  return 0;
}

static int compare_couleur32_compteur(const void *a, const void *b)
{
  const couleur32_compteur *ca = (const couleur32_compteur *)a;
  const couleur32_compteur *cb = (const couleur32_compteur *)b;

  if (ca->compte < cb->compte)
    return 1;
  if (ca->compte > cb->compte)
    return -1;
  return 0;
}

static void couleur_to_hex24(char *buffer, size_t size, const couleur24 *couleur)
{
  snprintf(buffer, size, "#%02x%02x%02x", couleur->rouge, couleur->vert, couleur->bleu);
}

static void couleur_to_hex32(char *buffer, size_t size, const couleur32 *couleur)
{
  snprintf(buffer, size, "#%02x%02x%02x", couleur->rouge, couleur->vert, couleur->bleu);
}

static void remplir_palette_bmp(const char *pathname, int nombre_couleurs, char *data, size_t data_size)
{
  couleur_compteur *cc = analyse_bmp_image((char *)pathname);
  int i;
  size_t offset = 0;

  if (cc == NULL)
  {
    snprintf(data, data_size, "couleurs:0:");
    return;
  }

  if (cc->compte_bit == BITS24)
  {
    couleur24_compteur *copie = malloc(sizeof(couleur24_compteur) * (size_t)cc->size);
    if (copie == NULL)
    {
      fprintf(stderr, "Erreur d'allocation pour la palette\n");
      snprintf(data, data_size, "couleurs:0:");
      return;
    }

    memcpy(copie, cc->cc.cc24, sizeof(couleur24_compteur) * (size_t)cc->size);
    qsort(copie, (size_t)cc->size, sizeof(couleur24_compteur), compare_couleur24_compteur);

    offset += snprintf(data + offset, data_size - offset, "couleurs:%d:", nombre_couleurs < cc->size ? nombre_couleurs : cc->size);
    for (i = 0; i < (nombre_couleurs < cc->size ? nombre_couleurs : cc->size); i++)
    {
      char hex[16];
      couleur_to_hex24(hex, sizeof(hex), &copie[i].c);
      offset += snprintf(data + offset, data_size - offset, "%s%s", (i == 0) ? "" : ",", hex);
    }

    free(copie);
    return;
  }

  if (cc->compte_bit == BITS32)
  {
    couleur32_compteur *copie = malloc(sizeof(couleur32_compteur) * (size_t)cc->size);
    if (copie == NULL)
    {
      fprintf(stderr, "Erreur d'allocation pour la palette\n");
      snprintf(data, data_size, "couleurs:0:");
      return;
    }

    memcpy(copie, cc->cc.cc32, sizeof(couleur32_compteur) * (size_t)cc->size);
    qsort(copie, (size_t)cc->size, sizeof(couleur32_compteur), compare_couleur32_compteur);

    offset += snprintf(data + offset, data_size - offset, "couleurs:%d:", nombre_couleurs < cc->size ? nombre_couleurs : cc->size);
    for (i = 0; i < (nombre_couleurs < cc->size ? nombre_couleurs : cc->size); i++)
    {
      char hex[16];
      couleur_to_hex32(hex, sizeof(hex), &copie[i].c);
      offset += snprintf(data + offset, data_size - offset, "%s%s", (i == 0) ? "" : ",", hex);
    }

    free(copie);
    return;
  }

  snprintf(data, data_size, "couleurs:0:");
}

int envoie_recois_message(int socketfd)
{
  char data[1024];
  char message[1024];

  memset(data, 0, sizeof(data));
  printf("Votre message (max 1000 caracteres): ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  message[strcspn(message, "\r\n")] = '\0';

  memset(data, 0, sizeof(data));
  {
    const char *prefix = "message:";
    size_t prefix_len = strlen(prefix);
    size_t copy_len = strlen(message);

    if (copy_len > sizeof(data) - prefix_len - 1)
    {
      copy_len = sizeof(data) - prefix_len - 1;
    }

    memcpy(data, prefix, prefix_len);
    memcpy(data + prefix_len, message, copy_len);
    data[prefix_len + copy_len] = '\0';
  }

  if (write(socketfd, data, strlen(data)) < 0)
  {
    perror("erreur ecriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  if (read(socketfd, data, sizeof(data)) < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu: %s\n", data);
  return 0;
}

int envoie_couleurs(int socketfd, const char *pathname, int nombre_couleurs)
{
  char data[4096];

  memset(data, 0, sizeof(data));
  remplir_palette_bmp(pathname, nombre_couleurs, data, sizeof(data));

  if (write(socketfd, data, strlen(data)) < 0)
  {
    perror("erreur ecriture");
    return -1;
  }

  return 0;
}

int main(int argc, char **argv)
{
  int socketfd;
  struct sockaddr_in server_addr;
  int nombre_couleurs = 10;

  if (argc < 2)
  {
    printf("usage: ./client chemin_bmp_image [nombre_couleurs]\n");
    return EXIT_FAILURE;
  }

  if (argc >= 3)
  {
    nombre_couleurs = atoi(argv[2]);
    if (nombre_couleurs <= 0 || nombre_couleurs > 30)
    {
      nombre_couleurs = 10;
    }
  }

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  if (argc == 2)
  {
    envoie_couleurs(socketfd, argv[1], nombre_couleurs);
  }
  else
  {
    envoie_couleurs(socketfd, argv[1], nombre_couleurs);
  }

  close(socketfd);
  return EXIT_SUCCESS;
}
