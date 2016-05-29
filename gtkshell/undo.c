/*
 *  Leafpad - GTK+ based simple text editor
 *  Copyright (C) 2004-2005 Tarot Osuji

	GUIShell - Copyright (C) 2007, Jeffrey Bedard

 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "gtkshell.h"
#include <gdk/gdkkeysyms.h>

#ifndef DEBUG
#define DV(x)
#else /* DEBUG */
#define DV(x) x
#endif /* ! DEBUG */

/* BEGIN -- view.c extracts */
static gint keyval;

#define SENSITIZE(widget) gtk_widget_set_sensitive(widget, TRUE);
#define DESENSITIZE(widget) gtk_widget_set_sensitive(widget, FALSE);

/* END - view.c extracts */

//"GTK_TEXT_VIEW(view)->overwrite_mode" can get overwrite_mode state

typedef struct {
	gchar command;
	gint start;
	gint end;
	bool seq;		// sequency flag
	gchar *str;
} UndoInfo;

enum {
	INS = 0,
	BS,
	DEL
};

static struct {
	struct {
		GtkWidget *undo;
		GtkWidget *redo;
		GtkTextView *text;
	} widgets;

	struct {
		GList *undo;
		GList *redo;
	} lists;

	struct {
		guint modified_step;
		guint prev_keyval;
		bool seq_reserve;
	} values;

	GString *undo_gstr;

	UndoInfo *ui_tmp;
} undo;

static inline void scroll_to_cursor(GtkTextBuffer * buffer)
{
	gtk_text_view_scroll_to_mark(undo.widgets.text,
				     gtk_text_buffer_get_insert(buffer),
				     0.05, FALSE, 0, 0);
}

static GList *undo_clear_info_list(GList * info_list)
{
	while (g_list_length(info_list)) {
		g_free(((UndoInfo *) info_list->data)->str);
		g_free(info_list->data);
		info_list = g_list_delete_link(info_list, info_list);
	}

	return info_list;
}

static void
undo_append_undo_info(const gchar command, gint start, gint end, gchar * str)
{
	UndoInfo *ui = g_malloc(sizeof(UndoInfo));

	ui->command = command;
	ui->start = start;
	ui->end = end;
	ui->seq = undo.values.seq_reserve;
	ui->str = str;

	undo.values.seq_reserve = FALSE;

	undo.lists.undo = g_list_append(undo.lists.undo, ui);
	DV(g_print("undo_cb: %d %s (%d-%d)\n", command, str, start, end));
}

static void undo_set_sequency(bool seq)
{
	if (g_list_length(undo.lists.undo))
		((UndoInfo *) g_list_last(undo.lists.undo)->data)->seq = seq;
	DV(g_print("<undo_set_sequency: %d>\n", seq));
}

static void
undo_create_undo_info(GtkTextBuffer * buffer, gchar command,
		      gint start, gint end)
{
	GtkTextIter start_iter, end_iter;
	bool seq_flag = FALSE;
	gchar *str;
	gint keyval = 0;

	gtk_text_buffer_get_iter_at_offset(buffer, &start_iter, start);
	gtk_text_buffer_get_iter_at_offset(buffer, &end_iter, end);
	str = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE);

	if (undo.undo_gstr->len) {
		if ((end - start == 1) && (command == undo.ui_tmp->command)) {
			switch (keyval) {
			case GDK_BackSpace:
				if (end == undo.ui_tmp->start)
					seq_flag = TRUE;
				break;
			case GDK_Delete:
				if (start == undo.ui_tmp->start)
					seq_flag = TRUE;
				break;
			case GDK_Tab:
			case GDK_space:
				if (start == undo.ui_tmp->end)
					seq_flag = TRUE;
				break;
			default:
				if ((undo.ui_tmp->end == start) && keyval
				    && keyval < 0xF000)
					switch (undo.values.prev_keyval) {
					case GDK_Return:
					case GDK_Tab:
					case GDK_space:
						break;
					default:
						seq_flag = TRUE;
					}
			}
		}
		if (seq_flag) {
			switch (command) {
			case BS:
				undo.undo_gstr =
				    g_string_prepend(undo.undo_gstr, str);
				undo.ui_tmp->start--;
				break;
			default:
				undo.undo_gstr =
				    g_string_append(undo.undo_gstr, str);
				undo.ui_tmp->end++;
			}
			undo.lists.redo = undo_clear_info_list(undo.lists.redo);
			undo.values.prev_keyval = keyval;
			SENSITIZE(undo.widgets.undo);
			DESENSITIZE(undo.widgets.redo);

			return;
		}
		undo_append_undo_info(undo.ui_tmp->command,
				      undo.ui_tmp->start, undo.ui_tmp->end,
				      g_strdup(undo.undo_gstr->str));
		undo.undo_gstr = g_string_erase(undo.undo_gstr, 0, -1);
	}

	if (!keyval && undo.values.prev_keyval)
		undo_set_sequency(TRUE);

	if (end - start == 1 && ((keyval && keyval < 0xF000)
				 || keyval == GDK_BackSpace
				 || keyval == GDK_Delete
				 || keyval == GDK_Tab)) {
		undo.ui_tmp->command = command;
		undo.ui_tmp->start = start;
		undo.ui_tmp->end = end;
		undo.undo_gstr = g_string_erase(undo.undo_gstr, 0, -1);
		g_string_append(undo.undo_gstr, str);
	} else
		undo_append_undo_info(command, start, end, g_strdup(str));

	undo.lists.redo = undo_clear_info_list(undo.lists.redo);
	undo.values.prev_keyval = keyval;
	keyval = 0;
	SENSITIZE(undo.widgets.undo);
	DESENSITIZE(undo.widgets.redo);
}

