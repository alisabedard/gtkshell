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

#ifdef XSH_DECORATE
#include "xshell.h"

#ifdef GRADIENT_DELTA
#undef GRADIENT_DELTA
#endif /* GRADIENT_DELTA */
#define GRADIENT_DELTA 16

GC xsh_setup_gc(Display * display, Window window)
{
	return XCreateGC(display, window, 0, NULL);
}

static void cleanup(Display * display, GC gc)
{
	XFreeGC(display, gc);
}

#ifdef XSH_USE_INDICATORS

#define SET_GC_FOR_INDICATOR_TYPE(dpy, gc, indicator)\
	XSH_SET_COLOR(dpy, gc, 255/(indicator+1), 0xb2, 0xc3);

static void
draw_indicator(Display * dpy, Window win, GC gc, XWindowAttributes geometry,
	       int indicator_type)
{
	SET_GC_FOR_INDICATOR_TYPE(dpy, gc, indicator_type);
#define INDICATOR_GEOMETRY geometry.width-8, geometry.height/5, 4, 8, 0, 23040
	XFillArc(dpy, win, gc, INDICATOR_GEOMETRY);
	XSH_SET_COLOR(dpy, gc, (0xae) / 2, (0xb2) / 2, (0xc3) / 2);
	XDrawArc(dpy, win, gc, INDICATOR_GEOMETRY);
	XSH_SET_COLOR(dpy, gc, (0xae) / 3, (0xb2) / 3, (0xc3) / 3);
	XDrawArc(dpy, win, gc, INDICATOR_GEOMETRY);
}
#endif /* XSH_USE_INDICATORS */

#define SET_COLOR XSH_SET_COLOR

static void
draw_frame(Display * dpy, Window win, GC gc, Bool outset,
	   XWindowAttributes geometry)
{
	short val;

	val = outset ? 255 : 0;
	XSH_SET_COLOR(dpy, gc, val, val, val);
	/* top */
	XDrawLine(dpy, win, gc, 0, 0, geometry.width, 0);
	/* left */
	XDrawLine(dpy, win, gc, 0, 0, 0, geometry.height);

	val = !outset ? 255 : 0;
	XSH_SET_COLOR(dpy, gc, val, val, val);
	/* bottom */
	XDrawLine(dpy, win, gc, 0, geometry.height - 1,
		  geometry.width, geometry.height - 1);
	/* right */
	XDrawLine(dpy, win, gc, geometry.width - 1, 0,
		  geometry.width - 1, geometry.height);

#ifdef XSH_USE_INDICATORS
	draw_indicator(dpy, win, gc, geometry, XSH_INDICATE_NORMAL);
#endif /* XSH_USE_INDICATORS */
}

#ifdef XSH_USE_GRADIENT
static void
draw_gradient(Display * display, Window window, GC gc,
	      XWindowAttributes * geometry, int order)
{
	unsigned int counter;

	for (counter = 0; counter++ < (unsigned int)geometry->height;) {
		unsigned int delta;
		int y;

		delta = -order * counter * 4;
		XSH_SET_COLOR(display, gc,
			      (0xae) + delta * (order),
			      (0xb2) + delta * (order),
			      (0xc3) + delta * (order));
		/* Sunken or raised determined by Y start.  */
		y = (order >= 0) ? counter : geometry->height - counter;
		/* Draw gradient portion.  */
		XDrawLine(display, window, gc, 0, y, geometry->width, y);
	}
}

#endif /* XSH_USE_GRADIENT */

void xsh_decorate(XWidget * widget, int order)
{
	GC gc;
	XShell *xsh;
	Display *display;
	Window window;

	xsh = xsh_get_XShell_for_widget(widget);
	gc = xsh_setup_gc(display = xsh->gui.display, window = widget->window);

	/* Draw decoration */
	{
		XWindowAttributes geometry;

		XGetWindowAttributes(display, window, &geometry);
#ifdef XSH_USE_GRADIENT
		draw_gradient(display, window, gc, &geometry, -order);
#else /* not XSH_USE_GRADIENT */
		XSH_SET_COLOR(display, gc,
			      (0xae) + 4 * -order, (0xb2) + 4 * -order,
			      (0xc3) + 4 * -order);
		XFillRectangle(display, window, gc, 0, 0, geometry.width,
			       geometry.height);
#endif /* XSH_USE_GRADIENT */
		if (order != 0)	/* for non-flat */
			draw_frame(display, window, gc, order != 1, geometry);
	}
	/* Free GC data.  */
	cleanup(display, gc);
}

#endif /* XSH_DECORATE */
