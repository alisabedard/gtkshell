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
#include <glib/gstdio.h>

static void setup_label(GtkWidget * widget, const gchar * command)
{
	gchar *formatted = antiright_beautified_label(command);
	if (GTK_IS_MENU_ITEM(widget)) {
		GtkWidget *label;

		GSH_ADD_WIDGET(widget, label, label, formatted);
		gtk_misc_set_alignment(GTK_MISC(label), 0, 0);
	} else
		gtk_button_set_label(GTK_BUTTON(widget), formatted);
	g_free(formatted);
}

static void
setup_callback(struct GSH *gsh, GtkWidget * button, const gchar * command)
{
	if (!GSH_FLAG(GSH_MENU_BUTTON)) {
		struct GSHCBData *cb;

		cb = ARNEW(gsh, GSHCBData, gsh, g_strdup(command));
		GSHSETCB(button, cb->system, cb);
	} else
		GSH_UNSET(GSH_MENU_BUTTON);
}

static GtkWidget *label_to_icon_translation(const gchar * label)
{
	GtkWidget *image = NULL;
	struct {
		const gchar *label;
		const gchar *icon;
	} mapping[] = GSH_LABEL_TO_ICON_MAPPINGS;
	const guint mapping_size = sizeof(mapping) / sizeof(mapping[0]);
	guint mapping_count;

	for (mapping_count = 0; mapping_count < mapping_size; mapping_count++) {
		if (!strncmp(mapping[mapping_count].label,
			     g_strstrip((gchar *) label), 2)) {
			image = gsh_get_image(mapping[mapping_count].icon,
					      GTK_ICON_SIZE_BUTTON);
			gtk_widget_set_tooltip_text(image, label);
			break;
		}
	}
	return image;
}

static bool
setup_icon_for_toolbutton(GtkWidget * toolbutton, gchar * label_text)
{
	GtkWidget *icon;

	icon = label_to_icon_translation(label_text);
	if (icon) {
		gtk_button_set_image(GTK_BUTTON(toolbutton), icon);
		return TRUE;
	} else
		return FALSE;
}

static void
setup_label_for_toolbutton(GtkWidget * toolbutton, const gchar * command)
{
	gchar *label_text = antiright_beautified_label((gchar *) command);
	gtk_button_set_label(GTK_BUTTON(toolbutton),
			     (setup_icon_for_toolbutton(toolbutton, label_text)
			      && (gsh_is_menubar_item(label_text) == GMT_NONE))
			     ? "" : label_text);
	g_free(label_text);
}

static void setup_common(GSH * gsh, GtkWidget * button, const gchar * command)
{
	gsh_setup_drag_drop(gsh, button);
	setup_callback(gsh, button, command);
}

static void
setup_toolbutton_from_command_button(GSH * gsh, const gchar * command)
{
	GtkWidget *toolitem;
	GtkWidget *toolbutton;

	GSH_ADD_WIDGET(gsh->widgets.app.toolbar, toolitem, tool_item)
	    GSH_ADD_WIDGET(toolitem, toolbutton, button);
	setup_label_for_toolbutton(toolbutton, command);
	setup_common(gsh, toolbutton, command);
	gtk_button_set_relief(GTK_BUTTON(toolbutton), GTK_RELIEF_NONE);
}

static bool is_toolbutton(GSH * gsh, const gchar * command)
{
	return (GSH_FLAG(GSH_APP_MODE)
		&& gsh->widgets.app.toolbar
		&& GTK_IS_MENU_ITEM(gsh->widgets.button)
		&& (gsh_is_menubar_item(command) == GMT_NONE));
}

static bool is_image_button(GSH * gsh, const gchar * command)
{
	bool ret;
	gchar **pair = g_strsplit(command, ",", 2);

	if ((ret = pair[1]))
		gsh_image_button(gsh, pair[0], pair[1]);
	g_strfreev(pair);

	return ret;
}

/* This is just a wrapper around gsh_new_button(), to
   follow the convention of returning a created widget.  */
GtkWidget *gsh_add_button(struct GSH * gsh, const gchar * command)
{
	if (!is_image_button(gsh, command)) {
		GtkWidget *button;
		{
			GtkWidget *vrow = gsh->rows->v;

			button = gsh->widgets.button
			    = (!GTK_IS_MENU(vrow) && !GTK_IS_MENU_BAR(vrow))
			    ? gtk_button_new() : gtk_image_menu_item_new();
		}
		setup_label(button = gsh->widgets.button, command);
		gsh_setup_drag_drop(gsh, button);
		setup_callback(gsh, button, command);
		if (is_toolbutton(gsh, command))
			setup_toolbutton_from_command_button(gsh, command);
		/* Set button widget options.  */
		if (GTK_IS_BUTTON(button))
			gtk_button_set_alignment(GTK_BUTTON(button), 0.0, 0.5);
		$(gsh, manage, button);
	}
	return gsh->widgets.button;
}
