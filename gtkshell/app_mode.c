/*
  GUIShell
  (c) 2006-2007 Jeffrey Bedard
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
  Boston, MA  02110-1301  USA
*/

#include "gtkshell.h"

#define GWA gsh->widgets.app

void
gsh_setup_app_mode (GSH *gsh)
{
  /* setup row */
  GSH_CREATE (GWA.row, vbox, FALSE, 0);
  /* add menu bar to application column */
  GSHCA_TIGHT (GWA.row, GWA.menubar);
  /* setup toolbar */
  GSH_ADD_WIDGET_TIGHT(GWA.row, GWA.toolbar, toolbar);
  gtk_toolbar_set_style (GTK_TOOLBAR (GWA.toolbar), GTK_TOOLBAR_ICONS);
  /* setup frame */
  GSH_ADD_WIDGET(GWA.row, GWA.frame, frame, NULL);
  /* setup status bar */
  GSH_ADD_WIDGET_TIGHT(GWA.row, GWA.status, statusbar);
}

