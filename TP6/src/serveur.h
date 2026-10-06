/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089
#define SVG_FILE_PATH "pie_chart.svg"

int renvoie_message(int, char *);
int recois_envoie_message(int, char *);

#endif
