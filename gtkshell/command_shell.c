/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
  antiright@gmail.com

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
#ifndef HAVE_VTE
#include "gtkshell.h"

static void
gsh_delete_GSHCommandShell (GSHCommandShell * this)
{
  g_free (this);
}

static GtkWidget *
get_command_shell (GSHCommandShell * this)
{
  return this->widgets.row;
}

static void
run_command (GSHCommandShell * this, const gchar * command)
{
  gchar *result;

  result = antiright_pipe_read (command);
  gtk_label_set_text (GTK_LABEL (this->widgets.output), result);
  g_free (result);
}

static void
run_command_cb (GtkWidget * widget __attribute__ ((unused)), gpointer data)
{
  GSHCommandShell *this;
  GtkEntry *entry;

  this = (GSHCommandShell *) data;
  entry = GTK_ENTRY (this->widgets.input);
  run_command (this, gtk_entry_get_text (entry));
  gtk_entry_set_text (entry, "");
}

static void
setup_command_shell_methods (GSHCommandShell * this)
{
  this->delete = &gsh_delete_GSHCommandShell;
  this->get = &get_command_shell;
  this->run = &run_command;
}

static void
set_output_label_options (GtkWidget * output)
{
  gtk_label_set_justify (GTK_LABEL (output), GTK_JUSTIFY_LEFT);
  gsh_widget_set_font (output, NULL);
  gtk_label_set_selectable (GTK_LABEL (output), TRUE);
}

static void
setup_output_scroller (GtkWidget * row, GtkWidget * output)
{
  GtkWidget *scroller;

  GSH_CREATE (scroller, scrolled_window, NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroller),
				  GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  GSHCA (row, scroller);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scroller),
					 output);
}

static void
setup_output_area (GSHCommandShell * this)
{
  GtkWidget *output;

  GSH_CREATE (this->widgets.output, label, NULL);
  output = this->widgets.output;
  set_output_label_options (output);
  setup_output_scroller (this->widgets.row, output);
}

static void
setup_command_shell_widgets (GSHCommandShell * this)
{
  this->widgets.row=gtk_vbox_new(0, FALSE);
  setup_output_area (this);
  this->widgets.input=gtk_entry_new();
  GSHCONNECT (this->widgets.input, "activate", run_command_cb, this);
  GSHCA_TIGHT (this->widgets.row, this->widgets.input);
}

static void
setup_command_shell (GSHCommandShell * this)
{
  setup_command_shell_methods (this);
  setup_command_shell_widgets (this);
}

GSHCommandShell *
gsh_new_GSHCommandShell ()
{
  GSHCommandShell *shell;

  shell = armalloc (sizeof (GSHCommandShell));
  setup_command_shell (shell);

  return shell;
}
#endif /* note HAVE_VTE */

