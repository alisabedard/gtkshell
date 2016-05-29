/*
  GUIShell
  (c) 2002-2010 Jeffrey Bedard
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

#include "gtkshell.h"

static bool gsh_check_geometry(struct GSH *gsh)
{
	/* Use a default geometry if the application has a scrolling window and
	 * the geometry has not yet been specified.  */
	if (G_UNLIKELY(GSH_FLAG(GSH_SCROLL)) && G_LIKELY(!(gsh->geometry)))
		gsh->geometry = g_strdup("400x267");

	/* Result used in test of whether or not to set geometry.  */
	return (gsh->geometry);
}

/* gsh->geometry is freed after this, so only call once.  */
void gsh_check_and_set_geometry(struct GSH *gsh)
{
	if (gsh && gsh_check_geometry(gsh)) {
		/* Use GTK convenience function to set window geometry.  */
		gtk_window_parse_geometry(GTK_WINDOW(gsh->widgets.window),
					  gsh->geometry);
		/* Free the geometry string pointer after use, so this function,
		 * if called twice, will use a default geometry, not the user
		 * specified one.  */
		g_free(gsh->geometry);
		/* Mark as unallocated.  */
		gsh->geometry = NULL;
	}
}
