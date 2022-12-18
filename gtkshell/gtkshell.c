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
  Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

static void delete_child_classes(GSH * gsh)
{
	ARDELETE(gsh->rows);
	ARDELETE(gsh->terminal);
	ARDELETE(gsh->update);
}

static void gsh_delete_GSH(GSH * gsh)
{
	/* Delete atomic members.  */
	GSH_FREE_IF(gsh->geometry);
	delete_child_classes(gsh);
	if (GSH_FLAG(GSH_HEAP_ALLOCATED))
		arfree(gsh);
}

static inline void manage_generic(GSH * gsh, GtkWidget * widget)
{
	gsh->rows->current++;
	gsh->widgets.last_managed = widget;
}

static void
manage_regular_widget(GSH * gsh, GtkWidget * container, GtkWidget * widget)
{
	manage_generic(gsh, widget);
	$(gsh->rows, check);
	if (G_UNLIKELY(GSH_FLAG(GSH_NO_EXPAND)))
		GSHCA_TIGHT(container, widget);
	else
		GSHCA(container, widget);
}

static void manage_in_current_pane(GSH * gsh, GtkWidget * widget)
{
	GtkWidget *container = gsh->rows->v;

	if (!(GTK_IS_MENU(container) || GTK_IS_MENU_BAR(container)
	      || GTK_IS_MENU_ITEM(container)))
		manage_regular_widget(gsh, container, widget);
	else
		gtk_menu_shell_append(GTK_MENU_SHELL(container), widget);
}

static void manage_in_other_pane(GSH * gsh, GtkWidget * widget)
{
	gsh_pane_previous(gsh, widget);
	manage_generic(gsh, widget);
}

static void gsh_manage(GSH * gsh, GtkWidget * widget)
{
	if (!GSH_FLAG(GSH_PANE_NEXT))
		manage_in_current_pane(gsh, widget);
	else
		manage_in_other_pane(gsh, widget);
}

static void assign_add_methods(GSH * gsh)
{
	gsh->add.window = &gsh_GSH_add_window;
	gsh->add.button = &gsh_add_button;
	gsh->add.label = &gsh_add_label;
}

static void assign_methods(GSH * gsh)
{
	/* setup methods */
	gsh->delete = &gsh_delete_GSH;
	gsh->parse = &gsh_parse_arguments;
	gsh->finalize = &gsh_GSH_finalize;
	gsh->manage = &gsh_manage;
	assign_add_methods(gsh);
}

static void initialize_app_mode_fields(GSH * gsh)
{
	/* setup app mode fields */
#define GWA gsh->widgets.app
	GWA.menubar = GWA.toolbar = GWA.status = GWA.frame = GWA.row = NULL;
#define GWAM GWA.menus
	GWAM.file = GWAM.edit = GWAM.view = GWAM.tools = GWAM.help = NULL;
}

static void initialize_fields(GSH * gsh)
{
	/* setup child classes */
	gsh->update = NULL;
	gsh->rows = ARNEW(gsh, GSHRows, gsh);
	gsh->terminal = NULL;
	/* initialize fields */
	gsh->widgets.last_managed = NULL;
	gsh->editor.widget = NULL;
	gsh->command_dictionary = NULL;
	gsh->editor.fgcolor = gsh->editor.bgcolor = gsh->editor.filename
	    = gsh->geometry = gsh->usage = (gchar *) NULL;
	gsh->bflags = 0;
	gsh->icon_size = GTK_ICON_SIZE_DND;
	initialize_app_mode_fields(gsh);
}

void gsh_GSH(GSH * gsh)
{
	assign_methods(gsh);
	initialize_fields(gsh);
	/* Add initial window.  */
	$(gsh, add.window);
}

GSH *gsh_new_GSH()
{
	GSH *gsh;

	gsh = (GSH *) armalloc(sizeof(GSH));
	gsh_GSH(gsh);
	GSH_SET(GSH_HEAP_ALLOCATED);

	return gsh;
}
