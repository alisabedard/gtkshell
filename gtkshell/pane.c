/*
  GUIShell
  (c) 2002-2007 Alisa Bedard
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

void gsh_reparent_widget(GtkWidget * widget, GtkWidget * old, GtkWidget * new)
{
	g_object_ref(widget);
	gtk_container_remove(GTK_CONTAINER(old), widget);
	gtk_container_add(GTK_CONTAINER(new), widget);
	g_object_unref(widget);
}

#define REPARENT_TO(new) gsh_reparent_widget(gsh->rows->v, gsh->rows->h, new)

static void split_columns_for_pane(struct GSH *gsh, GtkWidget * pane)
{
	struct GSHRows *rows;

	rows = gsh->rows;
	$(rows, new);
	$(gsh, manage, pane);
	$(rows, new);
}

static GtkWidget *setup_pane_half(GSH * gsh, const gchar * label)
{
	GtkWidget *frame;

	frame = gtk_frame_new(label);
	REPARENT_TO(frame);

	return frame;
}

void gsh_setup_hpaned(struct GSH *gsh, const gchar * label_pair)
{
	GtkWidget *pane;

	pane = gtk_hpaned_new();
	{
		gchar **pair;

		pair = g_strsplit(label_pair, ",", 2);
		/* assign pane sections */
		gtk_paned_add1(GTK_PANED(pane),
			       setup_pane_half(gsh, (const gchar *)pair[0]));
		split_columns_for_pane(gsh, pane);
		gtk_paned_add2(GTK_PANED(pane),
			       setup_pane_half(gsh, (const gchar *)pair[1]));
		g_strfreev(pair);
	}
}

void gsh_pane_previous(struct GSH *gsh, GtkWidget * target)
{
	GtkWidget *pane;
	GtkWidget *prev_frame;

	pane = gtk_vpaned_new();
	prev_frame = gtk_frame_new(NULL);
	gsh_reparent_widget(gsh->widgets.last_managed, gsh->rows->v,
			    prev_frame);
	gtk_paned_add1(GTK_PANED(pane), prev_frame);
	gtk_paned_add2(GTK_PANED(pane), target);
	GSH_UNSET(GSH_PANE_NEXT);
	$(gsh, manage, pane);
}
