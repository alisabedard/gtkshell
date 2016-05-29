/*
 GUIShell (c) 2007 Jeffrey Bedard jefbed@gmail.com

 This file is part of GUIShell.

 GUIShell is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free
 Software Foundation; either version 2 of the License, or (at your option)
 any later version.

 GUIShell is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 GUIShell; if not, write to the Free Software Foundation, Inc., 51 Franklin
 Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

/*
 * Portions Copyright 2005 Ryan McDougall, GNU GPL terms. Based on drag
 * and drop tutorial: http://live.gnome.org/GnomeLove/DragNDropTutorial
 */

enum {
	TARGET_STRING
};

static GtkTargetEntry target_list[] = {
	{(gchar *) "text/plain", 0, TARGET_STRING}
};

static void
drag_received(GtkWidget * widget, GdkDragContext * context,
	      gint x __attribute__ ((unused)),
	      gint y __attribute__ ((unused)),
	      GtkSelectionData * selection, guint target_type, guint time,
	      gpointer data __attribute__ ((unused)))
{
	bool drag_status;

	switch (target_type) {
	case TARGET_STRING:
		sysprintf("%s %s",
			  (const gchar *)
			  gtk_button_get_label(GTK_BUTTON(widget)),
			  (gchar *) selection->data);
		drag_status = TRUE;
		break;
	default:
		drag_status = FALSE;
		ARWARN("invalid data dropped");
	}

	gtk_drag_finish(context, drag_status, FALSE, time);
}

static bool
drag_drop(GtkWidget * widget, GdkDragContext * context,
	  gint x __attribute__ ((unused)),
	  gint y __attribute__ ((unused)),
	  guint time, gpointer data __attribute__ ((unused)))
{
	GdkAtom target_type;

	target_type =
	    GDK_POINTER_TO_ATOM(g_list_nth_data
				(context->targets, TARGET_STRING));

	if (context->targets) {
		gtk_drag_get_data(widget, context, target_type, time);
		return TRUE;
	} else
		return FALSE;
}

static void
drag_data_get(GtkWidget * widget,
	      GdkDragContext * context __attribute__ ((unused)),
	      GtkSelectionData * selection,
	      guint target_type __attribute__ ((unused)),
	      guint time __attribute__ ((unused)),
	      gpointer data __attribute__ ((unused)))
{
	const gchar *source_data;

	source_data = gtk_button_get_label(GTK_BUTTON(widget));
	gtk_selection_data_set(selection, selection->target, sizeof(gchar),
			       (guchar *) source_data, strlen(source_data));
}

void gsh_setup_drag_drop(struct GSH *gsh, GtkWidget * widget)
{
	const guint n_targets = G_N_ELEMENTS(target_list);

	gtk_drag_dest_set(widget, GTK_DEST_DEFAULT_MOTION
			  | GTK_DEST_DEFAULT_HIGHLIGHT, target_list, n_targets,
			  GDK_ACTION_COPY);

	gtk_drag_source_set(widget, GDK_BUTTON1_MASK, target_list, n_targets,
			    GDK_ACTION_COPY);

#define DND_SIGNAL(sig, func) \
	(void) g_signal_connect(widget, sig, G_CALLBACK(func), NULL)

	DND_SIGNAL("drag-data-received", drag_received);
	DND_SIGNAL("drag-drop", drag_drop);
	DND_SIGNAL("drag-data-get", drag_data_get);

	if (GSH_FLAG(GSH_CBEXIT))
		DND_SIGNAL("drag-end", gtk_main_quit);
}
