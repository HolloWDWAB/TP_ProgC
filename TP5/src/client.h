/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

#define PORT 8089

int envoie_recois_message(int socketfd);
int envoie_operateur_numeros(int socketfd, char operateur, double nombre1, double nombre2);

#endif
