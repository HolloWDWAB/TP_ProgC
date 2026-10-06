/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "serveur.h"

int socketfd = -1;

static int ouvrir_navigateur_si_disponible(void)
{
  const char *browser = getenv("BROWSER");
  char command[256];
  int result;

  if (browser != NULL && browser[0] != '\0')
  {
    snprintf(command, sizeof(command), "%s %s", browser, SVG_FILE_PATH);
    result = system(command);
    if (result == 0)
    {
      return 0;
    }
  }

  if (access("/usr/bin/firefox", X_OK) == 0)
  {
    snprintf(command, sizeof(command), "firefox %s", SVG_FILE_PATH);
    result = system(command);
    if (result == 0)
    {
      return 0;
    }
  }

  printf("Fichier SVG généré dans %s. Ouvrez-le manuellement dans un navigateur.\n", SVG_FILE_PATH);
  return 0;
}

static double degres_vers_radians(double degres)
{
  return degres * M_PI / 180.0;
}

static int creer_svg_pour_palettes(char *data)
{
  char *copie = strdup(data);
  char *p = copie;
  char *liste = NULL;
  char *token = NULL;
  char *saveptr = NULL;
  int nombre_couleurs = 0;
  int i = 0;
  FILE *svg_file = NULL;
  double start_angle = -90.0;
  const double center_x = 200.0;
  const double center_y = 200.0;
  const double radius = 150.0;

  if (copie == NULL)
  {
    perror("strdup");
    return EXIT_FAILURE;
  }

  if (strncmp(copie, "couleurs:", 9) != 0)
  {
    free(copie);
    return EXIT_FAILURE;
  }

  p = strchr(copie, ':');
  if (p == NULL)
  {
    free(copie);
    return EXIT_FAILURE;
  }

  p = strchr(p + 1, ':');
  if (p == NULL)
  {
    free(copie);
    return EXIT_FAILURE;
  }

  *p = '\0';
  nombre_couleurs = atoi(copie + 9);
  liste = p + 1;

  svg_file = fopen(SVG_FILE_PATH, "w");
  if (svg_file == NULL)
  {
    perror("Erreur ouverture SVG");
    free(copie);
    return EXIT_FAILURE;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\"/>\n");

  for (token = strtok_r(liste, ",", &saveptr), i = 0; token != NULL && i < nombre_couleurs; token = strtok_r(NULL, ",", &saveptr), i++)
  {
    double angle = 360.0 / (double)(nombre_couleurs > 0 ? nombre_couleurs : 1);
    double end_angle = start_angle + angle;
    double start_rad = degres_vers_radians(start_angle);
    double end_rad = degres_vers_radians(end_angle);
    double x1 = center_x + radius * cos(start_rad);
    double y1 = center_y + radius * sin(start_rad);
    double x2 = center_x + radius * cos(end_rad);
    double y2 = center_y + radius * sin(end_rad);

    fprintf(svg_file, "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\"/>\n",
            x1, y1, radius, radius, x2, y2, center_x, center_y, token);
    start_angle = end_angle;
  }

  fprintf(svg_file, "</svg>\n");
  fclose(svg_file);
  free(copie);

  ouvrir_navigateur_si_disponible();
  return EXIT_SUCCESS;
}

int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int recois_envoie_message(int client_socket_fd, char *data)
{
  printf("Message recu: %s\n", data);

  if (strncmp(data, "message:", 8) == 0)
  {
    return renvoie_message(client_socket_fd, data);
  }

  if (strncmp(data, "couleurs:", 9) == 0)
  {
    int status = creer_svg_pour_palettes(data);
    if (status == EXIT_SUCCESS)
    {
      char ack[64] = "ok:palette_generique";
      return renvoie_message(client_socket_fd, ack);
    }
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void gestionnaire_ctrl_c(int signal)
{
  (void)signal;
  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");

  if (socketfd != -1)
  {
    close(socketfd);
  }

  exit(0);
}

int main(void)
{
  int bind_status;
  struct sockaddr_in server_addr;
  int option = 1;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return EXIT_FAILURE;
  }

  signal(SIGINT, gestionnaire_ctrl_c);

  printf("Serveur en attente de connexions...\n");

  while (1)
  {
    listen(socketfd, 10);

    struct sockaddr_in client_addr;
    char data[4096];
    unsigned int client_addr_len = sizeof(client_addr);

    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      return EXIT_FAILURE;
    }

    memset(data, 0, sizeof(data));

    int data_size = read(client_socket_fd, (void *)data, sizeof(data));
    if (data_size < 0)
    {
      perror("erreur lecture");
      close(client_socket_fd);
      return EXIT_FAILURE;
    }

    if (data_size > 0)
    {
      recois_envoie_message(client_socket_fd, data);
    }

    close(client_socket_fd);
  }

  return 0;
}
