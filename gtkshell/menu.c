/*
  GUIShell
  (c) 2006-2010 Alisa Bedard
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

#define SPLIT_ALL -1

static void parse_special_and_noicon_items(GSH * gsh, gchar ** pair)
{
	/* Test if a separator should be created.  */
	if (!strncmp(pair[0], "---", 3)) {
		GtkWidget *separator;

		GSH_ADD_WIDGET(gsh->rows->v, separator, separator_menu_item);
	}
	/* String does not contain \n.  */
	else if (strncmp(pair[0], "\\n", 2)) {
		/* Support continuation lines for menu specification.  */
		/* Create a button.  */
		$(gsh, add.button, pair[0]);
	}
}

static void menuitem_parse(struct GSH *gsh, gchar * string)
{
	gchar **pair;

	pair = g_strsplit(string, ",", 2);
	if (pair[1])
		gsh_image_button(gsh, pair[0], pair[1]);
	else
		parse_special_and_noicon_items(gsh, pair);
	g_strfreev(pair);
}

static void set_submenu_label(gpointer widget, gpointer user_data)
{
	if (GTK_IS_LABEL((GtkWidget *) widget))
		gtk_label_set_text(GTK_LABEL((GtkWidget *) widget),
				   (const gchar *)user_data);
}

static void
find_and_set_compound_label_widget(GtkWidget * label, const gchar * label_text)
{
	GList *children;

	children = gtk_container_get_children(GTK_CONTAINER(label));
	g_list_foreach(children, set_submenu_label, (gchar *) label_text);
	g_list_free(children);
}

static void find_and_set_label_widget(GtkWidget * label, const gchar * command)
{
	gchar *label_text;
	gchar *tmp = g_strdup(command);

	label_text = antiright_beautified_label(tmp);
	g_free(tmp);
	if (GTK_IS_LABEL(label))
		set_submenu_label(label, label_text);
	else
		find_and_set_compound_label_widget(label, label_text);
	g_free(label_text);
}

void gsh_add_tearoff(GtkWidget * submenu)
{
	gtk_menu_shell_prepend(GTK_MENU_SHELL(submenu),
			       gtk_tearoff_menu_item_new());
}

static void
begin_submenu(GSH * gsh, GtkWidget ** submenus,
	      guint * submenu_count, guint * i, gchar ** tokens)
{
	GtkWidget *menu_button = gsh->widgets.button;

	GSH_UNSET(GSH_MENU_BUTTON);
	submenus[(*submenu_count)++] = gsh->rows->v;
	{
		GtkWidget *submenu;

		submenu = gsh->rows->v = gtk_menu_new();
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_button), submenu);
		gsh_add_tearoff(submenu);
	}
	find_and_set_label_widget(GSH_GET_CHILD(menu_button), tokens[++(*i)]);
}

static void
parse_submenu_or_item_specification(GSH * gsh, gchar ** tokens,
				    guint * submenu_count,
				    GtkWidget ** submenus,
				    const guint max_menus, guint * i)
{
	const gchar *submenu_open = "-->";
	const gboolean start_submenu = (!strncmp(tokens[*i],
						 submenu_open, 3)
					&& *submenu_count < max_menus);

	if (start_submenu)
		GSH_SET(GSH_MENU_BUTTON);
	/* Create the menu item.  */
	menuitem_parse(gsh, tokens[*i]);
	if (start_submenu)
		begin_submenu(gsh, submenus, submenu_count, i, tokens);
}

static void perform_addition_for_each_item(struct GSH *gsh, gchar ** tokens)
{
	guint i = 0;
	const guint max_menus = 6;
	/* Any more is not practical.  */
	GtkWidget *submenus[max_menus];
	guint submenu_count = 0;

	while (tokens[++i]) {
		const gchar *submenu_close = "<--";

		if (!strncmp(tokens[i], submenu_close, 3)) {
			if (submenu_count)
				gsh->rows->v = submenus[--submenu_count];
		} else
			parse_submenu_or_item_specification(gsh, tokens,
							    &submenu_count,
							    submenus, max_menus,
							    &i);
	}
}

static void add_menu_items(struct GSH *gsh, GtkWidget * menu, gchar ** tokens)
{
#define GSHR gsh->rows
	/* Set gsh->rows->v to a row within a menu.
	 * Create the menu before overwriting, then
	 * set back at end.  */
	const GtkWidget *old_row = gsh->rows->v;

	GSHR->v = menu;
	perform_addition_for_each_item(gsh, tokens);
	GSHR->v = (GtkWidget *) old_row;
}

static GtkWidget *add_menu_bar(struct GSH *gsh)
{
#define GWA gsh->widgets.app
	if (!GWA.menubar) {
		GSH_CREATE(GWA.menubar, menu_bar);
		GSH_FLAG(GSH_APP_MODE) ? gsh_setup_app_mode(gsh)
		    : $(gsh, manage, GWA.menubar);
	}

	return GWA.menubar;
}

GSHMenuType gsh_is_menubar_item(const gchar * label)
{
#define MENTEST(key, value) if(!strncmp(label, key, 2)) return value;
	MENTEST("File", GMT_FILE);
	MENTEST("Edit", GMT_EDIT);
	MENTEST("Tools", GMT_TOOLS);
	MENTEST("View", GMT_VIEW);
	MENTEST("Help", GMT_HELP);

	return GMT_NONE;
}

static void
test_for_main_app_menus(GSH * gsh, GtkWidget * menu, const gchar * label)
{
#define GSHMENUS GWA.menus
	switch (gsh_is_menubar_item(label)) {
	case GMT_FILE:
		GSHMENUS.file = menu;
		break;
	case GMT_EDIT:
		GSHMENUS.edit = menu;
		break;
	case GMT_VIEW:
		GSHMENUS.view = menu;
		break;
	case GMT_TOOLS:
		GSHMENUS.tools = menu;
		break;
	case GMT_HELP:
		GSHMENUS.help = menu;
		break;
	default:
		break;
	}
}

static GtkWidget *add_menu_launcher(struct GSH *gsh, const gchar * label)
{
	const GtkWidget *old_row = gsh->rows->v;
	GtkWidget *menu_item;

	gsh->rows->v = add_menu_bar(gsh);
	GSH_SET(GSH_MENU_BUTTON);
	menu_item = $(gsh, add.button, label);
	gtk_widget_show(menu_item);
	gsh->rows->v = (GtkWidget *) old_row;

	return menu_item;
}

void gsh_menubutton_parse(struct GSH *gsh, gchar ** tokens)
{
	GtkWidget *menu;
	const gchar *label;

	label = tokens[0];
	GSH_CREATE(menu, menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(add_menu_launcher(gsh,
								  label)),
				  menu);
	add_menu_items(gsh, menu, tokens);
	test_for_main_app_menus(gsh, menu, label);
}
