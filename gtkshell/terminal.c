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

/*#include <vte/reaper.h>*/

#ifdef HAVE_VTE
static void
set_terminal_options (GSHTerminal *term)
{
  GSH *gsh;
  VteTerminal *widget = (VteTerminal *)term->widget;
#define VSETW(element, ...)\
	vte_terminal_set_##element(widget, __VA_ARGS__)
  VSETW (size, term->dimensions.width, term->dimensions.height);
  VSETW (allow_bold, TRUE);
  VSETW (backspace_binding, VTE_ERASE_ASCII_BACKSPACE);
  gsh_widget_set_font(GTK_WIDGET(widget), term->font);
  gsh=term->gsh;
  if (GSH_FLAG (GSH_TERM_TRANSPARENT))
    {
      VSETW (background_transparent, TRUE);
    }
}

static const gchar *
get_shell ()
{
  /* This fixes the failure of environment inheritance
     under cygwin.  */
  const gchar *shell = g_getenv ("SHELL");

  return shell ? shell : (const gchar *) GSH_DEFAULT_SHELL;
}

static void
handle_child_exited (GtkWidget * widget, gpointer term)
{
  GtkNotebook *notebook 
    = GTK_NOTEBOOK (((GSHTerminal *)term)->__notebook);

  gtk_notebook_remove_page (notebook,
			    gtk_notebook_page_num (notebook, widget));
}

static gchar *
get_terminal_dimension(const gint dim, const gchar *env)
{
  gchar *dstr;
  gchar *tmp;

  tmp = ar_dtostr(dim);
  dstr = g_strconcat(env, tmp, NULL);
  g_free(tmp);

  return dstr;
}

static void
gsh_terminal_run (GSHTerminal *term, const gchar * command)
{
  /* Set up line and column counts so that VI has correct display
     in IDE terminal.  */
  gchar *height, *width;

  height = get_terminal_dimension(term->dimensions.height, "LINES=");
  width = get_terminal_dimension(term->dimensions.width, "COLUMNS=");

  {
    /* Null terminated list of environment elements.  */
    const gchar *envv[] = { height, width, NULL };
    /* Determine which shell to use.  */
    const gchar *shell = get_shell ();
    /* Null terminated list of program arguments.  Use
       the shell as a command processor, such to avoid
       handling argument separation here.  */
    const gchar *argv[] = { shell, "-c", command, NULL };
    /* Start the command in the terminal.  */
    vte_terminal_fork_command_full (VTE_TERMINAL (term->widget), 
                                    VTE_PTY_DEFAULT, NULL, 
                                    (char **) argv, (char **) envv, 
                                    G_SPAWN_SEARCH_PATH, NULL, 
                                    NULL, NULL, NULL);
  }
  /* Free after use.  */
  g_free (height);
  g_free (width);

  /* Handle terminal exit.  */
  GSHCONNECT(term->widget, "child-exited", handle_child_exited, term);
}

static void
gsh_delete_GSH_Terminal (GSHTerminal *term)
{
  arfree (term);
  /* Freeing the terminal font causes a segmentation fault under
   * linux, so likely a double free.  */
  /* The terminal widget itself is freed by gobject system
   * reference counting.  */
}

static void
info_changed_cb (GtkWidget * widget, gpointer data)
{
  const gchar * status=vte_terminal_get_status_line(VTE_TERMINAL(widget));
  gchar * title;
  GtkWidget *statusbar;
  GSH *gsh;

  gsh=data;
  title=g_strdup(vte_terminal_get_window_title(VTE_TERMINAL(widget)));
  if(status && (strnlen(status, 2)>1))
    {
      if ((statusbar = gsh->widgets.app.status))
        {
          gtk_statusbar_push (GTK_STATUSBAR (statusbar), 
                              gtk_statusbar_get_context_id 
                              ( GTK_STATUSBAR (statusbar), "terminal"), 
                              status);
        }
      else
        {
          gchar *tmp=title;

          title=g_strconcat(title, ": ", status, NULL);
          g_free(tmp);
        }
    }
  if(title)
    gtk_window_set_title(GTK_WINDOW(gsh->widgets.window), title);
  g_free(title);
}

static void
setup_terminal_signals (GSHTerminal *term)
{
  GtkWidget *widget;
  
  if((widget = term->widget))
    {
      GSH *gsh=term->gsh;

      GSHCONNECT (widget, "status-line-changed", info_changed_cb, gsh);
      GSHCONNECT (widget, "window-title-changed", info_changed_cb, gsh);
    }
}

static GtkWidget *
get_current_page(GtkNotebook *notebook)
{
  return gtk_notebook_get_nth_page(notebook,
                                   gtk_notebook_get_current_page(notebook));
}

static void
tab_button_close_cb (GtkWidget * button __attribute__ ((unused)), 
                     gpointer data)
{
  GSHTerminal *term = data;
  GtkNotebook *notebook = GTK_NOTEBOOK (term->__notebook);
  gtk_widget_destroy(get_current_page(notebook));
  info_changed_cb(get_current_page(notebook), term->gsh);
}

