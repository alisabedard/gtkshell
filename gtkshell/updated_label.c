/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
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
gsh_update_label (const gchar * command, gpointer widget)
{
  gchar *results;

  results = antiright_pipe_read (command);
  /* This ensures that the result string is not empty, avoiding
   * certain formatting problems.
   * Otherwise, a GTK warning and termination occurs.  */
  if (results[0] == '\0')
    {
      g_free (results);
      results = g_strdup ("(empty)");
    }
  if (GTK_IS_LABEL (widget))
    gtk_label_set_markup (GTK_LABEL (widget), results);
  else if (GTK_IS_STATUSBAR (widget))
    gtk_statusbar_push (GTK_STATUSBAR (widget),
			gtk_statusbar_get_context_id (GTK_STATUSBAR (widget),
						      "updater"), results);
  g_free (results);
}

void
gsh_add_updated_label (struct GSH *gsh, const gchar * command)
{
  GtkWidget *update_target;

#define GSH_STATUS_WIDGET gsh->widgets.app.status
  if (!(GSH_FLAG (GSH_APP_MODE) && (update_target = GSH_STATUS_WIDGET)))
    update_target = gsh_add_label (gsh, (char *) command);
  GSH_NEW_UPDATER_WITH_COMMAND (gsh, gsh_update_label,
				update_target, command);
  GSH_UNSET (GSH_APP_MODE);
  /* Prevent two updaters from being 
     assigned to the status bar label.  */
  GSH_STATUS_WIDGET = NULL;
}
