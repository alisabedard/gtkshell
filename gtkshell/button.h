/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
  jefbed@gmail.com

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

#ifndef GSH_BUTTON_H
#define GSH_BUTTON_H

GtkWidget *gsh_add_button(struct GSH *gsh, const gchar * string);

#define GSH_LABEL_TO_ICON_MAPPINGS \
{\
	{ "Run...", GTK_STOCK_EXECUTE },\
	{ "About", GTK_STOCK_ABOUT },\
	{ "Exit", GTK_STOCK_QUIT },\
	{ "Save", GTK_STOCK_SAVE },\
	{ "Save As...", GTK_STOCK_SAVE_AS },\
	{ "Cut", GTK_STOCK_CUT },\
	{ "Copy", GTK_STOCK_COPY },\
	{ "Paste", GTK_STOCK_PASTE },\
	{ "Close", GTK_STOCK_CLOSE }\
}

bool gsh_check_command_exists(GSH * gsh, const gchar * command);

#endif
