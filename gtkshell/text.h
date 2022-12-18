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

#ifndef GSH_TEXT_H
#define GSH_TEXT_H

GtkTextBuffer *gsh_text_area_set_text(GtkWidget * widget, const gchar * text);

GtkWidget *gsh_setup_command_entry(struct GSH *gsh, const gchar * command);

void gsh_setup_prompt_command_entry(struct GSH *gsh, const gchar * command);

GtkWidget *gsh_text_area(struct GSH *gsh);

void gsh_text_editor(struct GSH *gsh, const gchar * filename);

void gsh_editor_save_as(struct GSH *gsh);

void gsh_editor_save(struct GSH *gsh);

void gsh_editor_open(struct GSH *gsh);

#endif