static void
cb_insert_text(GtkTextBuffer * buffer, GtkTextIter * iter, const gchar * str)
{
	gint start, end;

	DV(g_print("insert-text\n"));
	end = gtk_text_iter_get_offset(iter);
	start = end - g_utf8_strlen(str, -1);

	undo_create_undo_info(buffer, INS, start, end);
}

static void
cb_delete_range(GtkTextBuffer * buffer,
		GtkTextIter * start_iter, GtkTextIter * end_iter)
{
	gint start, end;
	gchar command;

	DV(g_print("delete-range\n"));
	start = gtk_text_iter_get_offset(start_iter);
	end = gtk_text_iter_get_offset(end_iter);

	if (keyval == GDK_BackSpace)
		command = BS;
	else
		command = DEL;
	undo_create_undo_info(buffer, command, start, end);
}

static void undo_check_modified_step(GtkTextBuffer * buffer)
{
	bool flag;

	flag = (undo.values.modified_step == g_list_length(undo.lists.undo));
	if (gtk_text_buffer_get_modified(buffer) == flag)
		gtk_text_buffer_set_modified(buffer, !flag);
}

static void cb_begin_user_action(GtkTextBuffer * buffer)
{
	g_signal_handlers_unblock_by_func(G_OBJECT(buffer),
					  G_CALLBACK(cb_insert_text), NULL);
	g_signal_handlers_unblock_by_func(G_OBJECT(buffer),
					  G_CALLBACK(cb_delete_range), NULL);
	DV(g_print("begin-user-action(unblock_func)"));
	DV(g_print(": keyval = 0x%X\n", keyval));
}

static void cb_end_user_action(GtkTextBuffer * buffer)
{
	g_signal_handlers_block_by_func(G_OBJECT(buffer),
					G_CALLBACK(cb_insert_text), NULL);
	g_signal_handlers_block_by_func(G_OBJECT(buffer),
					G_CALLBACK(cb_delete_range), NULL);
	DV(g_print("end-user-action(block_func)\n"));
}

static void undo_flush_temporal_buffer(void)
{
	if (undo.undo_gstr->len) {
		undo_append_undo_info(undo.ui_tmp->command,
				      undo.ui_tmp->start, undo.ui_tmp->end,
				      g_strdup(undo.undo_gstr->str));
		undo.undo_gstr = g_string_erase(undo.undo_gstr, 0, -1);
	}
}

static void setup_signals(GtkTextBuffer * buffer)
{
	g_signal_connect_after(G_OBJECT(buffer), "insert-text",
			       G_CALLBACK(cb_insert_text), NULL);
	g_signal_connect(G_OBJECT(buffer), "delete-range",
			 G_CALLBACK(cb_delete_range), NULL);
	g_signal_connect_after(G_OBJECT(buffer), "begin-user-action",
			       G_CALLBACK(cb_begin_user_action), NULL);
	g_signal_connect(G_OBJECT(buffer), "end-user-action",
			 G_CALLBACK(cb_end_user_action), NULL);
}

