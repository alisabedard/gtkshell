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

void xsh_set_font(XShell * xsh, const char *name)
{
	XGCValues values;
	XFontStruct *font;
	XShellGUI *gui = &(xsh->gui);

	xsh->gui.font = font = XLoadQueryFont(gui->display, name);
	values.font = font->fid;

	XChangeGC(gui->display, gui->gc, GCFont, &values);
}

void xsh_free_font(XShell * xsh)
{
	XGCValues values;
	Display *dpy = xsh->gui.display;

	XGetGCValues(dpy, xsh->gui.gc, GCFont, &values);
	XFreeFont(dpy, xsh->gui.font);
}
