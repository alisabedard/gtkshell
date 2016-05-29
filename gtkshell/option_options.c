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

void
gsh_option_null_cb(GSH * gsh __attribute__ ((unused)),
		   gint * counter __attribute__ ((unused)),
		   const gchar ** argv __attribute__ ((unused)))
{
}

void
gsh_option_app_mode_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
		       const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_APP_MODE);
}

void gsh_option_color_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gsh->editor.bgcolor = (gchar *) argv[++(*counter)];
	gsh->editor.fgcolor = (gchar *) argv[++(*counter)];
}

void
gsh_option_no_relief_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
			const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_NO_RELIEF);
}

void
gsh_option_no_dummy_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
		       const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_GUIDL_NO_DUMMY);
}

void
gsh_option_echoes_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
		     const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_PROMPT_ECHOES);
}

void
gsh_option_exits_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
		    const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_CBEXIT);
}

void
gsh_option_no_base_frame_cb(GSH * gsh,
			    gint * counter __attribute__ ((unused)),
			    const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_NO_BASE_FRAME);
}

void
gsh_option_framed_labels_cb(GSH * gsh,
			    gint * counter __attribute__ ((unused)),
			    const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_FRAMED_LABELS);
}

void gsh_option_geometry_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	ARIFP(gsh->geometry) g_free(gsh->geometry);
	gsh->geometry = g_strdup(argv[++(*counter)]);
}

void
gsh_option_horiz_clock_cb(GSH * gsh,
			  gint * counter __attribute__ ((unused)),
			  const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_HORIZ_CLOCK);
}

void
gsh_option_horiz_labels_cb(GSH * gsh,
			   gint * counter __attribute__ ((unused)),
			   const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_HORIZONTAL_LABELS);
}

void gsh_option_icon_size_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	(*counter)++;
	/* Define some shortcuts.  */
#define GIS gsh->icon_size
	/* Test for gsh->icon_size equality. 
	   Note, only the first three characters are used.   */
#define GISCMP(text) !strncmp(text, argv[*counter], 3)
#define IFGISCMP(str, icon_size)\
	{ if(GISCMP(str)) { GIS=GTK_ICON_SIZE##icon_size; return; } }

	GSH_SET(GSH_ICON_SIZE_IS_CUSTOM);

	IFGISCMP("menu", _MENU);
	IFGISCMP("small toolbar", _SMALL_TOOLBAR);
	IFGISCMP("large toolbar", _LARGE_TOOLBAR);
	IFGISCMP("toolbar", _SMALL_TOOLBAR);
	IFGISCMP("medium", _BUTTON);
	IFGISCMP("button", _BUTTON);
	IFGISCMP("dialog", _DIALOG);
	IFGISCMP("DND", _DND);
	IFGISCMP("dnd", _DND);
	/* Default */
	GIS = GTK_ICON_SIZE_BUTTON;
}

void
gsh_option_expand_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
		     const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_NO_EXPAND);
}

void
gsh_option_no_expand_cb(GSH * gsh,
			gint * counter __attribute__ ((unused)),
			const gchar ** argv __attribute__ ((unused)))
{
	GSH_UNSET(GSH_NO_EXPAND);
}

void
gsh_option_no_decorations_cb(GSH * gsh,
			     gint * counter __attribute__ ((unused)),
			     const gchar ** argv __attribute__ ((unused)))
{
	GtkWindow *window;

	/* Until ARWM handles docks correctly, this will have to be done.  */
/*#define ARWM_SUPPORTS_DOCKS*/
#ifdef ARWM_SUPPORTS_DOCKS
	gsh->widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#else
	gsh->widgets.window = gtk_window_new(GTK_WINDOW_POPUP);
#endif
	window = GTK_WINDOW(gsh->widgets.window);
	gtk_window_set_type_hint(window, GDK_WINDOW_TYPE_HINT_DOCK);
	gtk_window_set_decorated(window, FALSE);
	gtk_window_set_skip_taskbar_hint(window, TRUE);
	gtk_window_set_accept_focus(window, TRUE);
	gtk_window_set_opacity(window, 0.8);
	gtk_window_stick(window);
}

void
gsh_option_pane_next_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
			const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_PANE_NEXT);
}

void gsh_option_rows_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gsh->rows->total = (unsigned int)atoi(argv[++(*counter)]);
}

void
gsh_option_scroll_cb(GSH * gsh, gint * counter __attribute__ ((unused)),
		     const gchar ** argv __attribute__ ((unused)))
{
	GSH_SET(GSH_SCROLL);
}

void gsh_option_title_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gtk_window_set_title(GTK_WINDOW(gsh->widgets.window),
			     argv[++(*counter)]);
}

void gsh_option_update_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	if (!(gsh->update))
		gsh->update = ARNEW(gsh, GSHUpdateManager);
	gsh->update->period = atoi(argv[++(*counter)]);
}
