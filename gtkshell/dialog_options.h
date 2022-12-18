/*
  GUIShell
  (c) 2002-2007 Alisa Bedard
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GSH_DIALOG_OPTIONS
#define GSH_DIALOG_OPTIONS

void gsh_dialog_about_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_color_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_folder_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_folder_open_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_error_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_font_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_file_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_information_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_warning_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_dialog_save_cb(GSH * gsh, gint * counter, const gchar ** argv);

#endif
