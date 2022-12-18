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

#ifndef XSH_COLOR_H
#define XSH_COLOR_H

unsigned long
xsh_get_color(Display * display,
	      unsigned short r, unsigned short g, unsigned short b);

void xsh_set_foreground(Display * display, GC gc, unsigned long color);

#define XSH_SET_COLOR(dpy, gc, r, g, b)\
	xsh_set_foreground(dpy, gc, xsh_get_color(dpy, r, g, b))

#endif /* not XSH_COLOR_H */
