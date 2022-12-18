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

#ifndef XSH_DECOR_H
#define XSH_DECOR_H

#ifdef XSH_DECORATE

#define XSH_DECOR_IN 1
#define XSH_DECOR_FLAT 0
#define XSH_DECOR_OUT -1

#define XSH_SETUP_GC(display, window)\
	XCreateGC(display, window, 0, NULL);

void xsh_decorate(XWidget * widget, int order);

#if 0
void xsh_setup_gradients(XShell * xsh);
#endif

#ifdef XSH_USE_INDICATORS
#define XSH_INDICATE_ERROR 	0
#define XSH_INDICATE_WARN 	1
#define XSH_INDICATE_INFO	2
#define XSH_INDICATE_DEBUG	3
#define XSH_INDICATE_NORMAL	4
#define XSH_INDICATE_NONE	6
#define XSH_INDICATE_DISABLED	10
#endif /* XSH_USE_INDICATORS */

#endif /* XSH_DECORATE */

/* These functions are used elsewhere regardless of decorated widgets.  */

GC xsh_setup_gc(Display * display, Window window);

unsigned long
xsh_get_color(Display * display,
	      unsigned short r, unsigned short g, unsigned short b);

void xsh_set_foreground(Display * display, GC gc, unsigned long color);

#define XSH_SET_COLOR(dpy, gc, r, g, b)\
	xsh_set_foreground(dpy, gc, xsh_get_color(dpy, r, g, b))

#endif /* XSH_DECOR_H */
