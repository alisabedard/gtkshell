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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

void
gsh_add_window_cb(GSH * gsh,
		  gint * counter __attribute__ ((unused)),
		  const gchar ** argv __attribute__ ((unused)))
{
	/* This is duplicate functionlity, as same can be
	   done with '---' argument.  */
	$(gsh, add.window);
	gsh->rows->current = 1;
	GSH_SET(GSH_IN_SECONDARY_WIN);
}

void
gsh_add_applet_clock_cb(GSH * gsh,
			gint * counter __attribute__ ((unused)),
			const gchar ** argv __attribute__ ((unused)))
{
	$(gsh, manage, gsh_clock_new(gsh));
}

void gsh_add_pane_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gsh_setup_hpaned(gsh, argv[++(*counter)]);
}

#ifndef HAVE_VTE
void gsh_add_command_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	GSHCommandShell *shell;

	shell = ARNEW(gsh, GSHCommandShell);
	$(gsh, manage, $(shell, get));
	if (argv[++(*counter)])
		$(shell, run, argv[*counter]);
	/* The command instance is not freed here, 
	   as it is accessed by callbacks.  */
}
#endif /* not HAVE_VTE */

void gsh_add_editor_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	GSH_SET(GSH_APP_MODE);
	gsh_text_editor(gsh, argv[++(*counter)]);
}

void gsh_add_form_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gsh_add_form(gsh, argv[++(*counter)]);
}

void gsh_add_list_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	$(gsh, manage, gsh_tree_view_new(gsh, argv[++(*counter)]));
}

void gsh_add_label_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	$(gsh, add.label, argv[++(*counter)]);
}

void
gsh_add_piped_text_cb(GSH * gsh,
		      gint * counter __attribute__ ((unused)),
		      const gchar ** argv __attribute__ ((unused)))
{
	gchar *piped;

	piped = antiright_read_file(stdin);
	gsh_text_area_set_text(gsh_text_area(gsh), piped);
	g_free(piped);
}

void
gsh_add_piped_label_cb(GSH * gsh,
		       gint * counter __attribute__ ((unused)),
		       const gchar ** argv __attribute__ ((unused)))
{
	gchar *piped;

	piped = antiright_read_file(stdin);
	$(gsh, add.label, piped);
	g_free(piped);
}

#if 0
void gsh_add_quickstart_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
#ifdef GSH_USE_QUICKSTART
	GSHQuickStart *quickstart;

	quickstart = ARNEW(gsh, GSHQuickStart);
	(*counter)++;
	$(quickstart, add, gsh, argv[*counter], argv[(*counter) + 1]);
	(*counter)++;
	$(gsh, manage, $(quickstart, getColumn));
#else /* ! GSH_USE_QUICKSTART */
#endif /* GSH_USE_QUICKSTART */
}
#endif
void
gsh_add_row_cb(GSH * gsh,
	       gint * counter __attribute__ ((unused)),
	       const gchar ** argv __attribute__ ((unused)))
{
	$(gsh->rows, new);
}

void
gsh_add_separator_cb(GSH * gsh,
		     gint * counter __attribute__ ((unused)),
		     const gchar ** argv __attribute__ ((unused)))
{
	$(gsh, manage, ((gsh->rows->total == 1)
			? gtk_vseparator_new() : gtk_hseparator_new()));
}

static void
add_commanded(GSH * gsh, gint * counter, const gchar ** argv,
	      GtkWidget * (*function) (GSH *, const gchar *))
{
	gchar *text;

	text = antiright_pipe_read(argv[++*counter]);
	function(gsh, text);
	g_free(text);
}

void gsh_add_commanded_button_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	add_commanded(gsh, counter, argv, gsh->add.button);
}

void gsh_add_commanded_label_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	add_commanded(gsh, counter, argv, gsh->add.label);
}

void gsh_add_shell_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
#ifdef HAVE_VTE
	GtkWidget *terminal;

	/* Ensure that the terminal manager object exists.  */
	if (!gsh->terminal)
		gsh->terminal = ARNEW(gsh, GSH_Terminal, gsh);
	/* Set counter to argument containing command.  */
	(*counter)++;
	/* Create a terminal widget to run the passed command.  */
	terminal = $(gsh->terminal, add, argv[*counter]);
	if (terminal) {		/* This is NULL if terminal is tabbed.  */
		/* Let GSH manage the terminal widget.  */
		$(gsh, manage, terminal);
	}
#else /* ! HAVE_VTE */
	gsh_add_command_cb(gsh, counter, argv);
#endif /* HAVE_VTE */
}

void gsh_add_entry_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	(*counter)++;
	gsh_setup_command_entry(gsh, argv[*counter]);
}

void
gsh_add_text_cb(GSH * gsh,
		gint * counter __attribute__ ((unused)),
		const gchar ** argv __attribute__ ((unused)))
{
	gsh_text_area(gsh);
}

void
gsh_add_updating_progress_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gsh_add_updated_progress(gsh, argv[++(*counter)]);
}

void gsh_add_updating_label_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	gsh_add_updated_label(gsh, argv[++(*counter)]);
}
