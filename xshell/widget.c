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

#include "xshell.h"

XShell *
xsh_get_XShell_for_widget(XWidget * widget)
{
	return (XShell *)(widget->xsh);
}

Display *
xsh_get_display_for_widget(XWidget * widget)
{
	XShell * xsh;

	xsh=xsh_get_XShell_for_widget(widget);

	return xsh->gui.display;
}

#define NULLIFY_WIDGET_MEMBERS(widget)\
	widget->data=NULL;\
	widget->next=NULL;\
	XSH_NULLIFY_WIDGET_EVENTS(widget);\
	

#define SETUP_WIDGET_GEOMETRY(widget, width, height, x, y)\
	widget->geometry.x=x;\
	widget->geometry.y=y;\
	widget->geometry.width=width;\
	widget->geometry.height=height;

static void
initialize_widget_members(XWidget * widget, 
	int x, int y, int width, int height)
{
	NULLIFY_WIDGET_MEMBERS(widget);
	SETUP_WIDGET_GEOMETRY(widget, width, height, x, y);
}

static void
setup_events(XShell * xsh, XWidget * widget)
{
	long event_mask;

	event_mask = ButtonPressMask | ButtonReleaseMask
		| ExposureMask | KeyPressMask | StructureNotifyMask;
	if(widget->window == xsh->gui.widgets->window)
		event_mask |= StructureNotifyMask; 
	XSelectInput(xsh->gui.display, widget->window, event_mask);
}

static void
setup_widget_window(XShell * xsh, XWidget * widget, XWidget * parent)
{
	XShellGUI * gui = &(xsh->gui);
	Display * dpy=gui->display;
	XWindowAttributes * geometry;
		
	geometry=&(widget->geometry);
	widget->window=XCreateSimpleWindow(dpy, 
		parent ? parent->window : DefaultRootWindow(dpy), 
		geometry->x, geometry->y, 
		geometry->width, geometry->height, 
#ifdef XSH_DECORATE
		0,
#else /* not XSH_DECORATE */
		1,
#endif /* XSH_DECORATE */
		BlackPixel(dpy, DefaultScreen(dpy)),
		WhitePixel(dpy, DefaultScreen(dpy)));
	if(!parent)
		gui->last_toplevel=widget;
	setup_events(xsh, widget);
}

void
xshell_XWidget_new(XShell * xsh, XWidget * parent, 
	int x, int y, int width, int height)
{
	XWidget * widget;

	widget=malloc(sizeof(XWidget));
	if(xsh->gui.widgets)
	{
		xsh->gui.last_widget->next=widget;
	}
	else
	{
		xsh->gui.widgets=widget;
	}
	initialize_widget_members(widget, x, y, width, height);
	widget->xsh=(void *)xsh;
	setup_widget_window(xsh, widget, parent);
	xsh->gui.last_widget=widget;
	xsh->gui.widget_count++;
}


