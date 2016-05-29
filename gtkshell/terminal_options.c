/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
  Boston, MA  02110-1301  USA
*/

#ifdef HAVE_VTE

#include "gtkshell.h"
#define CHECKTERM if(!(gsh->terminal))\
  gsh->terminal = ARNEW (gsh, GSH_Terminal, gsh);
void
gsh_option_terminal_width_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	CHECKTERM;
	gsh->terminal->dimensions.width = atoi(argv[++(*counter)]);
}

void
gsh_option_terminal_height_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	CHECKTERM;
	gsh->terminal->dimensions.height = atoi(argv[++(*counter)]);
}

void gsh_option_terminal_font_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	CHECKTERM;
	gsh->terminal->font = (gchar *) argv[++(*counter)];
}

void
gsh_option_terminal_transparent_cb(GSH * gsh,
				   gint * counter __attribute__ ((unused)),
				   const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_TERM_TRANSPARENT);
}

void
gsh_option_terminal_not_transparent_cb(GSH * gsh,
				       gint * counter
				       __attribute__ ((unused)),
				       const gchar ** argv
				       __attribute__ ((unused)))
{
	GSH_UNSET(GSH_TERM_TRANSPARENT);
}

void
gsh_option_terminal_not_tab_cb(GSH * gsh,
			       gint * counter __attribute__ ((unused)),
			       const gchar ** argv __attribute__ ((unused)))
{
	gsh->terminal = NULL;
}

#endif /* HAVE_VTE */
