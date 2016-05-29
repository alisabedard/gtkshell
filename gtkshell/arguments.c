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

#include "gtkshell.h"

#define SPLIT_ALL -1

static void menubar_parse(GSH * gsh, const gchar * string)
{
	gchar **tokens;

#ifdef DEBUG
	ARPASSERT(gsh);
	ARPASSERT(string);
#endif /* DEBUG */
	tokens = g_strsplit(string, "::", SPLIT_ALL);
	/* Determine if the button is a regular button or a menu button.  */
	if (tokens[1]) {
		if (!GSH_FLAG(GSH_ICON_SIZE_IS_CUSTOM))
			gsh->icon_size = GTK_ICON_SIZE_MENU;
		gsh_menubutton_parse(gsh, tokens);
	} else {
		if (!GSH_FLAG(GSH_ICON_SIZE_IS_CUSTOM))
			gsh->icon_size = GTK_ICON_SIZE_DND;
		$(gsh, add.button, string);
	}
	g_strfreev(tokens);
}

static void add_each_menu(GSH * gsh, gchar ** menubar_tokens)
{
	guint i;

#ifdef DEBUG
	ARPASSERT(gsh);
	ARPASSERT(menubar_tokens);
#endif /* DEBUG */

	for (i = 0; menubar_tokens[i]; i++)
		menubar_parse(gsh, menubar_tokens[i]);
}

/* Decide whether to use a regular button or a menu button.  */
static void button_parse(GSH * gsh, const gchar * string)
{
	gchar **menubar_tokens;

#ifdef DEBUG
	ARPASSERT(gsh);
	ARPASSERT(string);
#endif /* DEBUG */

	/* 
	   This allows a group of buttons and menu buttons to be specified
	   as one argument.  This is particularly useful in eliminating the
	   need for the ADD BUTTONS tokens in GUIDL, though that feature
	   will remain as it improves readability of an interface definition.
	 */
	menubar_tokens = g_strsplit(string, ":::", SPLIT_ALL);
	/* If ":::" is not found, STRING will be contained in
	   menubar_tokens[0].  */
	add_each_menu(gsh, menubar_tokens);
	g_strfreev(menubar_tokens);
}

void gsh_parse_arguments(GSH * gsh, const gint argc, const gchar ** argv)
{
	gint counter;

	for (counter = 1; counter < argc; counter++)
		(argv[counter][0] == '-') ?
		    gsh_handle_switch_argument(gsh, argv, &counter)
		    : button_parse(gsh, argv[counter]);
#ifdef LIBGC
	GC_gcollect();
#endif /* LIBGC */
}
