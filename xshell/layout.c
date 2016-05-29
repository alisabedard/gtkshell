/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
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

#include "xshell.h"

void xsh_layout_widgets(XShell * xsh)
{
	XShellGUI *gui = &(xsh->gui);
	XShellGUILayout *layout = &(gui->layout);
	unsigned int column_count = layout->column_count;

	if (!(xsh->options & XSH_STOP_LAYOUT))
		XResizeWindow(gui->display, gui->widgets->window,
			      layout->widget_width * (column_count + 1),
			      XSH_WIDGET_HEIGHT * ((column_count > 0
						    ? layout->
						    max_row_count : layout->
						    row_count)));
/*	xsh->options|=XSH_STOP_LAYOUT; */
}
