/*
  GUIShell
  (c) 2002-2010 Jeffrey Bedard
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

void
gsh_dialog_about_cb (GSH * gsh __attribute__ ((unused)),
		     gint * counter __attribute__ ((unused)),
		     const gchar ** argv __attribute__ ((unused)))
{
  gsh_about_dialog ();
}

void
gsh_dialog_color_cb (GSH * gsh,
		     gint * counter __attribute__ ((unused)),
		     const gchar ** argv __attribute__ ((unused)))
{
  gsh_common_dialog_executioner(gsh, 
                                gtk_color_selection_dialog_new("Select Color"),
                                &gsh_color_dialog_submit);
}

void
gsh_dialog_folder_cb (GSH * gsh,
		      gint * counter __attribute__ ((unused)),
		      const gchar ** argv __attribute__ ((unused)))
{
  GSH_FILE_DIALOG(gsh, GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER);
}

void
gsh_dialog_folder_open_cb (GSH * gsh,
			   gint * counter __attribute__ ((unused)),
			   const gchar ** argv __attribute__ ((unused)))
{
  GSH_FILE_DIALOG(gsh, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
}

void
gsh_dialog_error_cb (GSH * gsh, gint * counter, const gchar ** argv)
{
  GSH_MESSAGE_DIALOG (gsh, GTK_MESSAGE_ERROR, argv[++(*counter)]);
}

void
gsh_dialog_font_cb (GSH * gsh,
		    gint * counter __attribute__ ((unused)),
		    const gchar ** argv __attribute__ ((unused)))
{
  gsh_common_dialog_executioner(gsh, 
                                gtk_font_selection_dialog_new("Select Font"),
                                &gsh_font_dialog_submit);
}

void
gsh_dialog_file_cb (GSH * gsh,
		    gint * counter __attribute__ ((unused)),
		    const gchar ** argv __attribute__ ((unused)))
{
  GSH_FILE_DIALOG(gsh, GTK_FILE_CHOOSER_ACTION_OPEN);
}

void
gsh_dialog_information_cb (GSH * gsh, gint * counter, const gchar ** argv)
{
  GSH_MESSAGE_DIALOG (gsh, GTK_MESSAGE_INFO, argv[++(*counter)]);
}

void
gsh_dialog_warning_cb (GSH * gsh, gint * counter, const gchar ** argv)
{
  GSH_MESSAGE_DIALOG (gsh, GTK_MESSAGE_WARNING, argv[++(*counter)]);
}

void
gsh_dialog_save_cb (GSH * gsh,
		    gint * counter __attribute__ ((unused)),
		    const gchar ** argv __attribute__ ((unused)))
{
  GSH_FILE_DIALOG(gsh, GTK_FILE_CHOOSER_ACTION_SAVE);
}

