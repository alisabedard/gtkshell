/*
  GUIShell
  (c) 2006-2007 Alisa Bedard
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
  Boston, MA  02110-1301  USA
*/

#ifndef GSH_MENU_H
#define GSH_MENU_H

typedef enum {
	GMT_NONE,
	GMT_FILE,
	GMT_EDIT,
	GMT_TOOLS,
	GMT_VIEW,
	GMT_HELP
} GSHMenuType;

GSHMenuType gsh_is_menubar_item(const gchar * label);

void gsh_add_tearoff(GtkWidget * submenu);

void gsh_menubutton_parse(struct GSH *gsh, gchar ** tokens);

#endif /* GSH_MENU_H */
