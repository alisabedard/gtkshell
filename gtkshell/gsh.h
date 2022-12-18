/*
  GUIShell
  (c) 2002-2010 Alisa Bedard
  alisabedard@gmail.com

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
#ifndef GSH_GSH_H
#define GSH_GSH_H

#include "terminal_struct.h"

struct GSH {
	/* member data */
	/*@null@ */ gchar *geometry;
	Bitmask bflags;
	GtkIconSize icon_size;

	/* member data categories */
	struct {		/* widgets */
		GtkWidget *window;
		GtkWidget *scrolled_window;
		GtkWidget *button;
		GtkWidget *last_managed;
		struct {	/* app mode */
			struct {	/* menus */
				GtkWidget *file;
				GtkWidget *edit;
				GtkWidget *tools;
				GtkWidget *view;
				GtkWidget *help;
			} menus;
			GtkWidget *menubar;
			GtkWidget *toolbar;
			GtkWidget *status;
			GtkWidget *frame;
			GtkWidget *row;
		} app;
	} widgets;

	struct {		/* text editor */
		gchar *filename;
		GtkWidget *widget;
		gchar *bgcolor;
		gchar *fgcolor;
	} editor;

	/* member classes */
	struct GSHRows *rows;
	struct GSHUpdateManager *update;
	struct GSHTerminal *terminal;

	ARTupleVector *command_dictionary;
	gchar *usage;

	/* methods */
	void (*delete) (struct GSH *);
	void (*parse) (struct GSH *, const gint, const gchar **);
	void (*finalize) (struct GSH *);
	void (*manage) (struct GSH *, GtkWidget *);

	/* method categories */
	struct {
		GtkWidget *(*window) (struct GSH *);
		GtkWidget *(*button) (struct GSH *, const gchar *);
		GtkWidget *(*label) (struct GSH *, const gchar *);
	} add;

};

typedef struct GSH GSH;

#endif /* GSH_GSH_H */
