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

#include "gtkshell.h"

static void
test_checked(gpointer element_data, gpointer user_data __attribute__ ((unused)))
{
	GtkWidget *radio_button;

	radio_button = (GtkWidget *) element_data;
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button)))
		puts(gtk_button_get_label(GTK_BUTTON(radio_button)));
}

static void
submit_cb(GtkWidget * button __attribute__ ((unused)), gpointer cb_data)
{
	GtkWidget *radio_base = (GtkWidget *) cb_data;
	GSList *radio_group;

	radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_base));
	g_slist_foreach(radio_group, test_checked, NULL);
	exit(0);
}

static void setup_controls(GtkWidget * vertical, GtkWidget * radio_base)
{
	GtkWidget *controls;
	GtkWidget *button;

	controls = gtk_hbox_new(TRUE, 2);
	button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
	GSHCONNECT(button, "clicked", gtk_main_quit, NULL);
	GSHCA(controls, button);
	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	GSHCONNECT(button, "clicked", submit_cb, radio_base);
	GSHCA(controls, button);
	GSHCA(vertical, controls);
}

static GtkWidget *setup_contents(const gchar * contents, GtkWidget * vertical)
{
	GtkWidget *radio_base;
	gchar **element;
	unsigned int counter;

	element = g_strsplit(contents, ",", -1);
	assert(element[0]);
	radio_base = gtk_radio_button_new_with_label(NULL, element[0]);
	GSHCA(vertical, radio_base);
	for (counter = 1; element[counter]; counter++) {
		GtkWidget *radio;

		radio =
		    gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON
								(radio_base),
								element
								[counter]);
		GSHCA(vertical, radio);
	}

	return radio_base;
}

void gsh_add_form(GSH * gsh, const gchar * contents)
{
	GtkWidget *vertical;
	GtkWidget *radio_base;

	vertical = gtk_vbox_new(TRUE, 1);
	radio_base = setup_contents(contents, vertical);
	setup_controls(vertical, radio_base);
	$(gsh, manage, vertical);
}
