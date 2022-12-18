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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

static void set_options(struct GSH *gsh, GtkWidget * label)
{
#define GLS(attr, ...) gtk_label_set_##attr(GTK_LABEL(label), __VA_ARGS__)
	GLS(single_line_mode, FALSE);
	GSH_FLAG(GSH_HORIZONTAL_LABELS) ?
	    GLS(angle, 90.0) : GLS(line_wrap, TRUE);
	GLS(max_width_chars, 120);
	gsh_widget_set_font(label, NULL);
}

static GtkWidget *make_framed_label(GtkWidget * label)
{
	GtkWidget *frame;

	frame = gtk_frame_new(NULL);
	GSHCA(frame, label);
	gtk_widget_show(label);

	return frame;
}

GtkWidget *gsh_add_label(struct GSH * gsh, const gchar * text)
{
	GtkWidget *label;

	label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label), text);
	set_options(gsh, label);
	$(gsh, manage, GSH_FLAG(GSH_FRAMED_LABELS)
	  ? make_framed_label(label) : label);

	return label;
}
