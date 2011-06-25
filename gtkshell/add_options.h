/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
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

#ifndef GSH_ADD_OPTIONS_H
#define GSH_ADD_OPTIONS_H

#include "gtkshell.h"

void gsh_add_window_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_applet_clock_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_pane_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_command_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_editor_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_form_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_list_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_label_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_piped_text_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_piped_label_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_quickstart_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_row_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_separator_cb (GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_add_commanded_button_cb (GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_add_commanded_label_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_shell_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_entry_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_text_cb (GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_add_updating_progress_cb (GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_add_updating_label_cb (GSH * gsh, gint * counter, const gchar ** argv);

void gsh_add_embedded_cb (GSH * gsh, gint * counter, const gchar ** argv);

#endif
