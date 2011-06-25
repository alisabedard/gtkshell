/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
  antiright@gmail.com

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
#include "undo.h"

static void setup_undo (GSH * gsh);


static void
setup_entry_cb (struct GSH *gsh, GtkWidget * entry, const gchar * command)
{
  struct GSHCBData *cb;

  if (gsh && entry && command)
    {
      cb = ARNEW (gsh, GSHCBData, gsh, (gpointer)(command ? command : "echo"));
      GSHCONNECT(gtk_bin_get_child(GTK_BIN(entry)), "activate", cb->entry, cb);
    }
}

GtkWidget *
gsh_setup_command_entry (struct GSH *gsh, const gchar * command)
{
  GtkWidget *entry;

  /* Create widget and assign callback.  */
  setup_entry_cb (gsh, entry = gtk_combo_box_entry_new_text (), command);
  $(gsh, manage, entry);

  return entry;
}

static void
set_options (GSH * gsh, GtkWidget * text_widget)
{
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (text_widget), GTK_WRAP_WORD);
  gsh_widget_set_font (text_widget, NULL);
  /* Set background color, if specified.  */
  if (gsh->editor.bgcolor)
      gsh_widget_set_color (text_widget, gsh->editor.bgcolor, FALSE);
  /* Set background color, if specified.  */
  if (gsh->editor.fgcolor) /* TRUE for foreground */
      gsh_widget_set_color (text_widget, gsh->editor.fgcolor, TRUE);
}


static void
setup_text_scroller (GSH * gsh, GtkWidget * text)
{
  GtkWidget *scroller;

  GSH_ADD_MANAGED(gsh, scroller, scrolled_window, NULL, NULL);
  GSHCA (scroller, text);
}

GtkWidget *
gsh_text_area (GSH *gsh)
{
  GtkWidget *text;

  GSH_CREATE (text = gsh->editor.widget, text_view);
  set_options (gsh, text);
  setup_text_scroller (gsh, text);
  setup_undo (gsh);
  if(!(gsh->geometry))
    gsh->geometry=g_strdup("640x389");

  return text;
}

GtkTextBuffer *
gsh_text_area_set_text (GtkWidget * widget, const gchar * text)
{
  GtkTextBuffer *buffer;

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widget));
  gtk_text_buffer_set_text (buffer, text, strlen (text));

  return buffer;
}

static GtkWidget *
setup_unredo_button(GtkWidget *destination, const bool has_toolbar,
                  const gchar *stock, GCallback cb, GtkWidget * text_widget)
{
  GtkWidget *button;

  button=has_toolbar 
    ? GSH_STOCK_ITEM(tool_button, stock) 
    : GSH_STOCK_ITEM(button, stock);
  GSHCA(destination, button);
  g_signal_connect_swapped (G_OBJECT (button), "clicked",
			    (GCallback) cb,
			    gtk_text_view_get_buffer (GTK_TEXT_VIEW
						      (text_widget)));

  return button;
}

static GtkWidget *
setup_toolbar (GSH *gsh)
{
  GtkWidget *toolbar, *expander;

  GSH_SET (GSH_NO_EXPAND);
  GSH_ADD_MANAGED (gsh, expander, expander, gsh->editor.filename);
  gtk_expander_set_spacing(GTK_EXPANDER(expander), 0);
  GSH_ADD_WIDGET (expander, toolbar, toolbar);
  gsh->widgets.app.toolbar=toolbar;

  return toolbar;
}

static void
setup_undo (GSH * gsh)
{
  GtkWidget *text_widget = gsh->editor.widget;
  GtkWidget *destination;
  GtkWidget *gsh_toolbar = gsh->widgets.app.toolbar;
  const bool has_toolbar=(gsh_toolbar);

  destination = has_toolbar ? gsh->widgets.app.toolbar : setup_toolbar(gsh);
  gsh_undo_init(text_widget, 
                setup_unredo_button(destination, has_toolbar, "gtk-undo", 
                                    (GCallback)gsh_undo_undo, text_widget), 
                setup_unredo_button(destination, has_toolbar, "gtk-redo", 
                                    (GCallback)gsh_undo_redo, text_widget));
}


