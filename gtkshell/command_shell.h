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

#ifndef GSH_CMDSHELL_H
#define GSH_CMDSHELL_H
#ifndef HAVE_VTE

struct GSHCommandShell {
	struct {
		GtkWidget *input;
		GtkWidget *output;
		GtkWidget *row;
	} widgets;
	void (*delete) (struct GSHCommandShell *);
	void (*run) (struct GSHCommandShell *, const gchar *);
	GtkWidget *(*get) (struct GSHCommandShell *);
};

typedef struct GSHCommandShell GSHCommandShell;

GSHCommandShell *gsh_new_GSHCommandShell();

#endif /* not HAVE_VTE */
#endif /* not GSH_CMDSHELL_H */
