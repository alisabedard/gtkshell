/*
   GUIShell
   (c) 2007 Jeffrey Bedard
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

#include "gtkshell.h"

static void
setup_quit_signals (GtkWindow * window)
{
  g_signal_connect (window, "delete-event", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}


GtkWidget *
gsh_GSH_add_window (struct GSH *gsh)
{
  GtkWidget *window;

  window = gsh->widgets.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  setup_quit_signals (GTK_WINDOW (window));

  return window;
}

static void
focus_on_terminal_widget(GSHTerminal *term)
{
  if(term)
    {
      GtkNotebook *notebook;

      notebook = GTK_NOTEBOOK(term->__notebook);
      gtk_widget_grab_focus( gtk_notebook_get_nth_page 
                            (notebook, 
                             gtk_notebook_get_current_page(notebook)));
    }
}

void
gsh_GSH_finalize (struct GSH *gsh)
{
  /* free command line usage string if it has been set up */
  if (gsh->usage)
    g_free (gsh->usage);
  /* Choose the correct parenting of the widget hierarchy based on options
   * set.  */
  gsh_setup_base_container (gsh);
  /* If geometry has been set in command line arguments, use that, else
   * use a reasonable default.  */
  gsh_check_and_set_geometry (gsh);
  if(gsh->command_dictionary)
    $(gsh->command_dictionary, delete);
  focus_on_terminal_widget(gsh->terminal);
  /* Show everything when ready.  */
  gtk_widget_show_all(gsh->widgets.window);
}