/* Check that the editor widget has been initialized.  */
#define TEST_EDITOR_EXISTS(gsh)\
	if(!gsh->editor.widget)\
		return;
/* Text editor does not exist, so return.  */

static gchar *
get_text (GtkWidget * editor)
{
  GtkTextBuffer *buffer;
  GtkTextIter start, end;

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor));
  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);

  return gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
}

static void
save_to_opened_file (GSH * gsh)
{
  gchar *text;

  text = get_text (gsh->editor.widget);
  AR_TEXT_TO_FILE (gsh->editor.filename, text);
  g_free (text);
}

void
gsh_editor_save (struct GSH *gsh)
{
  TEST_EDITOR_EXISTS (gsh);
  /* Choose action based on whether or not file has been chosen. */
  if (gsh->editor.filename)
    save_to_opened_file (gsh);
  else
    gsh_editor_save_as (gsh);
}

#define PROMPT_FILENAME() antiright_pipe_read("gtkshell -df")
#define FILENAME_NOT_EMPTY strcmp(gsh->editor.filename, "")

static void
get_filename (struct GSH *gsh)
{
  gchar *tmp_filename;

  tmp_filename = g_strdup (gsh->editor.filename);
  /* Make sure that FILENAME is freed if previously used.  */
  if (gsh->editor.filename)
    g_free (gsh->editor.filename);
  /* Get the filename.  */
  gsh->editor.filename = PROMPT_FILENAME ();
  /* Restore filename if empty, in case of open file, so that
     file will not have to be reopened/reselected on save.  */
  if (!FILENAME_NOT_EMPTY)
    gsh->editor.filename = tmp_filename;
  else
    g_free (tmp_filename);
}

void
gsh_editor_save_as (struct GSH *gsh)
{
  TEST_EDITOR_EXISTS (gsh);
  get_filename (gsh);
  /* Make sure filename is not empty.  */
  if (FILENAME_NOT_EMPTY)
    gsh_editor_save (gsh);
}

static void
open_in_editor (GSH * gsh)
{
  if (gsh->editor.filename && FILENAME_NOT_EMPTY)
    {
      gchar *text;

      text = antiright_read_named_file (gsh->editor.filename);
      gsh_text_area_set_text (gsh->editor.widget, text);
      g_free (text);
    }
}

static void
recent_file_cb (GtkWidget * widget, gpointer data)
{
  GSH *gsh;

  gsh = (GSH *) data;
  if (gsh->editor.filename)
    g_free (gsh->editor.filename);
  gsh->editor.filename = g_strdup ((gchar *)
				   gtk_label_get_text (GTK_LABEL
						       (gtk_bin_get_child
							(GTK_BIN (widget)))));
  gsh_editor_save (gsh);
  open_in_editor (gsh);
}

static void
add_to_recent_files (GSH * gsh, const gchar * filename)
{
  GtkWidget *menu;

  if ((menu = gsh->widgets.app.menus.view))
    {
      GtkWidget *button;

      button = gtk_menu_item_new_with_label (filename);
      GSHCONNECT (button, "activate", recent_file_cb, gsh);
      gtk_widget_show (button);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), button);
    }
}

void
gsh_editor_open (struct GSH *gsh)
{
  TEST_EDITOR_EXISTS (gsh);
  get_filename (gsh);
  open_in_editor(gsh);
  add_to_recent_files (gsh, gsh->editor.filename);
}

void
gsh_text_editor (struct GSH *gsh, const gchar * filename)
{
  gsh_text_area (gsh);
  gsh->editor.filename = (gchar *) filename;
  open_in_editor (gsh);
}

