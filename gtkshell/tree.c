/*
  gtkshell
  (c) 2002-2011 Jeffrey Bedard
  jefbed@gmail.com

  This file is part of gtkshell.

  gtkshell is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  gtkshell is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with gtkshell; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

enum
{
  KEY_COLUMN,
  VALUE_COLUMN,
  COLUMN_COUNT
};

static void
add_item (GtkListStore * store, GtkTreeIter * iter,
	  const gchar * key, const gchar * value)
{
  gtk_list_store_append (store, iter);
  gtk_list_store_set (store, iter, KEY_COLUMN, key, VALUE_COLUMN, value, -1);
}

static void
split_and_add_pair (gchar * pair, GtkTreeIter * iter, GtkListStore * store)
{
  gchar **split_pair;

  /* Use colon-separated key-value pair.  */
  if ((split_pair = g_strsplit (pair, ":", 2)))
    {
      add_item (store, iter,
		(const gchar *) split_pair[0], (const gchar *) split_pair[1]);
      /* Free allocated string array.  */
      g_strfreev (split_pair);
    }
  else				/* Allocation was not successful.  */
    {
      ARWARN ("split_pair NULL");
    }
}

static void
parse_input (const gchar * input, GtkListStore * store)
{
  GtkTreeIter iter;
  gchar **pairs;
  guint counter;

  for (counter = 0, pairs = g_strsplit (input, ",", -1);
       pairs[counter]; counter++)
    split_and_add_pair (pairs[counter], &iter, store);
  g_strfreev (pairs);
}

static GtkTreeModel *
setup_model (const gchar * input)
{
  GtkListStore *store;

  store = gtk_list_store_new (COLUMN_COUNT, G_TYPE_STRING, G_TYPE_STRING);
  parse_input (input, store);

  return GTK_TREE_MODEL (store);
}

#define ADD_COLUMN(view, name, id)\
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),\
		-1, name, renderer, "text", id, NULL)

static void
selection_handler (GtkTreeSelection * selection, gpointer data)
{
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *key;
  GSH * gsh = (GSH*)data;

  gtk_tree_selection_get_selected (selection, &model, &iter);
  gtk_tree_model_get (model, &iter, KEY_COLUMN, &key, -1);
  puts (key);
  if(GSH_FLAG(GSH_CBEXIT))
	  exit(0);
}

static void
setup_signals (GSH * gsh, GtkWidget * tree_view)
{
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view));
  gtk_tree_selection_set_mode (selection, GTK_SELECTION_SINGLE);
  g_signal_connect (G_OBJECT (selection), "changed",
		    G_CALLBACK (selection_handler), gsh);
}

GtkWidget *
gsh_tree_view_new (GSH * gsh, const gchar * input)
{
  GtkTreeModel *model;
  GtkCellRenderer *renderer;
  GtkWidget *view;

  model = setup_model (input);
  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();
  ADD_COLUMN (view, "KEY", KEY_COLUMN);
  ADD_COLUMN (view, "VALUE", VALUE_COLUMN);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model);
  setup_signals (gsh, view);

  return view;
}
