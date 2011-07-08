/*
  GUIShell
  (c) 2002-2010 Jeffrey Bedard
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


#ifndef GSH_DIALOG_H
#define GSH_DIALOG_H

void
gsh_common_dialog_executioner (GSH * gsh, GtkWidget * dialog,
			       void (*callback) (GtkWidget *));

void gsh_file_dialog_submit (GtkWidget * dialog);

void gsh_font_dialog_submit (GtkWidget * dialog);

void gsh_color_dialog_submit (GtkWidget * dialog);

#define GSH_MESSAGE_DIALOG(gsh, type, text)\
	gsh_common_dialog_executioner(gsh, gtk_message_dialog_new(\
		GTK_WINDOW(gsh->widgets.window),\
                GTK_DIALOG_DESTROY_WITH_PARENT,\
		type, GTK_BUTTONS_OK, "%s", (gchar *) text), NULL)

#endif /* GSH_DIALOG_H */
