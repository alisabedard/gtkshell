/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef XSH_STRUCT_H
#define XSH_STRUCT_H

struct XWidget
{
	Window window;
	XWindowAttributes geometry;
	struct {
		XEvent * event;
		void (*expose)(struct XWidget *);
		void (*button_press)(struct XWidget *);
		void (*button_release)(struct XWidget *);
		void (*key_press)(struct XWidget *);
		void (*configure)(struct XWidget *);
	} events;
	void * data;
	void * xsh; /* Ensure root access.  */
	struct XWidget *next;
};

typedef struct XWidget XWidget;

typedef unsigned int XSHBitmask;

#define XSH_OVERRIDE_REDIRECT 1

#ifdef XSH_USE_GRADIENT
typedef struct 
{
	Pixmap outset;
	Pixmap inset;
}XShellGUIPixbufs;
#endif /* XSH_USE_GRADIENT */

typedef struct 
{
	unsigned int row_count;
	unsigned int max_row_count;
	unsigned int column_count;
	unsigned int widget_width;
}XShellGUILayout;

typedef struct 
{
	Display * display;
	XWidget * widgets;
	XWidget * last_widget;
	XWidget * last_toplevel;
	unsigned int widget_count;
	GC gc;
	XFontStruct * font;

#ifdef XSH_USE_GRADIENT
	XShellGUIPixbufs pixbufs;
#endif /* XSH_USE_GRADIENT */
	XShellGUILayout layout;
} XShellGUI;

typedef struct 
{
	XShellGUI gui;
	XSHBitmask options;
} XShell;

#endif /* not XSH_STRUCT_H */