void
gsh_undo_init(GtkWidget * view,
	      GtkWidget * undo_button, GtkWidget * redo_button)
{
	GtkTextBuffer *buffer = GTK_TEXT_VIEW(view)->buffer;

	undo.widgets.undo = undo_button;
	undo.widgets.redo = redo_button;
	undo.lists.undo = NULL;
	undo.lists.redo = NULL;
	undo.widgets.text = GTK_TEXT_VIEW(view);
	undo.values.seq_reserve = FALSE;
	setup_signals(buffer);
	cb_end_user_action(buffer);

	undo.ui_tmp = g_malloc(sizeof(UndoInfo));
	undo.undo_gstr = g_string_new("");

	/* Clear undo history and state.  */
	undo.lists.undo = undo_clear_info_list(undo.lists.undo);
	undo.lists.redo = undo_clear_info_list(undo.lists.redo);
	/* Reset modified step.  */
	undo_flush_temporal_buffer();
	undo.values.modified_step = g_list_length(undo.lists.undo);
	/* Set widget receptiveness.  */
	DESENSITIZE(undo.widgets.undo);
	DESENSITIZE(undo.widgets.redo);

	undo.ui_tmp->command = INS;
	undo.undo_gstr = g_string_erase(undo.undo_gstr, 0, -1);
	undo.values.prev_keyval = 0;
}

void gsh_undo_undo(GtkTextBuffer * buffer)
{
	bool sentinel = FALSE;
	do {
		GtkTextIter start_iter, end_iter;
		UndoInfo *ui;

		sentinel = FALSE;
		undo_flush_temporal_buffer();
		if (g_list_length(undo.lists.undo)) {
			ui = g_list_last(undo.lists.undo)->data;
			gtk_text_buffer_get_iter_at_offset(buffer, &start_iter,
							   ui->start);
			if (ui->command == INS) {
				gtk_text_buffer_get_iter_at_offset(buffer,
								   &end_iter,
								   ui->end);
				gtk_text_buffer_delete(buffer, &start_iter,
						       &end_iter);
			} else {
				gtk_text_buffer_insert(buffer, &start_iter,
						       ui->str, -1);
			}
			undo.lists.redo = g_list_append(undo.lists.redo, ui);
			undo.lists.undo = g_list_delete_link(undo.lists.undo,
							     g_list_last
							     (undo.lists.undo));
			if (g_list_length(undo.lists.undo)) {
				if (((UndoInfo *) g_list_last(undo.lists.undo)->
				     data)->seq)
					sentinel = TRUE;
			} else
				DESENSITIZE(undo.widgets.undo);
			if (!sentinel) {
				SENSITIZE(undo.widgets.redo);
				if (ui->command == DEL)
					gtk_text_buffer_get_iter_at_offset
					    (buffer, &start_iter, ui->start);
				gtk_text_buffer_place_cursor(buffer,
							     &start_iter);
				scroll_to_cursor(buffer);
			}
		}
		if (!sentinel)
			undo_check_modified_step(buffer);
	}
	while (sentinel);
}

void gsh_undo_redo(GtkTextBuffer * buffer)
{
	bool sentinel = FALSE;

	do {
		GtkTextIter start_iter, end_iter;
		UndoInfo *ri;

		sentinel = FALSE;
		if (g_list_length(undo.lists.redo)) {
			ri = g_list_last(undo.lists.redo)->data;
			gtk_text_buffer_get_iter_at_offset(buffer, &start_iter,
							   ri->start);
			if (ri->command == INS) {
				gtk_text_buffer_insert(buffer, &start_iter,
						       ri->str, -1);
			} else {
				gtk_text_buffer_get_iter_at_offset(buffer,
								   &end_iter,
								   ri->end);
				gtk_text_buffer_delete(buffer, &start_iter,
						       &end_iter);
			}
			undo.lists.undo = g_list_append(undo.lists.undo, ri);
			undo.lists.redo = g_list_delete_link(undo.lists.redo,
							     g_list_last
							     (undo.lists.redo));
			DV(g_print
			   ("cb_edit_redo: undo left = %d, " "redo left = %d\n",
			    g_list_length(undo.lists.undo),
			    g_list_length(undo.lists.redo)));
			if (ri->seq) {
				undo_set_sequency(TRUE);
				sentinel = TRUE;
			} else {
				if (!g_list_length(undo.lists.redo))
					gtk_widget_set_sensitive(undo.widgets.
								 redo, FALSE);
				gtk_widget_set_sensitive(undo.widgets.undo,
							 TRUE);
				gtk_text_buffer_place_cursor(buffer,
							     &start_iter);
				scroll_to_cursor(buffer);
			}
		}
		if (!sentinel)
			undo_check_modified_step(buffer);
	}
	while (sentinel);
}
