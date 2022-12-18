/*
  GUIShell
  (c) 2002-2006 Alisa Bedard
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

#ifndef GSH_FILE_DIALOG_H
#define GSH_FILE_DIALOG_H

#define GSH_FILE_DIALOG(gsh, action)\
	gsh_common_dialog_executioner(gsh,\
		gtk_file_chooser_dialog_new("File Chooser",\
		  GTK_WINDOW(gsh->widgets.window), action,\
                  GTK_STOCK_CANCEL,\
		  GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN,\
                  GTK_RESPONSE_ACCEPT, NULL),\
		  gsh_file_dialog_submit)

#endif /* !GSH_FILE_DIALOG_H */
