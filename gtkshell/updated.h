/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
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

#ifndef GSH_UPDATED_H
#define GSH_UPDATED_H

struct GSHUpdatedWidget {
	GtkWidget *widget;
	gchar *command;
	void (*function) (const gchar *, gpointer);
	void (*update) (struct GSHUpdatedWidget *);
	void (*delete) (struct GSHUpdatedWidget *);
};

struct GSHUpdatedWidget
*gsh_new_GSHUpdatedWidget(void (*function) (const gchar *, gpointer),
			  const gchar * command, GtkWidget * widget);

#define GSH_NEW_UPDATER_WITH_COMMAND(gsh, function, widget, command)\
  if(!(gsh->update)) gsh->update=ARNEW(gsh, GSHUpdateManager);\
	$(gsh->update, add, ARNEW(gsh, GSHUpdatedWidget,\
		&function, command, widget))

#define GSH_NEW_UPDATER(gsh, function, widget)\
	GSH_NEW_UPDATER_WITH_COMMAND(gsh, function, widget, NULL)

#endif /* !GSH_UPDATED_H */
