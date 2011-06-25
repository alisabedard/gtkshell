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

static gdouble
get_command_val (const gchar * command)
{
  gchar *output;
  gdouble result;

  output=antiright_pipe_read(command);
  result=g_strtod(output, NULL);
  g_free(output);
  if(result>1)
    result=1;

  return result;
}

static void
gsh_update_progress (const gchar * command, gpointer widget)
{
  gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (widget), 
                                 get_command_val(command));
}

void
gsh_add_updated_progress (struct GSH *gsh, const gchar * command)
{
  GtkWidget *progress;

  $ (gsh, manage, progress = gtk_progress_bar_new ());
  GSH_NEW_UPDATER_WITH_COMMAND (gsh, gsh_update_progress, progress, command);
}