static void
change_page_cb (GtkNotebook * notebook, 
                gint arg1 __attribute__ ((unused)), 
                gpointer user_data)
{
  GSHTerminal *term = (GSHTerminal *) user_data;
  info_changed_cb(get_current_page(notebook), term->gsh);
}

static void
switch_page_cb (GtkNotebook *notebook __attribute__ ((unused)),
                GtkWidget *page,
                guint page_number __attribute__ ((unused)),
                gpointer user_data)
{
  info_changed_cb(page, user_data);
}

static void
tab_button_callback (GtkWidget * button __attribute__ ((unused)), 
                     gpointer data)
{
  GSHTerminal *term = (GSHTerminal *)data;
  $ (term, add, get_shell());
}

static void
tab_next(GtkWidget * button __attribute__ ((unused)), 
                     gpointer data)
{
  gtk_notebook_next_page(GTK_NOTEBOOK(((GSHTerminal *)data)->__notebook));
}

static void
tab_prev(GtkWidget * button __attribute__ ((unused)), 
                     gpointer data)
{
  gtk_notebook_prev_page(GTK_NOTEBOOK(((GSHTerminal *)data)->__notebook));
}

static void
page_removed_cb (GtkNotebook *notebook, 
                 GtkWidget *child __attribute__ ((unused)),
                 guint page_num __attribute__ ((unused)),
                 gpointer user_data __attribute__ ((unused)))
{
  if(gtk_notebook_get_n_pages(notebook)==0)
    exit(0);
}

static void
setup_action_widgets(GSHTerminal * term)
{
  GtkNotebook *notebook = GTK_NOTEBOOK(term->__notebook);
  GtkWidget *button;
  GtkWidget *row;

  /* setup container for navigation buttons */
  GSH_SHOW_CREATE(row, toolbar);

#define TAB_BUTTON(stock, cb)\
  ADD_STOCK_BUTTON(row, button, GTK_STOCK_##stock);\
  gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);\
  GSHCONNECT (button, "clicked", cb, term)

  /* setup New button */
  TAB_BUTTON(NEW, tab_button_callback);

  /* setup prev button */
  TAB_BUTTON(GO_BACK, tab_prev);

  /* setup next button */
  TAB_BUTTON(GO_FORWARD, tab_next);

  /* setup Close button */
  TAB_BUTTON(CLOSE, tab_button_close_cb);

  /* add the row to the tab bar */
  gtk_notebook_set_action_widget(notebook, row, GTK_PACK_END);
}

static void
setup_notebook(GSHTerminal *term)
{
  GtkWidget *notebook;

  GSH_CREATE(notebook=term->__notebook, notebook);
  setup_action_widgets(term);
  GSHCONNECT (notebook, "change-current-page", change_page_cb, term);
  GSHCONNECT (notebook, "select-page", change_page_cb, term);
  GSHCONNECT (notebook, "switch-page", switch_page_cb, term->gsh);
  GSHCONNECT (notebook, "page-removed", page_removed_cb, term);
}

static void
new_terminal_tab (GSHTerminal *term, gchar * command)
{
  GtkNotebook *notebook = GTK_NOTEBOOK(term->__notebook);
  GtkWidget *term_widget;

  term_widget = term->widget = vte_terminal_new ();
  gtk_widget_show(term_widget);
  gtk_notebook_set_current_page(notebook, 
                                gtk_notebook_append_page (notebook, 
                                                          term_widget, 
                                                          NULL));
  gtk_notebook_set_tab_label_text(notebook, term_widget, command);
  gtk_notebook_set_tab_reorderable(notebook, term_widget, TRUE);
  gtk_notebook_set_tab_detachable(notebook, term_widget, TRUE);
  gtk_widget_grab_focus(term_widget);
}

static GtkWidget *
gsh_GSH_Terminal_add (GSHTerminal *term, const gchar * command)
{
  bool original_tab;
  /* Create and set properties of the VTE-based terminal.  */
  if ((original_tab=!(term->__notebook)))
    setup_notebook(term);
  new_terminal_tab (term, g_strdup(command));
  setup_terminal_signals (term);
  set_terminal_options (term);
  gsh_terminal_run (term, command);
  
  return original_tab ? term->__notebook : NULL;
}

static void
setup_GSH_Terminal (GSHTerminal *term)
{
  /* initialize fields */
  term->widget = NULL;
  term->font = NULL;
  term->dimensions.width = 80;
  term->dimensions.height = 24;
  term->__notebook = NULL;
  /* assign methods */
  term->delete = &gsh_delete_GSH_Terminal;
  term->add = &gsh_GSH_Terminal_add;
}

GSHTerminal *
gsh_new_GSH_Terminal (GSH * gsh)
{
  GSHTerminal *term;

  term = armalloc (sizeof (GSHTerminal));
  setup_GSH_Terminal (term);
  term->gsh = (gpointer) gsh;

  return term;
}

#endif /* HAVE_VTE */

