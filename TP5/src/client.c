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

#include "client.h"

int envoie_operateur_numeros(int socketfd, char operateur, double nombre1, double nombre2)
{
  char data[1024];
  char reponse[1024];

  snprintf(data, sizeof(data), "calcule : %c %.2f %.2f", operateur, nombre1, nombre2);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(reponse, 0, sizeof(reponse));
  int read_status = read(socketfd, reponse, sizeof(reponse));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("Résultat: %s\n", reponse);
  return 0;
}

int envoie_recois_message(int socketfd)
{
  char data[1024];
  char message[1024];

  printf("Votre message (max 1000 caractères): ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  message[strcspn(message, "\r\n")] = '\0';

  if (strncmp(message, "calcule", 7) == 0)
  {
    char operateur;
    double nombre1;
    double nombre2;

    if (sscanf(message, "calcule : %c %lf %lf", &operateur, &nombre1, &nombre2) == 3 ||
        sscanf(message, "calcule: %c %lf %lf", &operateur, &nombre1, &nombre2) == 3)
    {
      return envoie_operateur_numeros(socketfd, operateur, nombre1, nombre2);
    }

    printf("Format invalide. Exemple : calcule : + 23 45\n");
    return 0;
  }

  const char *prefix = "message: ";
  size_t prefix_len = strlen(prefix);
  size_t copy_len = strlen(message);

  memset(data, 0, sizeof(data));
  if (copy_len > sizeof(data) - prefix_len - 1)
  {
    copy_len = sizeof(data) - prefix_len - 1;
  }

  memcpy(data, prefix, prefix_len);
  memcpy(data + prefix_len, message, copy_len);
  data[prefix_len + copy_len] = '\0';

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("Message reçu: %s\n", data);
  return 0;
}

int main(void)
{
  int socketfd;
  struct sockaddr_in server_addr;

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

  envoie_recois_message(socketfd);

  close(socketfd);
  return EXIT_SUCCESS;
}
