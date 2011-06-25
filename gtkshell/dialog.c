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

#include "gtkshell.h"

void
gsh_common_dialog_executioner (GSH * gsh, GtkWidget * dialog,
			       void (*callback) (GtkWidget *))
{
  const gint response = gtk_dialog_run (GTK_DIALOG (dialog));
  if (((response == GTK_RESPONSE_OK) || (response == GTK_RESPONSE_ACCEPT))
      && callback)
    callback (dialog);
  if (!GSH_FLAG (GSH_IN_SECONDARY_WIN))
    exit (0);
}

void
gsh_file_dialog_submit (GtkWidget * dialog)
{
  gchar *name;

  name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
  g_print ("%s\n", name);
  g_free (name);
}

void
gsh_font_dialog_submit (GtkWidget * dialog)
{
  gchar *font;

  font =
    gtk_font_selection_dialog_get_font_name (GTK_FONT_SELECTION_DIALOG
					     (dialog));
  g_print ("%s\n", font);
  g_free (font);
}

void
gsh_color_dialog_submit (GtkWidget * dialog)
{
  GdkColor color;

  gtk_color_selection_get_current_color (GTK_COLOR_SELECTION
					 (GTK_COLOR_SELECTION_DIALOG
					  (dialog)->colorsel), &color);
  /* Display the selected color on the command line in HTML
     hexidecimal format.  */
  g_print ("#%x%x%x\n", color.red, color.green, color.blue);
}

