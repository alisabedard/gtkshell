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

#define gsh_send_signal g_signal_emit_by_name

static void
gsh_delete_GSHCBData (struct GSHCBData *cb)
{
  g_free (cb->data);
  arfree (cb);
}

static void
terminal_feed (gchar * command, GtkWidget * terminal)
{
  if (!terminal)
    {
      ARWARN ("terminal command requires a terminal to have been created");
      return;
    }

  command += 6;
    {
      gchar *feed_command;
      {
        gchar **split_command;

        split_command = g_strsplit (command, "#", 2);
        feed_command = g_strconcat (split_command[0], "\n", NULL);
        g_strfreev (split_command);
      }
#ifdef HAVE_VTE
      vte_terminal_feed_child (VTE_TERMINAL (terminal), 
                               feed_command, strlen (feed_command));
#endif /* HAVE_VTE */
      g_free (feed_command);
    }
}

#include <ctype.h>

static bool
test_special_command (struct GSHCBData *cb)
{
  const gchar *command = g_strstrip(cb->data);
  const size_t cmdsiz=strlen(command);
  struct GSH *gsh = cb->gsh;

#define GSS(sig) gsh_send_signal(gsh->editor.widget, sig)
#define TESTEDITOR() if(!(gsh->editor.widget)) break
  if(command[cmdsiz-1] != '_')
    return FALSE; /* special commands end with _ */
  switch(tolower(command[0]))
    {
    case 'a':
      gtkshell_system ("gtkshell -da &");
      break;
    case 'c':
      TESTEDITOR();
      if(tolower(command[1])=='u')
        GSS("cut-clipboard");
      else
        GSS("copy-clipboard");
      break;
    case 'e':
      gtk_main_quit();
      break;
    case 'o':
      TESTEDITOR();
      gsh_editor_open (gsh);
      break;
    case 'p':
      TESTEDITOR();
      GSS("paste-clipboard");
      break;
    case 's':
      TESTEDITOR();
      if((cmdsiz>5) && (tolower(command[5]) == 'a'))
        gsh_editor_save_as (gsh);
      else
        gsh_editor_save (gsh);
      break;
    case 't':
      terminal_feed ((gchar *) command, gsh->terminal->widget);
      break;
    default:
      return FALSE;
    }
  /* A special command match was found.  */
  return TRUE;
}

#define test_exit(gsh) if(gsh->bflags & GSH_CBEXIT) gtk_main_quit()

static void
gsh_system_cb (GtkWidget * widget __attribute__ ((unused)), gpointer data)
{
  if (data)
    {
      struct GSHCBData *cb = data;

      if (!test_special_command (cb))
	(void) gtkshell_system (cb->data);
      test_exit (cb->gsh);
    }
#ifdef LIBGC
  GC_gcollect ();
#endif /* LIBGC */
}

static void
exec_and_test_print (struct GSHCBData *cb, const gchar * input)
{
  struct GSH *gsh;

  gsh = cb->gsh;

  if (GSH_FLAG (GSH_PROMPT_ECHOES))
    g_print ("%s\n", input);
  else
    sysprintf ("%s %s", (char *) cb->data, (char *) input);
}

static void
gsh_entry_cb (GtkWidget * widget, gpointer data)
{
  struct GSHCBData *cb;

  /* Convert to dereferencable form.  */
  cb = (struct GSHCBData *) data;

  {
    GtkWidget *combo_box;
    /* INPUT must not be freed, as 
       it is internal to the widget.   */
    const gchar *input;
    /* Get widget from which to retrieve text.  */
    combo_box = gtk_widget_get_ancestor (widget, GTK_TYPE_COMBO_BOX);
    /* Get the text from the widget.  */
    input = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combo_box));
    exec_and_test_print (cb, input);
    /* Determine whether or not to exit 
     * because of this callback.  */
    test_exit (cb->gsh);
    /* Add retrieved text to combo box popup list.  */
    gtk_combo_box_prepend_text (GTK_COMBO_BOX (combo_box), (gchar *) input);
  }
}

/* GSHCBData Constructor */
struct GSHCBData *
gsh_new_GSHCBData (struct GSH *gsh, gpointer data)
{
  struct GSHCBData *cb;

  /* Allocate.  */
  cb = armalloc (sizeof (struct GSHCBData));
  /* Store constructor arguments.  */
  cb->gsh = gsh;
  cb->data = data;
  /* Assign the function pointers for GSHCBData's methods.  */
  cb->delete = &gsh_delete_GSHCBData;
  cb->entry = &gsh_entry_cb;
  cb->system = &gsh_system_cb;

  return cb;
}

