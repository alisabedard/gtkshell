/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
  jefbed@gmail.com

  This file is part of GUIShell.

  GUIShell is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  GUIShell is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GUIShell; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "library.h"
#include <strings.h>

static inline gchar *substitute(const gchar * c)
{
	gchar *s = strdup(c);
	gchar *i = s;

	while (*i++)
		switch (*i) {
		case '_':
			*i = ' ';
			break;
		case '@':
			*i = '_';
			break;
		}

	return s;
}

/* Free the returned value!  */
gchar *antiright_beautified_label(const gchar * text)
{
	const char *nospace = strrchr(text, ' ');

	return substitute(nospace ? nospace : text);
}

gchar *ar_dtostr(const gdouble d)
{
	gchar *s = g_malloc(G_ASCII_DTOSTR_BUF_SIZE);

	g_ascii_dtostr(s, G_ASCII_DTOSTR_BUF_SIZE, d);

	return s;
}
